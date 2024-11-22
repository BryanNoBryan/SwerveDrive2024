#ifndef _DEVICES
#define _DEVICES

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"

// Controllers
extern pros::Controller controller;

// Drivetrain motors & MotorGroups

// Left Front
extern pros::Motor leftFrontTopMotor;
extern pros::Motor leftFrontBottomMotor;

extern pros::MotorGroup leftFrontForward;
extern pros::MotorGroup leftFrontRotate;


// Left Back
extern pros::Motor leftBackTopMotor;
extern pros::Motor leftBackBottomMotor;

extern pros::MotorGroup leftBackForward;
extern pros::MotorGroup leftBackRotate;

// Temporary
extern pros::MotorGroup driveLeft;


// Right Front
extern pros::Motor rightFrontTopMotor;
extern pros::Motor rightFrontBottomMotor;

extern pros::MotorGroup rightFrontForward;
extern pros::MotorGroup rightFrontRotate;


// Right Back
extern pros::Motor rightBackTopMotor;
extern pros::Motor rightBackBottomMotor;

extern pros::MotorGroup rightBackForward;
extern pros::MotorGroup rightBackRotate;

// Temporary
extern pros::MotorGroup driveRight;

// Sensors
extern pros::Imu imu;

// Intake
extern pros::Motor intakeLeft;
extern pros::Motor intakeRight;

//Lift
extern pros::Motor liftLeft;
extern pros::Motor liftRight;

#endif