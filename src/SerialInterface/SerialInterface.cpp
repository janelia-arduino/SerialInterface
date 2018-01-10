// ----------------------------------------------------------------------------
// SerialInterface.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "../SerialInterface.h"


using namespace serial_interface;

SerialInterface::SerialInterface()
{
}

void SerialInterface::setup()
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
  modular_server::Property & serial_bauds_property = modular_server_.createProperty(constants::serial_bauds_property_name,constants::serial_bauds_default);
  serial_bauds_property.setSubset(constants::serial_baud_subset);
  serial_bauds_property.setArrayLengthRange(constants::SERIAL_STREAM_COUNT,constants::SERIAL_STREAM_COUNT);
  serial_bauds_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&SerialInterface::resetSerialStreamHandler));

  modular_server::Property & serial_settings_property = modular_server_.createProperty(constants::serial_settings_property_name,constants::serial_settings_default);
  serial_settings_property.setSubset(constants::serial_setting_ptr_subset);
  serial_settings_property.setArrayLengthRange(constants::SERIAL_STREAM_COUNT,constants::SERIAL_STREAM_COUNT);
  serial_settings_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&SerialInterface::resetSerialStreamHandler));

  // Parameters

  // Functions
  modular_server::Function & get_serial_stream_count_function = modular_server_.createFunction(constants::get_serial_stream_count_function_name);
  get_serial_stream_count_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SerialInterface::getSerialStreamCountHandler));
  get_serial_stream_count_function.setResultTypeLong();

  // Callbacks

  // Begin Streams
  for (size_t i=0; i<constants::SERIAL_STREAM_COUNT; ++i)
  {
    resetSerialStreamHandler(i);
  }
}

size_t SerialInterface::getSerialStreamCount()
{
  return constants::SERIAL_STREAM_COUNT;
}

Stream & SerialInterface::getSerialStream(const size_t stream_index)
{
  if (stream_index >= constants::SERIAL_STREAM_COUNT)
  {
    return Serial;
  }
  return *(constants::serial_stream_ptrs[stream_index]);
}

long SerialInterface::getSerialStreamBaud(const size_t stream_index)
{
  if (stream_index >= constants::SERIAL_STREAM_COUNT)
  {
    return -1;
  }

  long baud;
  modular_server_.property(constants::serial_bauds_property_name).getElementValue(stream_index,baud);

  return baud;
}

byte SerialInterface::getSerialStreamSetting(const size_t stream_index)
{
  if (stream_index >= constants::SERIAL_STREAM_COUNT)
  {
    return -1;
  }

  byte setting = SERIAL_8N1;

  const ConstantString * setting_ptr;
  modular_server_.property(constants::serial_settings_property_name).getElementValue(stream_index,setting_ptr);

  if (setting_ptr == &constants::serial_setting_7e1)
  {
    setting = SERIAL_7E1;
  }
  else if (setting_ptr == &constants::serial_setting_7o1)
  {
    setting = SERIAL_7O1;
  }
  else if (setting_ptr == &constants::serial_setting_8n1)
  {
    setting = SERIAL_8N1;
  }
  else if (setting_ptr == &constants::serial_setting_8n2)
  {
    setting = SERIAL_8N2;
  }
  else if (setting_ptr == &constants::serial_setting_8e1)
  {
    setting = SERIAL_8E1;
  }
  else if (setting_ptr == &constants::serial_setting_8o1)
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

void SerialInterface::resetSerialStreamHandler(const size_t stream_index)
{
  if (stream_index >= constants::SERIAL_STREAM_COUNT)
  {
    return;
  }
  long baud = getSerialStreamBaud(stream_index);
  byte setting = getSerialStreamSetting(stream_index);
  constants::serial_stream_ptrs[stream_index]->end();
  constants::serial_stream_ptrs[stream_index]->begin(baud,setting);
}

void SerialInterface::getSerialStreamCountHandler()
{
  modular_server_.response().returnResult((long)constants::SERIAL_STREAM_COUNT);
}
