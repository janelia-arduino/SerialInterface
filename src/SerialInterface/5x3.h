// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef SERIAL_INTERFACE_5X3_CONSTANTS_H
#define SERIAL_INTERFACE_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__MK64FX512__)

namespace serial_interface
{
namespace constants
{
enum{SERIAL_STREAM_COUNT=2};

extern HardwareSerial * serial_stream_ptrs[SERIAL_STREAM_COUNT];
extern const size_t serial_rx_pins[SERIAL_STREAM_COUNT];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long bauds_default[SERIAL_STREAM_COUNT];

extern const ConstantString * const formats_default[SERIAL_STREAM_COUNT];

extern const ConstantString * const line_endings_default[SERIAL_STREAM_COUNT];

extern const long timeouts_default[SERIAL_STREAM_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
