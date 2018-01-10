// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace serial_interface
{
namespace constants
{
HardwareSerial * serial_stream_ptrs[SERIAL_STREAM_COUNT] =
  {
    &Serial2,
  };
const size_t serial_rx_pins[SERIAL_STREAM_COUNT] =
  {
    9,
  };

// Interrupts

// Units

// Properties
const long serial_bauds_default[SERIAL_STREAM_COUNT] =
  {
   serial_baud_default,
  };

const ConstantString * const serial_settings_default[SERIAL_STREAM_COUNT] =
  {
   serial_setting_ptr_default,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
