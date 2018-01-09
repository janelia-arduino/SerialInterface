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

CONSTANT_STRING(firmware_name,"Rs232Interface");
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
    {.l=7},
    {.l=8},
  };
const long data_bits_element_default = 8;

CONSTANT_STRING(parities_property_name,"parities");
CONSTANT_STRING(parity_property_name,"parity");
CONSTANT_STRING(parity_none,"NONE");
CONSTANT_STRING(parity_even,"EVEN");
CONSTANT_STRING(parity_odd,"ODD");
modular_server::SubsetMemberType parity_ptr_subset[PARITY_SUBSET_LENGTH] =
  {
    {.cs_ptr=&parity_none},
    {.cs_ptr=&parity_even},
    {.cs_ptr=&parity_odd},
  };
const ConstantString * const parity_ptr_default = &parity_none;

CONSTANT_STRING(stop_bits_property_name,"stopBits");
modular_server::SubsetMemberType stop_bits_subset[STOP_BITS_SUBSET_LENGTH] =
  {
    {.l=1},
    {.l=2},
  };
const long stop_bits_element_default = 1;

// Parameters

// Functions
CONSTANT_STRING(get_rs232_stream_count_function_name,"getRs232StreamCount");

// Callbacks

// Errors
}
}
