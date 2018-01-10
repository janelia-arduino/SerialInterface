// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace serial_interface
{
namespace constants
{
HardwareSerial * serial_stream_ptrs[SERIAL_STREAM_COUNT] =
  {
    &Serial5,
    &Serial6,
  };
const size_t serial_rx_pins[SERIAL_STREAM_COUNT] =
  {
    34,
    47,
  };

// Interrupts

// Units

// Properties
const long serial_bauds_default[SERIAL_STREAM_COUNT] =
  {
   serial_baud_default,
   serial_baud_default,
  };

const ConstantString * const serial_settings_default[SERIAL_STREAM_COUNT] =
  {
   serial_setting_ptr_default,
   serial_setting_ptr_default,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
