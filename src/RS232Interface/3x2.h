// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef RS232_INTERFACE_3X2_CONSTANTS_H
#define RS232_INTERFACE_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace rs232_interface
{
namespace constants
{
enum{RS232_STREAM_COUNT=1};

extern HardwareSerial * rs232_stream_ptrs[RS232_STREAM_COUNT];
extern const size_t rs232_rx_pins[RS232_STREAM_COUNT];

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long baud_rates_default[RS232_STREAM_COUNT];

extern const long data_bits_default[RS232_STREAM_COUNT];

extern const ConstantString * const parities_default[RS232_STREAM_COUNT];

extern const long stop_bits_default[RS232_STREAM_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
