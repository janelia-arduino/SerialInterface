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

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
