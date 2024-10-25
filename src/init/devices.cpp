#include "devices.h"
#include "main.h"
#include "api.h"

#define rightFrontTop 1
#define rightFrontBottom 2
#define leftFrontTop 3
#define leftFrontBottom 4
#define leftBackTop 5
#define leftBackBottom 6
#define rightBackTop 7 
#define rightBackBottom 8

#define rightFrontEncoderPort 9
#define leftFrontEncoderPort 10
#define leftBackEncoderPort 11
#define rightBackEncoderPort 12

#define FOUR_BAR 14

#define IMU 13

pros::Controller controller (CONTROLLER_MASTER);

//Drivetrain motors
pros::Motor rightFrontTopMotor (rightFrontTop, pros::v5::MotorGears::green, pros::MotorUnits::deg);
pros::Motor rightFrontBottomMotor (rightFrontBottom, pros::v5::MotorGears::green, pros::MotorUnits::deg);
pros::Motor leftFrontTopMotor (leftFrontTop, pros::v5::MotorGears::green, pros::MotorUnits::deg);
pros::Motor leftFrontBottomMotor (leftFrontBottom, pros::v5::MotorGears::green, pros::MotorUnits::deg);
pros::Motor leftBackTopMotor (leftBackTop, pros::v5::MotorGears::green, pros::MotorUnits::deg);
pros::Motor leftBackBottomMotor (leftBackBottom, pros::v5::MotorGears::green, pros::MotorUnits::deg);
pros::Motor rightBackTopMotor (rightBackTop, pros::v5::MotorGears::green, pros::MotorUnits::deg);
pros::Motor rightBackBottomMotor (rightBackBottom, pros::v5::MotorGears::green, pros::MotorUnits::deg);
//Drivetrain encoders
pros::Rotation rightFrontEncoder(rightFrontEncoderPort);
pros::Rotation leftFrontEncoder(leftFrontEncoderPort);
pros::Rotation leftBackEncoder(leftBackEncoderPort);
pros::Rotation rightBackEncoder(rightBackEncoderPort);


pros::Motor fourBar(FOUR_BAR, pros::v5::MotorGears::green, pros::MotorUnits::deg);

//Sensors
pros::Imu imu (IMU);