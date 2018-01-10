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
enum{PROPERTY_COUNT_MAX=2};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=1};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString serial_bauds_property_name;
enum{SERIAL_BAUD_SUBSET_LENGTH=16};
extern modular_server::SubsetMemberType serial_baud_subset[SERIAL_BAUD_SUBSET_LENGTH];
extern const long & serial_baud_default;

extern ConstantString serial_settings_property_name;
enum{SERIAL_SETTING_SUBSET_LENGTH=6};
extern ConstantString serial_setting_7e1;
extern ConstantString serial_setting_7o1;
extern ConstantString serial_setting_8n1;
extern ConstantString serial_setting_8n2;
extern ConstantString serial_setting_8e1;
extern ConstantString serial_setting_8o1;
extern modular_server::SubsetMemberType serial_setting_ptr_subset[SERIAL_SETTING_SUBSET_LENGTH];
extern const ConstantString * const serial_setting_ptr_default;

// Parameters

// Functions
extern ConstantString get_serial_stream_count_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
