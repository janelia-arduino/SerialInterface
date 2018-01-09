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
  modular_server::Property & rs232_bauds_property = modular_server_.createProperty(constants::rs232_bauds_property_name,constants::rs232_bauds_default);
  rs232_bauds_property.setSubset(constants::rs232_baud_subset);
  rs232_bauds_property.setArrayLengthRange(constants::RS232_STREAM_COUNT,constants::RS232_STREAM_COUNT);
  rs232_bauds_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&Rs232Interface::resetRs232StreamHandler));

  modular_server::Property & rs232_settings_property = modular_server_.createProperty(constants::rs232_settings_property_name,constants::rs232_settings_default);
  rs232_settings_property.setSubset(constants::rs232_setting_ptr_subset);
  rs232_settings_property.setArrayLengthRange(constants::RS232_STREAM_COUNT,constants::RS232_STREAM_COUNT);
  rs232_settings_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&Rs232Interface::resetRs232StreamHandler));

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
  modular_server_.property(constants::rs232_bauds_property_name).getElementValue(stream_index,baud);

  return baud;
}

byte Rs232Interface::getRs232StreamSetting(const size_t stream_index)
{
  if (stream_index >= constants::RS232_STREAM_COUNT)
  {
    return -1;
  }

  byte setting = SERIAL_8N1;

  const ConstantString * setting_ptr;
  modular_server_.property(constants::rs232_settings_property_name).getElementValue(stream_index,setting_ptr);

  if (setting_ptr == &constants::rs232_setting_7e1)
  {
    setting = SERIAL_7E1;
  }
  else if (setting_ptr == &constants::rs232_setting_7o1)
  {
    setting = SERIAL_7O1;
  }
  else if (setting_ptr == &constants::rs232_setting_8n1)
  {
    setting = SERIAL_8N1;
  }
  else if (setting_ptr == &constants::rs232_setting_8n2)
  {
    setting = SERIAL_8N2;
  }
  else if (setting_ptr == &constants::rs232_setting_8e1)
  {
    setting = SERIAL_8E1;
  }
  else if (setting_ptr == &constants::rs232_setting_8o1)
  {
    setting = SERIAL_8O1;
  }

  return setting;
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
  byte setting = getRs232StreamSetting(stream_index);
  constants::rs232_stream_ptrs[stream_index]->end();
  constants::rs232_stream_ptrs[stream_index]->begin(baud,setting);
}

void Rs232Interface::getRs232StreamCountHandler()
{
  modular_server_.response().returnResult((long)constants::RS232_STREAM_COUNT);
}
