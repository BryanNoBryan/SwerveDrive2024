#include "autons/matchAuton.h"
#include "serial/serial_comm.h"


void matchAuton() {
    rxtx_enable.set_value(true);
    serial_read(NULL);

}