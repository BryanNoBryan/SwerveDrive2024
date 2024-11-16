#include "serial/serial_comm.h"
#define BUFFER_SIZE (uint16_t)22

// Initialize data buffer
std::string max485_data = "";

void serial_read() {

    // Reset data buffer after each call
    max485_data = "";

    // Start serial on desired port
    vexGenericSerialEnable(SERIALPORT - 1, 0);

    // Set BAUD rate
    vexGenericSerialBaudrate(SERIALPORT - 1, VEX_BAUD_RATE);

    // Let VEX OS configure port
    pros::delay(10);


    // Buffer to store serial data
    uint8_t buffer[BUFFER_SIZE];

    // Get serial data
    int32_t nRead = vexGenericSerialReceive(SERIALPORT - 1, buffer, BUFFER_SIZE);

    // Now parse the data
    if (nRead >= 21) {

        // Go through characters
        for (int i = 0; i < nRead; i++) {
            max485_data += (char)buffer[i];
        }
    }

    // Delay to let serial data arrive
    pros::delay(10);

}