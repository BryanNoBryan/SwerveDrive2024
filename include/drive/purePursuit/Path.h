#ifndef _PATH_
#define _PATH_

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "init/devices.h"
#include "lemlib/api.hpp"
#include <cmath>
#include "init/utility.h"
#include "drive/SwerveDrive.h"
// #include "serial/serial_comm.h"
#include "drive/purePursuit/Pose.h"

#define REACHED_MARGIN 1

class Path {
    public:
        Pose start_pos;
        Pose end_pos;
        bool use_heading;

        Path() {}

        Path(Pose start_pos, Pose end_pos, bool use_heading) :
        start_pos(start_pos),
        end_pos(end_pos),
        use_heading(use_heading) {}

        Pose current_pos();
        bool reachedTarget(Pose current_pos);

        //Return the current reference position based on the given motion profile times, maximum acceleration, velocity, and current time
        double motion_profile(double max_acceleration, double max_velocity, double distance, double elapsed_time);
};

#endif