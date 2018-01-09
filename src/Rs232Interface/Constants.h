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
enum{PROPERTY_COUNT_MAX=4};
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
extern ConstantString baud_rates_property_name;
extern const long baud_rate_min;
extern const long baud_rate_max;
extern const long baud_rate_default;

extern ConstantString data_bits_property_name;
enum{DATA_BITS_SUBSET_LENGTH=4};
extern modular_server::SubsetMemberType data_bits_subset[DATA_BITS_SUBSET_LENGTH];
extern const long data_bits_element_default;

extern ConstantString parities_property_name;
enum{PARITY_SUBSET_LENGTH=3};
extern ConstantString parity_none;
extern ConstantString parity_even;
extern ConstantString parity_odd;
extern modular_server::SubsetMemberType parity_ptr_subset[PARITY_SUBSET_LENGTH];
extern const ConstantString * const parity_ptr_default;

extern ConstantString stop_bits_property_name;
enum{STOP_BITS_SUBSET_LENGTH=2};
extern modular_server::SubsetMemberType stop_bits_subset[STOP_BITS_SUBSET_LENGTH];
extern const long stop_bits_element_default;

// Parameters

// Functions

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
