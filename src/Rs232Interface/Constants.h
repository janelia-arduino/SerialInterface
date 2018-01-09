// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef RS232_INTERFACE_CONSTANTS_H
#define RS232_INTERFACE_CONSTANTS_H
#include <ConstantVariable.h>
#include <ModularServer.h>


namespace rs232_interface
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
extern ConstantString rs232_bauds_property_name;
extern const long rs232_baud_min;
extern const long rs232_baud_max;
extern const long rs232_baud_default;

extern ConstantString rs232_settings_property_name;
enum{RS232_SETTING_SUBSET_LENGTH=6};
extern ConstantString rs232_setting_7e1;
extern ConstantString rs232_setting_7o1;
extern ConstantString rs232_setting_8n1;
extern ConstantString rs232_setting_8n2;
extern ConstantString rs232_setting_8e1;
extern ConstantString rs232_setting_8o1;
extern modular_server::SubsetMemberType rs232_setting_ptr_subset[RS232_SETTING_SUBSET_LENGTH];
extern const ConstantString * const rs232_setting_ptr_default;

// Parameters

// Functions
extern ConstantString get_rs232_stream_count_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
