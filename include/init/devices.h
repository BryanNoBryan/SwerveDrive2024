#ifndef _DEVICES
#define _DEVICES

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

// Port to use for serial data
#define SERIALPORT 7

#include "api.h"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include <sstream>

// Controllers
extern pros::Controller controller;

// Drivetrain encoders
extern pros::Rotation rightFrontEncoder;
extern pros::Rotation leftFrontEncoder;
extern pros::Rotation leftBackEncoder;
extern pros::Rotation rightBackEncoder;

// Drivetrain motors & MotorGroups

// Left Front
extern pros::Motor leftFrontTopMotor;
extern pros::Motor leftFrontBottomMotor;

// Left Back
extern pros::Motor leftBackTopMotor;
extern pros::Motor leftBackBottomMotor;

// Temporary
extern pros::MotorGroup driveLeft;

// Right Front
extern pros::Motor rightFrontTopMotor;
extern pros::Motor rightFrontBottomMotor;

// Right Back
extern pros::Motor rightBackTopMotor;
extern pros::Motor rightBackBottomMotor;

// Temporary
extern pros::MotorGroup driveRight;

// Prototypes for hidden vex functions to bypass PROS bug
extern "C" int32_t vexGenericSerialReceive(uint32_t index, uint8_t *buffer, int32_t length);
extern "C" void vexGenericSerialEnable(uint32_t index, uint32_t nu);
extern "C" void vexGenericSerialBaudrate(uint32_t index, uint32_t rate);

extern pros::adi::DigitalOut rxtx_enable;

// Intake
extern pros::Motor intake;

//Lift
extern pros::Motor liftLeft;
extern pros::Motor liftRight;

extern pros::MotorGroup lift;

//Bucket
extern pros::Motor bucket;

// Sensors
extern pros::Imu imu;

extern pros::adi::Potentiometer leftPot;
extern pros::adi::Potentiometer rightPot;

extern pros::Optical mogoOptical;

//MogoClamp
extern pros::adi::Pneumatics mogoClamp;

#endif