// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SERIAL_INTERFACE_CONSTANTS_H
#define SERIAL_INTERFACE_CONSTANTS_H
#include <ConstantVariable.h>
#include <ModularServer.h>


namespace serial_interface
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=3};
enum{PARAMETER_COUNT_MAX=2};
enum{FUNCTION_COUNT_MAX=5};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString bauds_property_name;
enum{BAUD_SUBSET_LENGTH=16};
extern modular_server::SubsetMemberType baud_subset[BAUD_SUBSET_LENGTH];
extern const long & baud_default;

extern ConstantString formats_property_name;
enum{FORMAT_SUBSET_LENGTH=6};
extern ConstantString format_7e1;
extern ConstantString format_7o1;
extern ConstantString format_8n1;
extern ConstantString format_8n2;
extern ConstantString format_8e1;
extern ConstantString format_8o1;
extern modular_server::SubsetMemberType format_ptr_subset[FORMAT_SUBSET_LENGTH];
extern const ConstantString * const format_ptr_default;

extern ConstantString line_endings_property_name;
enum{LINE_ENDING_SUBSET_LENGTH=4};
extern ConstantString line_ending_none;
extern ConstantString line_ending_cr;
extern ConstantString line_ending_lf;
extern ConstantString line_ending_crlf;
extern modular_server::SubsetMemberType line_ending_ptr_subset[LINE_ENDING_SUBSET_LENGTH];
extern const ConstantString * const line_ending_ptr_default;

// Parameters
extern ConstantString serial_stream_index_parameter_name;
extern const long serial_stream_index_min;

extern ConstantString data_parameter_name;

// Functions
extern ConstantString get_serial_stream_count_function_name;
extern ConstantString get_serial_stream_index_function_name;
extern ConstantString set_serial_stream_index_function_name;
extern ConstantString write_function_name;
extern ConstantString write_read_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
