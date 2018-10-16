// ----------------------------------------------------------------------------
// SerialInterface.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "SerialInterface/Constants.h"


class SerialInterface : public ModularDeviceBase
{
public:
  SerialInterface();
  virtual void setup();

  size_t getSerialStreamCount();
  size_t getSerialStreamIndex();
  size_t setSerialStreamIndex(size_t stream_index);
  Stream & getSerialStream();

  char getLineEnding(const ConstantString * line_ending_ptr);

  size_t write(const char data[]);
  size_t writeBytes(const uint8_t buffer[],
    size_t size);
  size_t writeByte(uint8_t byte);
  size_t writeLineEnding();

  size_t read(char response[],
    size_t response_length_max);

  size_t writeRead(const char data[],
    char response[],
    size_t response_length_max);

private:
  modular_server::Property properties_[serial_interface::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[serial_interface::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[serial_interface::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[serial_interface::constants::CALLBACK_COUNT_MAX];

  size_t serial_stream_index_;

  long getSerialStreamBaud(size_t stream_index);
  size_t getSerialStreamSetting(size_t stream_index);
  long getSerialStreamTimeout(size_t stream_index);

  void terminateResponse(char response[],
    size_t response_length_max,
    size_t bytes_read);

  // Handlers
  void resetSerialStreamHandler(size_t stream_index);
  void getSerialStreamCountHandler();
  void getSerialStreamIndexHandler();
  void setSerialStreamIndexHandler();
  void writeHandler();
  void writeReadHandler();
};

#endif
