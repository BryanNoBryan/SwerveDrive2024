#include "autons/matchAuton.h"
#include "drive/purePursuit/purePursuit.h"
#include "serial/serial_comm.h"

void matchAuton(){
    rxtx_enable.set_value(true);
    serial_read(NULL);

    purePursuit purePursuit;
    
    vector<PPoint> path = vector<PPoint>();
    path.push_back(PPoint(0, 12.0, 0.0));
    path.push_back(PPoint(-40.0, 24.0, 0.0));
    path.push_back(PPoint(-80.0, 40.0, 0.0));
    path.push_back(PPoint(-80.0, 80.0, 0.0));
    purePursuit.runPath(path, 1000);
}