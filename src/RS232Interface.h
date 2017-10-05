// ----------------------------------------------------------------------------
// RS232Interface.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef RS232_INTERFACE_H
#define RS232_INTERFACE_H
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

#include <ModularClient.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "RS232Interface/Constants.h"


class RS232Interface : public ModularDeviceBase
{
public:
  RS232Interface();
  virtual void setup();

private:
  modular_server::Property properties_[rs232_interface::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[rs232_interface::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[rs232_interface::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[rs232_interface::constants::CALLBACK_COUNT_MAX];

  // Handlers

};

#endif
