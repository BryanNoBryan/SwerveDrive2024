#include "autons/matchAuton.h"
#include "drive/purePursuit/purePursuit.h"


void matchAuton(){
    purePursuit purePursuit;

    vector<PPoint> path = vector<PPoint>();
    path.push_back(PPoint(0, 12.0, 0.0));
    path.push_back(PPoint(-40.0, 24.0, 0.0));
    path.push_back(PPoint(-80.0, 40.0, 0.0));
    path.push_back(PPoint(-80.0, 80.0, 0.0));
    purePursuit.runPath(path, 1000);
}