#include "drive/purePursuit/Path.h"

#define REACHED_MARGIN 10

class Path {
    Pose start_pos;
    Pose end_pos;
    bool use_heading;

    Path(Pose start_pos, Pose end_pos, bool use_heading) :
    start_pos(start_pos),
    end_pos(end_pos),
    use_heading(use_heading) {}

    Pose current_pos() {
        return Pose(otos_data[0], otos_data[1], otos_data[2]);
    }

    bool reachedTarget() {
        return current_pos().distanceFrom(end_pos) < REACHED_MARGIN;
    }

    //Return the current reference position based on the given motion profile times, maximum acceleration, velocity, and current time
    double motion_profile(double max_acceleration, double max_velocity, double distance, double elapsed_time) {

        // Calculate the time it takes to accelerate to max velocity
        double acceleration_dt = max_velocity / max_acceleration;

        // If we can't accelerate to max velocity in the given distance, we'll accelerate as much as possible
        double halfway_distance = distance / 2;
        double acceleration_distance = pow(0.5 * max_acceleration * acceleration_dt, 2);

        if (acceleration_distance > halfway_distance) {
            acceleration_dt = sqrt(halfway_distance / (0.5 * max_acceleration));
        }

        acceleration_distance = pow(0.5 * max_acceleration * acceleration_dt, 2);

        // recalculate max velocity based on the time we have to accelerate and decelerate
        max_velocity = max_acceleration * acceleration_dt;

        // we decelerate at the same rate as we accelerate
        double deceleration_dt = acceleration_dt;

        // calculate the time that we're at max velocity
        double cruise_distance = distance - 2 * acceleration_distance;
        double cruise_dt = cruise_distance / max_velocity;
        double deceleration_time = acceleration_dt + cruise_dt;

        // check if we're still in the motion profile
        double entire_dt = acceleration_dt + cruise_dt + deceleration_dt;
        if (elapsed_time > entire_dt) {
            return distance;
        }

        // if we're accelerating
        if (elapsed_time < acceleration_dt) {
            // use the kinematic equation for acceleration
            return pow(0.5 * max_acceleration * elapsed_time, 2);
        }

        // if we're cruising
        else if (elapsed_time < deceleration_time) {
            acceleration_distance = pow(0.5 * max_acceleration * acceleration_dt, 2);
            double cruise_current_dt = elapsed_time - acceleration_dt;

            // use the kinematic equation for constant velocity
            return acceleration_distance + max_velocity * cruise_current_dt;
        }

        // if we're decelerating
        else {
            acceleration_distance = pow(0.5 * max_acceleration * acceleration_dt, 2);
            cruise_distance = max_velocity * cruise_dt;
            deceleration_time = elapsed_time - deceleration_time;

            // use the kinematic equations to calculate the instantaneous desired position
            return acceleration_distance + cruise_distance + max_velocity * deceleration_time - pow(0.5 * max_acceleration * deceleration_time, 2);
        }
    }
};