#include "drive/purePursuit/Path.h"

Pose Path::current_pos() {
    rxtx_enable.set_value(HIGH);
    serial_read(nullptr);

    return Pose(-otos_data[0], -otos_data[1], -otos_data[2]);
}

bool Path::reachedTarget(Pose current_pos) {
    printf("distance %f\n", current_pos.distanceFrom(end_pos));
    return current_pos.distanceFrom(end_pos) < REACHED_MARGIN;
}

//Return the current reference position based on the given motion profile times, maximum acceleration, velocity, and current time
double Path::motion_profile(double max_acceleration, double max_velocity, double distance, double elapsed_time) {

    if(distance < 0){
        max_velocity *= -1;
        max_acceleration *= -1;
    }

    // Calculate the time it takes to accelerate to max velocity
    double acceleration_dt = max_velocity / max_acceleration;

    // If we can't accelerate to max velocity in the given distance, we'll accelerate as much as possible
    double halfway_distance = distance / 2;
    double acceleration_distance = 0.5 * max_acceleration * pow(acceleration_dt, 2);

    if (acceleration_distance > halfway_distance) {
        acceleration_dt = sqrt(halfway_distance / (0.5 * max_acceleration));
    }

    acceleration_distance = 0.5 * max_acceleration * pow(acceleration_dt, 2);

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
        return 0.5 * max_acceleration * pow(acceleration_dt, 2);
    }

    // if we're cruising
    else if (elapsed_time < deceleration_time) {
        acceleration_distance = 0.5 * max_acceleration * pow(acceleration_dt, 2);
        double cruise_current_dt = elapsed_time - acceleration_dt;

        // use the kinematic equation for constant velocity
        return acceleration_distance + max_velocity * cruise_current_dt;
    }

    // if we're decelerating
    else {
        acceleration_distance = 0.5 * max_acceleration * pow(acceleration_dt, 2);
        cruise_distance = max_velocity * cruise_dt;
        deceleration_time = elapsed_time - deceleration_time;

        // use the kinematic equations to calculate the instantaneous desired position
        return acceleration_distance + cruise_distance + max_velocity * deceleration_time - 0.5 * max_acceleration * pow(acceleration_dt, 2);
    }
}