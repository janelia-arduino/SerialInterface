// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef SERIAL_INTERFACE_3X2_CONSTANTS_H
#define SERIAL_INTERFACE_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace serial_interface
{
namespace constants
{
enum{SERIAL_STREAM_COUNT=1};

extern HardwareSerial * serial_stream_ptrs[SERIAL_STREAM_COUNT];
extern const size_t serial_rx_pins[SERIAL_STREAM_COUNT];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long bauds_default[SERIAL_STREAM_COUNT];

extern const ConstantString * const formats_default[SERIAL_STREAM_COUNT];

extern const ConstantString * const write_line_endings_default[SERIAL_STREAM_COUNT];

extern const ConstantString * const read_line_endings_default[SERIAL_STREAM_COUNT];

extern const long timeouts_default[SERIAL_STREAM_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
