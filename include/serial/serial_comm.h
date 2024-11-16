#ifndef SERIAL_COMM
#define SERIAL_COMM

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "pros/misc.h"

#define VEX_BAUD_RATE 115200U

void serial_read();

extern std::string max485_data;

#endif