#include "init/devices.h"

// Controllers
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain motors
// In each swerve wheel there are two motors, one motor has a gear on the top and the other has a gear on the bottom
// So leftFrontTopMotor would refer to the motor that is in the left and front of the robot and the motor who's gear is on top
// This logic extends to the other motors

//PORTS
/*
Bottom Motor, Top Motor, Encoder

Top Left: 1 2 3
Bottom left: 11 12 13

Top Right: 10 9 8
Bottom Right: 20 19 18
*/


// Left Front
pros::Motor leftFrontTopMotor(-4, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::Motor leftFrontBottomMotor(-5, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// pros::MotorGroup leftFrontForward({1, -2}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
// pros::MotorGroup leftFrontRotate({1, 2}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);


// Left Back
pros::Motor leftBackTopMotor(12, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::Motor leftBackBottomMotor(11, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// pros::MotorGroup leftBackForward({3, -4}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
// pros::MotorGroup leftBackRotate({3, 4}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// Temporary
pros::MotorGroup driveLeft({1,-2, 3, -4}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);


// Right Front
pros::Motor rightFrontTopMotor(-9, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::Motor rightFrontBottomMotor(-10, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// pros::MotorGroup rightFrontForward({14, -15}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
// pros::MotorGroup rightFrontRotate({14, 15}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// Right Back
pros::Motor rightBackTopMotor(19, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::Motor rightBackBottomMotor(20, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// pros::MotorGroup rightBackForward({7, -8}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
// pros::MotorGroup rightBackRotate({7, 8}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// Temporary
pros::MotorGroup driveRight({5, -6, 7, -8}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);


// Sensors
pros::Rotation leftFrontEncoder(-3);
pros::Rotation leftBackEncoder(13);
pros::Rotation rightFrontEncoder(-8);
pros::Rotation rightBackEncoder(18);

pros::Motor intake(13, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

pros::Imu imu(20);