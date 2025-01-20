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

// Prototypes for hidden vex functions to bypass PROS bug
extern "C" int32_t vexGenericSerialReceive(uint32_t index, uint8_t *buffer, int32_t length);
extern "C" void vexGenericSerialEnable(uint32_t index, uint32_t nu);
extern "C" void vexGenericSerialBaudrate(uint32_t index, uint32_t rate);

extern pros::adi::DigitalOut rxtx_enable;

// Sensors
extern pros::Imu imu;

#endif