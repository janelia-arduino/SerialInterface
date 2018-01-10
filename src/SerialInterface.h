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
  Stream & getSerialStream(const size_t stream_index);

private:
  modular_server::Property properties_[serial_interface::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[serial_interface::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[serial_interface::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[serial_interface::constants::CALLBACK_COUNT_MAX];

  long getSerialStreamBaud(const size_t stream_index);
  byte getSerialStreamSetting(const size_t stream_index);

  // Handlers
  void resetSerialStreamHandler(const size_t stream_index);
  void getSerialStreamCountHandler();
};

#endif
