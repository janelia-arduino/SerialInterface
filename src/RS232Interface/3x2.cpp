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
const long baud_rates_default[RS232_STREAM_COUNT] =
  {
   baud_rate_default,
  };

const long data_bits_default[RS232_STREAM_COUNT] =
  {
   data_bits_element_default,
  };

const ConstantString * const parities_default[RS232_STREAM_COUNT] =
  {
   parity_ptr_default,
  };

const long stop_bits_default[RS232_STREAM_COUNT] =
  {
   stop_bits_element_default,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
