#include "serial/serial_comm.h"
#define BUFFER_SIZE (uint16_t)80

// Initialize data buffer
std::string max485_data = "";
float otos_data[9];
float otos_offset[3];

float otos_x;
float otos_y;
float otos_heading;

void serial_read(void *params) {

    // Reset data buffer after each call
    max485_data = "";

    // Start serial on desired port
    vexGenericSerialEnable(SERIALPORT - 1, 0);

    // Set BAUD rate
    vexGenericSerialBaudrate(SERIALPORT - 1, VEX_BAUD_RATE);

    // Buffer to store serial data
    uint8_t buffer[BUFFER_SIZE];

    // Get serial data
    int32_t nRead = vexGenericSerialReceive(SERIALPORT - 1, buffer, BUFFER_SIZE);
    // Now parse the data

    std::stringstream data_stream("");
    int index = 0;
    bool record_data = true;

    if (nRead >= 80) {
        // Go through characters
        for (int i = 0; i < nRead; i++) {
            if (max485_data.size() >= 5 && max485_data.substr(0, 5) == "VEXPX")
            {
                if (std::isalpha((char)buffer[i]) && record_data) {
                    record_data = false;
                    float temp;
                    data_stream >> temp;
                    data_stream.clear();
                    otos_data[index++] = temp;

                }
                else if (std::isalpha((char)buffer[i]) && !record_data)
                    record_data = false;
                else
                    record_data = true;

                if(record_data)
                    data_stream << (char)buffer[i];
            }
            max485_data += (char)buffer[i];

        }
    }

    otos_x = otos_data[0] + otos_offset[0];
    otos_y = otos_data[1] + otos_offset[1];
    otos_heading = otos_data[2] + otos_offset[2];
}