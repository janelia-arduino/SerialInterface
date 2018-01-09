// ----------------------------------------------------------------------------
// Rs232Interface.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "../Rs232Interface.h"


using namespace rs232_interface;

Rs232Interface::Rs232Interface()
{
}

void Rs232Interface::setup()
{
  // Parent Setup
  ModularDeviceBase::setup();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & baud_rates_property = modular_server_.createProperty(constants::baud_rates_property_name,constants::baud_rates_default);
  baud_rates_property.setRange(constants::baud_rate_min,constants::baud_rate_max);
  baud_rates_property.setArrayLengthRange(constants::RS232_STREAM_COUNT,constants::RS232_STREAM_COUNT);
  baud_rates_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&Rs232Interface::resetRs232StreamHandler));

  modular_server::Property & data_bits_property = modular_server_.createProperty(constants::data_bits_property_name,constants::data_bits_default);
  data_bits_property.setSubset(constants::data_bits_subset);
  data_bits_property.setArrayLengthRange(constants::RS232_STREAM_COUNT,constants::RS232_STREAM_COUNT);
  data_bits_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&Rs232Interface::resetRs232StreamHandler));

  modular_server::Property & parities_property = modular_server_.createProperty(constants::parities_property_name,constants::parities_default);
  parities_property.setSubset(constants::parity_ptr_subset);
  parities_property.setArrayLengthRange(constants::RS232_STREAM_COUNT,constants::RS232_STREAM_COUNT);
  parities_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&Rs232Interface::resetRs232StreamHandler));

  modular_server::Property & stop_bits_property = modular_server_.createProperty(constants::stop_bits_property_name,constants::stop_bits_default);
  stop_bits_property.setSubset(constants::stop_bits_subset);
  stop_bits_property.setArrayLengthRange(constants::RS232_STREAM_COUNT,constants::RS232_STREAM_COUNT);
  stop_bits_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&Rs232Interface::resetRs232StreamHandler));

  // Parameters

  // Functions
  modular_server::Function & get_rs232_stream_count_function = modular_server_.createFunction(constants::get_rs232_stream_count_function_name);
  get_rs232_stream_count_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&Rs232Interface::getRs232StreamCountHandler));
  get_rs232_stream_count_function.setResultTypeLong();

  // Callbacks

  // Begin Streams
  for (size_t i=0; i<constants::RS232_STREAM_COUNT; ++i)
  {
    resetRs232StreamHandler(i);
  }
}

size_t Rs232Interface::getRs232StreamCount()
{
  return constants::RS232_STREAM_COUNT;
}

Stream & Rs232Interface::getRs232Stream(const size_t stream_index)
{
  if (stream_index >= constants::RS232_STREAM_COUNT)
  {
    return Serial;
  }
  return *(constants::rs232_stream_ptrs[stream_index]);
}

long Rs232Interface::getRs232StreamBaud(const size_t stream_index)
{
  if (stream_index >= constants::RS232_STREAM_COUNT)
  {
    return -1;
  }

  long baud;
  modular_server_.property(constants::baud_rates_property_name).getElementValue(stream_index,baud);

  return baud;
}

byte Rs232Interface::getRs232StreamConfig(const size_t stream_index)
{
  if (stream_index >= constants::RS232_STREAM_COUNT)
  {
    return -1;
  }

  byte config = SERIAL_8N1;

  long data_bits;
  modular_server_.property(constants::data_bits_property_name).getElementValue(stream_index,data_bits);

  const ConstantString * parity_ptr;
  modular_server_.property(constants::parities_property_name).getElementValue(stream_index,parity_ptr);

  long stop_bits;
  modular_server_.property(constants::stop_bits_property_name).getElementValue(stream_index,stop_bits);

  else if ((data_bits == 7) && (parity_ptr == &constants::parity_none) && (stop_bits == 1))
  {
    config = SERIAL_7N1;
  }
  else if ((data_bits == 8) && (parity_ptr == &constants::parity_none) && (stop_bits == 1))
  {
    config = SERIAL_8N1;
  }
  else if ((data_bits == 7) && (parity_ptr == &constants::parity_none) && (stop_bits == 2))
  {
    config = SERIAL_7N2;
  }
  else if ((data_bits == 8) && (parity_ptr == &constants::parity_none) && (stop_bits == 2))
  {
    config = SERIAL_8N2;
  }
  else if ((data_bits == 7) && (parity_ptr == &constants::parity_even) && (stop_bits == 1))
  {
    config = SERIAL_7E1;
  }
  else if ((data_bits == 8) && (parity_ptr == &constants::parity_even) && (stop_bits == 1))
  {
    config = SERIAL_8E1;
  }
  else if ((data_bits == 7) && (parity_ptr == &constants::parity_even) && (stop_bits == 2))
  {
    config = SERIAL_7E2;
  }
  else if ((data_bits == 8) && (parity_ptr == &constants::parity_even) && (stop_bits == 2))
  {
    config = SERIAL_8E2;
  }
  else if ((data_bits == 7) && (parity_ptr == &constants::parity_odd) && (stop_bits == 1))
  {
    config = SERIAL_7O1;
  }
  else if ((data_bits == 8) && (parity_ptr == &constants::parity_odd) && (stop_bits == 1))
  {
    config = SERIAL_8O1;
  }
  else if ((data_bits == 7) && (parity_ptr == &constants::parity_odd) && (stop_bits == 2))
  {
    config = SERIAL_7O2;
  }
  else if ((data_bits == 8) && (parity_ptr == &constants::parity_odd) && (stop_bits == 2))
  {
    config = SERIAL_8O2;
  }

  return config;
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void Rs232Interface::resetRs232StreamHandler(const size_t stream_index)
{
  if (stream_index >= constants::RS232_STREAM_COUNT)
  {
    return;
  }
  long baud = getRs232StreamBaud(stream_index);
  byte config = getRs232StreamConfig(stream_index);
  constants::rs232_stream_ptrs[stream_index]->end();
  constants::rs232_stream_ptrs[stream_index]->begin(baud,config);
}

void Rs232Interface::getRs232StreamCountHandler()
{
  modular_server_.response().returnResult((long)constants::RS232_STREAM_COUNT);
}
