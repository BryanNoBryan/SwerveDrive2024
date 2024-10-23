#ifndef _DRIVETRAIN
#define _DRIVETRAIN

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "lemlib/api.hpp"
#include "init/devices.h"
#include "lemlib/chassis/chassis.hpp"

float customDriveCurve(float input, float scale);

// Drivetrain
extern lemlib::Drivetrain drivetrain;

// Odometry
extern lemlib::TrackingWheel horizontal;

extern lemlib::OdomSensors sensors;

// PID
extern lemlib::ControllerSettings lateralController;
extern lemlib::ControllerSettings angularController;

// Putting it all together
extern lemlib::Chassis chassis;

#endif