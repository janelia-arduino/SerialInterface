// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace rs232_interface
{
namespace constants
{
CONSTANT_STRING(device_name,"rs232_interface");

CONSTANT_STRING(firmware_name,"RS232Interface");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
    .name_ptr=&firmware_name,
    .version_major=1,
    .version_minor=0,
    .version_patch=0,
  };

// Interrupts

// Units

// Properties
CONSTANT_STRING(baud_rates_property_name,"baudRates");
const long baud_rate_min = 300;
const long baud_rate_max = 1000000;
const long baud_rate_default = 9600;

CONSTANT_STRING(data_bits_property_name,"dataBits");
modular_server::SubsetMemberType data_bits_subset[DATA_BITS_SUBSET_LENGTH] =
  {
    {.l=5},
    {.l=6},
    {.l=7},
    {.l=8},
  };
const long data_bits_element_default = 8;

// Parameters

// Functions

// Callbacks

// Errors
}
}
