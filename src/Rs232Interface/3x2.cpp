// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace rs232_interface
{
namespace constants
{
HardwareSerial * rs232_stream_ptrs[RS232_STREAM_COUNT] =
  {
    &Serial2,
  };
const size_t rs232_rx_pins[RS232_STREAM_COUNT] =
  {
    9,
  };

// Interrupts

// Units

// Properties
const long rs232_bauds_default[RS232_STREAM_COUNT] =
  {
   rs232_baud_default,
  };

const ConstantString * const rs232_settings_default[RS232_STREAM_COUNT] =
  {
   rs232_setting_ptr_default,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
