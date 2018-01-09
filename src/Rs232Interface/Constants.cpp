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
CONSTANT_STRING(rs232_bauds_property_name,"rs232Bauds");
const long rs232_baud_min = 300;
const long rs232_baud_max = 1000000;
const long rs232_baud_default = 9600;

CONSTANT_STRING(rs232_settings_property_name,"rs232Settings");
CONSTANT_STRING(rs232_setting_7e1,"7E1");
CONSTANT_STRING(rs232_setting_7o1,"7O1");
CONSTANT_STRING(rs232_setting_8n1,"8N1");
CONSTANT_STRING(rs232_setting_8n2,"8N2");
CONSTANT_STRING(rs232_setting_8e1,"8E1");
CONSTANT_STRING(rs232_setting_8o1,"8O1");
modular_server::SubsetMemberType rs232_setting_ptr_subset[RS232_SETTING_SUBSET_LENGTH] =
  {
    {.cs_ptr=&rs232_setting_7e1},
    {.cs_ptr=&rs232_setting_7o1},
    {.cs_ptr=&rs232_setting_8n1},
    {.cs_ptr=&rs232_setting_8n2},
    {.cs_ptr=&rs232_setting_8e1},
    {.cs_ptr=&rs232_setting_8o1},
  };
const ConstantString * const rs232_setting_ptr_default = &rs232_setting_8n1;

// Parameters

// Functions
CONSTANT_STRING(get_rs232_stream_count_function_name,"getRs232StreamCount");

// Callbacks

// Errors
}
}
