// ----------------------------------------------------------------------------
// SerialInterface.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H
#include <Flash.h>
#include <EEPROM.h>
#include <Streaming.h>
#include <ArduinoJson.h>
#include <JsonSanitizer.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <MemoryFree.h>
#include <ConstantVariable.h>
#include <SavedVariable.h>
#include <Functor.h>
#include <IndexedContainer.h>
#include <FunctorCallbacks.h>
#include <Watchdog.h>

#include <ModularClient.h>

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
  size_t setSerialStreamIndex(const size_t stream_index);
  Stream & getSerialStream();

  char getLineEnding(const ConstantString * line_ending_ptr);

  size_t write(const char data[]);
  size_t writeBytes(const uint8_t buffer[],
                    const size_t size);
  size_t writeByte(const uint8_t byte);
  size_t writeLineEnding();

  size_t read(char response[],
              const size_t response_length_max);

  size_t writeRead(const char data[],
                   char response[],
                   const size_t response_length_max);

private:
  modular_server::Property properties_[serial_interface::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[serial_interface::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[serial_interface::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[serial_interface::constants::CALLBACK_COUNT_MAX];

  size_t serial_stream_index_;

  long getSerialStreamBaud(const size_t stream_index);
  byte getSerialStreamSetting(const size_t stream_index);
  long getSerialStreamTimeout(const size_t stream_index);

  void terminateResponse(char response[],
                         const size_t response_length_max,
                         const size_t bytes_read);

  // Handlers
  void resetSerialStreamHandler(const size_t stream_index);
  void getSerialStreamCountHandler();
  void getSerialStreamIndexHandler();
  void setSerialStreamIndexHandler();
  void writeHandler();
  void writeReadHandler();
};

#endif
