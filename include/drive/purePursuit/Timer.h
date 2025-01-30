#ifndef _TIMER
#define _TIMER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "init/devices.h"
#include "lemlib/api.hpp"
#include <cmath>
#include "init/utility.h"
#include "drive/SwerveDrive.h"
#include "serial/serial_comm.h"
#include "drive/purePursuit/Pose.h"

using namespace std;

class Timer {
    double start_time;

    void start();

    double elapsed_time();
};

#endif