// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
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

// Pins

// Units

// Properties
const long bauds_default[SERIAL_STREAM_COUNT] =
{
  baud_default,
  baud_default,
};

const ConstantString * const formats_default[SERIAL_STREAM_COUNT] =
{
  format_ptr_default,
  format_ptr_default,
};

const ConstantString * const write_line_endings_default[SERIAL_STREAM_COUNT] =
{
  write_line_ending_ptr_default,
  write_line_ending_ptr_default,
};

const ConstantString * const read_line_endings_default[SERIAL_STREAM_COUNT] =
{
  read_line_ending_ptr_default,
  read_line_ending_ptr_default,
};

const long timeouts_default[SERIAL_STREAM_COUNT] =
{
  timeout_default,
  timeout_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
