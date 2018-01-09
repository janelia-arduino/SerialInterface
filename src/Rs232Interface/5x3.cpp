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
const long baud_rates_default[RS232_STREAM_COUNT] =
  {
   baud_rate_default,
   baud_rate_default,
  };

const long data_bits_default[RS232_STREAM_COUNT] =
  {
   data_bits_element_default,
   data_bits_element_default,
  };

const ConstantString * const parities_default[RS232_STREAM_COUNT] =
  {
   parity_ptr_default,
   parity_ptr_default,
  };

const long stop_bits_default[RS232_STREAM_COUNT] =
  {
   stop_bits_element_default,
   stop_bits_element_default,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
