#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"

// The bits per second that will be sent on the serial bus
#define VEX_BAUD_RATE 115200U

// Function that updates data buffer from reading the serial bus
void serial_read(void* params);

// Global data buffer
extern std::string max485_data;

extern float otos_data[9];
extern float otos_offset[3];

extern float otos_x;
extern float otos_y;
extern float otos_heading;

// [0] -> pos_x
// [1] -> pos_y
// [2] -> pos_h
// [3] -> vel_x
// [4] -> vel_y
// [5] -> vel_h
// [6] -> accel_x
// [7] -> accel_y
// [8] -> accel_h

#endif