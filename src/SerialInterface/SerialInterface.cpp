// ----------------------------------------------------------------------------
// SerialInterface.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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
  setSerialStreamIndex(constants::serial_stream_index_min);

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & bauds_property = modular_server_.createProperty(constants::bauds_property_name,constants::bauds_default);
  bauds_property.setSubset(constants::baud_subset);
  bauds_property.setArrayLengthRange(constants::SERIAL_STREAM_COUNT,constants::SERIAL_STREAM_COUNT);
  bauds_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&SerialInterface::resetSerialStreamHandler));

  modular_server::Property & formats_property = modular_server_.createProperty(constants::formats_property_name,constants::formats_default);
  formats_property.setSubset(constants::format_ptr_subset);
  formats_property.setArrayLengthRange(constants::SERIAL_STREAM_COUNT,constants::SERIAL_STREAM_COUNT);
  formats_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&SerialInterface::resetSerialStreamHandler));

  modular_server::Property & write_line_endings_property = modular_server_.createProperty(constants::write_line_endings_property_name,constants::write_line_endings_default);
  write_line_endings_property.setSubset(constants::line_ending_ptr_subset);
  write_line_endings_property.setArrayLengthRange(constants::SERIAL_STREAM_COUNT,constants::SERIAL_STREAM_COUNT);

  modular_server::Property & read_line_endings_property = modular_server_.createProperty(constants::read_line_endings_property_name,constants::read_line_endings_default);
  read_line_endings_property.setSubset(constants::line_ending_ptr_subset);
  read_line_endings_property.setArrayLengthRange(constants::SERIAL_STREAM_COUNT,constants::SERIAL_STREAM_COUNT);

  modular_server::Property & timeouts_property = modular_server_.createProperty(constants::timeouts_property_name,constants::timeouts_default);
  timeouts_property.setUnits(constants::millisecond_units);
  timeouts_property.setRange(constants::timeout_min,constants::timeout_max);
  timeouts_property.setArrayLengthRange(constants::SERIAL_STREAM_COUNT,constants::SERIAL_STREAM_COUNT);
  timeouts_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&SerialInterface::resetSerialStreamHandler));

  // Parameters
  modular_server::Parameter & serial_stream_index_parameter = modular_server_.createParameter(constants::serial_stream_index_parameter_name);
  serial_stream_index_parameter.setRange(constants::serial_stream_index_min,(long)(constants::SERIAL_STREAM_COUNT - 1));

  modular_server::Parameter & data_parameter = modular_server_.createParameter(constants::data_parameter_name);
  data_parameter.setTypeString();

  // Functions
  modular_server::Function & get_serial_stream_count_function = modular_server_.createFunction(constants::get_serial_stream_count_function_name);
  get_serial_stream_count_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SerialInterface::getSerialStreamCountHandler));
  get_serial_stream_count_function.setResultTypeLong();

  modular_server::Function & get_serial_stream_index_function = modular_server_.createFunction(constants::get_serial_stream_index_function_name);
  get_serial_stream_index_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SerialInterface::getSerialStreamIndexHandler));
  get_serial_stream_index_function.setResultTypeLong();

  modular_server::Function & set_serial_stream_index_function = modular_server_.createFunction(constants::set_serial_stream_index_function_name);
  set_serial_stream_index_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SerialInterface::setSerialStreamIndexHandler));
  set_serial_stream_index_function.addParameter(serial_stream_index_parameter);
  set_serial_stream_index_function.setResultTypeLong();

  modular_server::Function & write_function = modular_server_.createFunction(constants::write_function_name);
  write_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SerialInterface::writeHandler));
  write_function.addParameter(data_parameter);
  write_function.setResultTypeLong();

  modular_server::Function & write_read_function = modular_server_.createFunction(constants::write_read_function_name);
  write_read_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SerialInterface::writeReadHandler));
  write_read_function.addParameter(data_parameter);
  write_read_function.setResultTypeString();

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

size_t SerialInterface::getSerialStreamIndex()
{
  return serial_stream_index_;
}

size_t SerialInterface::setSerialStreamIndex(size_t stream_index)
{
  if (stream_index < constants::SERIAL_STREAM_COUNT)
  {
    serial_stream_index_ = stream_index;
  }
  return serial_stream_index_;
}

Stream & SerialInterface::getSerialStream()
{
  return *(constants::serial_stream_ptrs[serial_stream_index_]);
}

char SerialInterface::getWriteLineEnding(const ConstantString * write_line_ending_ptr)
{
  modular_server_.property(constants::write_line_endings_property_name).getElementValue(serial_stream_index_,write_line_ending_ptr);
  return lineEndingToChar(write_line_ending_ptr);
}

char SerialInterface::getReadLineEnding(const ConstantString * read_line_ending_ptr)
{
  modular_server_.property(constants::read_line_endings_property_name).getElementValue(serial_stream_index_,read_line_ending_ptr);
  return lineEndingToChar(read_line_ending_ptr);
}

size_t SerialInterface::write(const char data[])
{
  size_t bytes_written = getSerialStream().write(data);
  bytes_written += writeLineEnding();
  return bytes_written;
}

size_t SerialInterface::writeBytes(const uint8_t buffer[],
  size_t size)
{
  return getSerialStream().write(buffer,size);
}

size_t SerialInterface::writeByte(uint8_t byte)
{
  return getSerialStream().write(byte);
}

