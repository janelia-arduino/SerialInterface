// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace serial_interface
{
namespace constants
{
CONSTANT_STRING(device_name,"serial_interface");

CONSTANT_STRING(firmware_name,"SerialInterface");
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
CONSTANT_STRING(bauds_property_name,"bauds");
modular_server::SubsetMemberType baud_subset[BAUD_SUBSET_LENGTH] =
  {
    {.l=300},
    {.l=1200},
    {.l=2400},
    {.l=4800},
    {.l=9600},
    {.l=19200},
    {.l=31250},
    {.l=38400},
    {.l=57600},
    {.l=115200},
    {.l=230400},
    {.l=250000},
    {.l=460800},
    {.l=500000},
    {.l=921600},
    {.l=1000000},
  };
const long & baud_default = baud_subset[4].l;

CONSTANT_STRING(formats_property_name,"formats");
CONSTANT_STRING(format_7e1,"7E1");
CONSTANT_STRING(format_7o1,"7O1");
CONSTANT_STRING(format_8n1,"8N1");
CONSTANT_STRING(format_8n2,"8N2");
CONSTANT_STRING(format_8e1,"8E1");
CONSTANT_STRING(format_8o1,"8O1");
modular_server::SubsetMemberType format_ptr_subset[FORMAT_SUBSET_LENGTH] =
  {
    {.cs_ptr=&format_7e1},
    {.cs_ptr=&format_7o1},
    {.cs_ptr=&format_8n1},
    {.cs_ptr=&format_8n2},
    {.cs_ptr=&format_8e1},
    {.cs_ptr=&format_8o1},
  };
const ConstantString * const format_ptr_default = &format_8n1;

CONSTANT_STRING(line_endings_property_name,"lineEndings");
CONSTANT_STRING(line_ending_none,"NONE");
CONSTANT_STRING(line_ending_cr,"CR");
CONSTANT_STRING(line_ending_lf,"LF");
CONSTANT_STRING(line_ending_crlf,"CRLF");
modular_server::SubsetMemberType line_ending_ptr_subset[LINE_ENDING_SUBSET_LENGTH] =
  {
    {.cs_ptr=&line_ending_none},
    {.cs_ptr=&line_ending_cr},
    {.cs_ptr=&line_ending_lf},
    {.cs_ptr=&line_ending_crlf},
  };
const ConstantString * const line_ending_ptr_default = &line_ending_lf;

// Parameters
CONSTANT_STRING(serial_stream_index_parameter_name,"serial_stream_index");
const long serial_stream_index_min = 0;

CONSTANT_STRING(data_parameter_name,"data");

// Functions
CONSTANT_STRING(get_serial_stream_count_function_name,"getSerialStreamCount");
CONSTANT_STRING(get_serial_stream_index_function_name,"getSerialStreamIndex");
CONSTANT_STRING(set_serial_stream_index_function_name,"setSerialStreamIndex");
CONSTANT_STRING(write_function_name,"write");
CONSTANT_STRING(write_read_function_name,"writeRead");

// Callbacks

// Errors
}
}
