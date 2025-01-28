#include "init/devices.h"
#include "pros/adi.hpp"

// Controllers
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain motors
// In each swerve wheel there are two motors, one motor has a gear on the top and the other has a gear on the bottom
// So leftFrontTopMotor would refer to the motor that is in the left and front of the robot and the motor who's gear is on top
// This logic extends to the other motors

// Left Front
pros::Motor leftFrontTopMotor(11, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor leftFrontBottomMotor(14, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// Left Back
pros::Motor leftBackTopMotor(13, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor leftBackBottomMotor(15, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// Right Front
pros::Motor rightFrontTopMotor(20, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor rightFrontBottomMotor(17, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// Right Back
pros::Motor rightBackTopMotor(16, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor rightBackBottomMotor(19, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

//Intake
pros::Motor intake(-5, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// Enables serial communication between the vex brain and arduino by sending a 5V DC signal
pros::adi::DigitalOut rxtx_enable('E');

//Lift
pros::Motor liftLeft(-4, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::Motor liftRight(8, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

pros::MotorGroup lift({-4, 8}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

pros::Motor bucket(2, pros::v5::MotorGears::red, pros::v5::MotorEncoderUnits::degrees);

// Sensors
pros::Rotation leftFrontEncoder(1);
pros::Rotation leftBackEncoder(-6);
pros::Rotation rightFrontEncoder(10);
pros::Rotation rightBackEncoder(-9);

pros::Imu imu(7);

pros::Optical mogoOptical(12);

pros::adi::Potentiometer leftPot('D', pros::E_ADI_POT_EDR);
pros::adi::Potentiometer rightPot('B', pros::E_ADI_POT_EDR);

//Mogo Clamp
pros::adi::Pneumatics mogoClamp('C', false, false);
