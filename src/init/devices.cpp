#include "init/devices.h"

// Controllers
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain motors
// In each swerve wheel there are two motors, one motor has a gear on the top and the other has a gear on the bottom
// So leftFrontTopMotor would refer to the motor that is in the left and front of the robot and the motor who's gear is on top
// This logic extends to the other motors

// Left Front
pros::Motor leftFrontTopMotor(9, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor leftFrontBottomMotor(10, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// Left Back
pros::Motor leftBackTopMotor(1, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor leftBackBottomMotor(2, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// Right Front
pros::Motor rightFrontTopMotor(4, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor rightFrontBottomMotor(5, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// Right Back
pros::Motor rightBackTopMotor(6, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor rightBackBottomMotor(7, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// Temporary
pros::MotorGroup driveLeft({1,-2, 3, -4}, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// Temporary
pros::MotorGroup driveRight({5, -6, 7, -8}, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// Sensors
pros::Rotation leftFrontEncoder(-19);
pros::Rotation leftBackEncoder(13);
pros::Rotation rightFrontEncoder(-3);
pros::Rotation rightBackEncoder(18);


//Intake
pros::Motor intakeLeft(14, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor intakeRight(15, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

pros::MotorGroup intake({14, -15}, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// Enables serial communication between the vex brain and arduino by sending a 5V DC signal
pros::adi::DigitalOut rxtx_enable('A');

// Sensors
pros::Imu imu(9);

//Lift
pros::Motor liftLeftTop(8, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor liftLeftBottom(20, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

pros::Motor liftRightTop(11, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::Motor liftRightBottom(12, pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

//Mogo Clamp
pros::adi::Pneumatics clampLeft('C', true, false);
pros::adi::Pneumatics clampRight('C', true, false);