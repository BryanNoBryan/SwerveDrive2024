#ifndef SERIAL_COMM
#define SERIAL_COMM

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"

// The bits per second that will be sent on the serial bus
#define VEX_BAUD_RATE 115200U

// Function that updates data buffer from reading the serial bus
void serial_read();

// Global data buffer
extern std::string max485_data;

#endif