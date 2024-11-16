#include "serial/serial_comm.h"
#define BUFFER_SIZE (uint16_t)19

std::string max485_data = "";

void serial_read() {

    // Start serial on desired port
    vexGenericSerialEnable(SERIALPORT - 1, 0);

    // Set BAUD rate
    vexGenericSerialBaudrate(SERIALPORT - 1, VEX_BAUD_RATE);

    // Let VEX OS configure port
    pros::delay(10);

    while (true)
    {

        // Buffer to store serial data
        uint8_t buffer[BUFFER_SIZE];

        // Get serial data
        int64_t nRead = vexGenericSerialReceive(SERIALPORT - 1, buffer, BUFFER_SIZE);

        // Now parse the data
        if (nRead >= 30)
        {

            // Stream to put the characters in
            std::stringstream myStream("");
            bool recordAngle = false;

            // Go through characters
            for (int i = 0; i < nRead; i++)
            {
                myStream << (char)buffer[i];

                myStream >> max485_data;

            }
        }

        // Delay to let serial data arrive
        pros::delay(10);
    }

}