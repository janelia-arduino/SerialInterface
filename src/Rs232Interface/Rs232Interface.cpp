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
  baud_rates_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&Rs232Interface::resetRS232StreamHandler));

  modular_server::Property & data_bits_property = modular_server_.createProperty(constants::data_bits_property_name,constants::data_bits_default);
  data_bits_property.setSubset(constants::data_bits_subset);
  data_bits_property.setArrayLengthRange(constants::RS232_STREAM_COUNT,constants::RS232_STREAM_COUNT);
  data_bits_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&Rs232Interface::resetRS232StreamHandler));

  modular_server::Property & parities_property = modular_server_.createProperty(constants::parities_property_name,constants::parities_default);
  parities_property.setSubset(constants::parity_ptr_subset);
  parities_property.setArrayLengthRange(constants::RS232_STREAM_COUNT,constants::RS232_STREAM_COUNT);
  parities_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&Rs232Interface::resetRS232StreamHandler));

  modular_server::Property & stop_bits_property = modular_server_.createProperty(constants::stop_bits_property_name,constants::stop_bits_default);
  stop_bits_property.setSubset(constants::stop_bits_subset);
  stop_bits_property.setArrayLengthRange(constants::RS232_STREAM_COUNT,constants::RS232_STREAM_COUNT);
  stop_bits_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&Rs232Interface::resetRS232StreamHandler));

  // Parameters

  // Functions

  // Callbacks

  // Begin Streams
  for (size_t i=0; i<constants::RS232_STREAM_COUNT; ++i)
  {
    constants::rs232_stream_ptrs[i]->begin(baud,config);
  }
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

void Rs232Interface::resetRS232StreamHandler(const size_t stream_index)
{

}
