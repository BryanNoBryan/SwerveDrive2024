#ifndef _POSE
#define _POSE

#include "init/devices.h"
#include "lemlib/api.hpp"
#include <cmath>
#include "init/utility.h"
#include "drive/SwerveDrive.h"
#include "serial/serial_comm.h"
#include "drive/purePursuit/Pose.h"

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS


class Pose {
    public:
        double x, y, theta;

        Pose(double x, double y, double theta);

        double getX();
        double getY();
        double getTheta();
        double distanceFrom(Pose pose);
        Pose vectorDiff(Pose pose);
        double length();
        static Pose current_pos();
};

#endif