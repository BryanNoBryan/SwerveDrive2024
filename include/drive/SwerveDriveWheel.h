#ifndef _SWERVE_DRIVE_WHEEL
#define _SWERVE_DRIVE_WHEEL

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "init/devices.h"
#include "lemlib/api.hpp"

#include "lemlib/pid.hpp"

#include "init/utility.h"
#include <cmath>

class SwerveDriveWheel
{
public:
    //motor1 is top
    //motor2 is bottom
    pros::Motor* motor1;
    pros::Motor* motor2;
    //  ASSUMPTIONS:
    //motor encoder is built-in
    //in-built motor PID should be sufficent for differential swerve

    pros::Rotation rotateEncoder;
    //PID for rotation
    lemlib::PID PIDr;
    bool reverseRotEncoder;

    //rotation angle in deg, for PID
    double current_r;
    double target_r;

    SwerveDriveWheel(pros::Motor* motor1, pros::Motor* motor2, pros::Rotation rotateEncoder, lemlib::PID &pid, bool reverseRotEncoder = false);

    double getAngle();
    
    /** Zeroes the wheel by updating the offset, and returns the new offset */
    void zero();

    void move(double speed, double angle, double power);
};

#endif