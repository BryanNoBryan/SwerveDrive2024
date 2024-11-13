#include "init/devices.h"

// Controllers
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain motors
// In each swerve wheel there are two motors, one motor has a gear on the top and the other has a gear on the bottom
// So leftFrontTopMotor would refer to the motor that is in the left and front of the robot and the motor who's gear is on top
// This logic extends to the other motors

// Left Front
pros::Motor leftFrontTopMotor(1, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::Motor leftFrontBottomMotor(2, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

pros::MotorGroup leftFrontForward({1, -2}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::MotorGroup leftFrontRotate({1, 2}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);


// Left Back
pros::Motor leftBackTopMotor(3, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::Motor leftBackBottomMotor(4, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

pros::MotorGroup leftBackForward({3, -4}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::MotorGroup leftBackRotate({3, 3}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// Temporary
pros::MotorGroup driveLeft({1,-2, 3, -4}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);



// Right Front
pros::Motor rightFrontTopMotor(14, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::Motor rightFrontBottomMotor(15, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

pros::MotorGroup rightFrontForward({14, -15}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::MotorGroup rightFrontRotate({14, 15}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// Right Back
pros::Motor rightBackTopMotor(7, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::Motor rightBackBottomMotor(8, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

pros::MotorGroup rightBackForward({7, -8}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);
pros::MotorGroup rightBackRotate({7, 8}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);

// Temporary
pros::MotorGroup driveRight({5, -6, 7, -8}, pros::v5::MotorGears::green, pros::v5::MotorEncoderUnits::degrees);


// Sensors
pros::Rotation rightFrontEncoder(9);
pros::Rotation leftFrontEncoder(10);
pros::Rotation leftBackEncoder(11);
pros::Rotation rightBackEncoder(12);

pros::Imu imu(20);