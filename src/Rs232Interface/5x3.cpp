// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace rs232_interface
{
namespace constants
{
HardwareSerial * rs232_stream_ptrs[RS232_STREAM_COUNT] =
  {
    &Serial5,
    &Serial6,
  };
const size_t rs232_rx_pins[RS232_STREAM_COUNT] =
  {
    34,
    47,
  };

// Interrupts

// Units

// Properties
const long rs232_bauds_default[RS232_STREAM_COUNT] =
  {
   rs232_baud_default,
   rs232_baud_default,
  };

const ConstantString * const rs232_settings_default[RS232_STREAM_COUNT] =
  {
   rs232_setting_ptr_default,
   rs232_setting_ptr_default,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