size_t SerialInterface::writeLineEnding()
{
  size_t bytes_written = 0;

  const ConstantString * write_line_ending_ptr = NULL;
  char write_line_ending_char = getWriteLineEnding(write_line_ending_ptr);

  if (write_line_ending_ptr == &constants::line_ending_none)
  {
    return bytes_written;
  }

  bytes_written = writeByte(write_line_ending_char);
  if (write_line_ending_ptr == &constants::line_ending_crlf)
  {
    bytes_written += writeByte('\n');
  }

  return bytes_written;
}

size_t SerialInterface::read(char response[],
  size_t response_length_max)
{
  size_t bytes_read = 0;

  const ConstantString * read_line_ending_ptr = NULL;
  char read_line_ending_char = getReadLineEnding(read_line_ending_ptr);

  if (read_line_ending_ptr != &constants::line_ending_none)
  {
    bytes_read = getSerialStream().readBytesUntil(read_line_ending_char,response,response_length_max);
  }
  else
  {
    bytes_read = getSerialStream().readBytes(response,response_length_max);
  }

  char single_char[constants::SINGLE_CHAR_LENGTH];
  if (read_line_ending_ptr == &constants::line_ending_crlf)
  {
    getSerialStream().readBytes(single_char,constants::SINGLE_CHAR_LENGTH);
  }

  terminateResponse(response,response_length_max,bytes_read);

  return bytes_read;
}

size_t SerialInterface::writeRead(const char data[],
  char response[],
  size_t response_length_max)
{
  size_t bytes_written = write(data);
  size_t bytes_read = 0;
  if (bytes_written > 0)
  {
    bytes_read = read(response,response_length_max);
  }
  return bytes_read;
}

char SerialInterface::lineEndingToChar(const ConstantString * line_ending_ptr)
{
  char line_ending_char = '\n';
  if (line_ending_ptr == &constants::line_ending_cr)
  {
    line_ending_char = '\r';
  }
  else if (line_ending_ptr == &constants::line_ending_lf)
  {
    line_ending_char = '\n';
  }
  else if (line_ending_ptr == &constants::line_ending_crlf)
  {
    line_ending_char = '\r';
  }
  return line_ending_char;
}

long SerialInterface::getSerialStreamBaud(size_t stream_index)
{
  if (stream_index >= constants::SERIAL_STREAM_COUNT)
  {
    return -1;
  }

  long baud;
  modular_server_.property(constants::bauds_property_name).getElementValue(stream_index,baud);

  return baud;
}

size_t SerialInterface::getSerialStreamSetting(size_t stream_index)
{
  if (stream_index >= constants::SERIAL_STREAM_COUNT)
  {
    return -1;
  }

  size_t setting = SERIAL_8N1;

  const ConstantString * setting_ptr;
  modular_server_.property(constants::formats_property_name).getElementValue(stream_index,setting_ptr);

  if (setting_ptr == &constants::format_7e1)
  {
    setting = SERIAL_7E1;
  }
  else if (setting_ptr == &constants::format_7o1)
  {
    setting = SERIAL_7O1;
  }
  else if (setting_ptr == &constants::format_8n1)
  {
    setting = SERIAL_8N1;
  }
  else if (setting_ptr == &constants::format_8n2)
  {
    setting = SERIAL_8N2;
  }
  else if (setting_ptr == &constants::format_8e1)
  {
    setting = SERIAL_8E1;
  }
  else if (setting_ptr == &constants::format_8o1)
  {
    setting = SERIAL_8O1;
  }

  return setting;
}

long SerialInterface::getSerialStreamTimeout(size_t stream_index)
{
  if (stream_index >= constants::SERIAL_STREAM_COUNT)
  {
    return -1;
  }

  long timeout;
  modular_server_.property(constants::timeouts_property_name).getElementValue(stream_index,timeout);

  return timeout;
}

void SerialInterface::terminateResponse(char response[],
  size_t response_length_max,
  size_t bytes_read)
{
  if (bytes_read < response_length_max)
  {
    response[bytes_read] = '\0';
  }
  else if (response_length_max > 0)
  {
    response[response_length_max - 1] = '\0';
  }
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray
// ArduinoJson::JsonObject
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void SerialInterface::resetSerialStreamHandler(size_t stream_index)
{
  if (stream_index >= constants::SERIAL_STREAM_COUNT)
  {
    return;
  }
  constants::serial_stream_ptrs[stream_index]->end();

  long baud = getSerialStreamBaud(stream_index);
  size_t setting = getSerialStreamSetting(stream_index);
  constants::serial_stream_ptrs[stream_index]->begin(baud,setting);

  long timeout = getSerialStreamTimeout(stream_index);
  constants::serial_stream_ptrs[stream_index]->setTimeout(timeout);
}

void SerialInterface::getSerialStreamCountHandler()
{
  size_t stream_count = getSerialStreamCount();
  modular_server_.response().returnResult(stream_count);
}

void SerialInterface::getSerialStreamIndexHandler()
{
  size_t stream_index = getSerialStreamIndex();
  modular_server_.response().returnResult(stream_index);
}

void SerialInterface::setSerialStreamIndexHandler()
{
  long stream_index;
  modular_server_.parameter(constants::serial_stream_index_parameter_name).getValue(stream_index);

  stream_index = setSerialStreamIndex(stream_index);
  modular_server_.response().returnResult(stream_index);
}

void SerialInterface::writeHandler()
{
  const char * data;
  modular_server_.parameter(constants::data_parameter_name).getValue(data);

  size_t bytes_written = write(data);
  modular_server_.response().returnResult(bytes_written);
}

void SerialInterface::writeReadHandler()
{
  const char * data;
  modular_server_.parameter(constants::data_parameter_name).getValue(data);

  // modular_server_.response().returnResult(response);
  modular_server_.response().returnResult(data);
}
