#ifndef _DEVICES
#define _DEVICES


#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"


//Controllers
extern pros::Controller controller;

//Motors
extern pros::Motor rightFrontTopMotor;
extern pros::Motor rightFrontBottomMotor;
extern pros::Motor leftFrontTopMotor;
extern pros::Motor leftFrontBottomMotor;
extern pros::Motor leftBackTopMotor;
extern pros::Motor leftBackBottomMotor;
extern pros::Motor rightBackTopMotor;
extern pros::Motor rightBackBottomMotor;

extern pros::Rotation rightFrontEncoder;
extern pros::Rotation leftFrontEncoder;
extern pros::Rotation leftBackEncoder;
extern pros::Rotation rightBackEncoder;


extern pros::Motor fourBar;


//Sensors
extern pros::Imu imu;


#endif
