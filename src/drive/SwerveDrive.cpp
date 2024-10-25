#include "drive/SwerveDrive.h"

// Physical constants
#define TRACK_LENGTH 11.625f
#define TRACK_WIDTH 11.625f
#define MAX_SPEED_CONSTRAINT 1

// radius from center to each wheel
const double RADIUS = sqrt(pow(TRACK_LENGTH, 2) + pow(TRACK_WIDTH, 2));

lemlib::PID testPID (0.01, 0, 0, 10, false);


SwerveDrive::SwerveDrive() :
rightFront(rightFrontTopMotor, rightBackBottomMotor, rightFrontEncoder, testPID, false),
leftFront(leftFrontTopMotor, leftFrontBottomMotor, leftFrontEncoder, testPID, false),
leftBack(leftBackTopMotor, leftBackBottomMotor, leftBackEncoder, testPID, false),
rightBack(rightBackTopMotor, rightBackBottomMotor, rightBackEncoder, testPID, false) 
{
}

// anglewrapped [-180, 180], positive is clockwise, zero is straight ahead
// +x to the right, +y is downfield, power is scalar multiplier
void SwerveDrive::moveTo(double x, double y, double angle, double power)
{
    double A = x - angle * TRACK_LENGTH / 2;
    double B = x + angle * TRACK_LENGTH / 2;
    double C = y - angle * TRACK_LENGTH / 2;
    double D = y + angle * TRACK_LENGTH / 2;
    // wheel 1: top right
    // wheel 2: top left
    // wheel 3: bottom left
    // wheel 4: bottom right
    double speed1 = sqrt(pow(B, 2) + pow(C, 2));
    double angle1 = atan2(B, C) * 180 / M_PI;
    double speed2 = sqrt(pow(B, 2) + pow(D, 2));
    double angle2 = atan2(B, D) * 180 / M_PI;
    double speed3 = sqrt(pow(A, 2) + pow(D, 2));
    double angle3 = atan2(A, D) * 180 / M_PI;
    double speed4 = sqrt(pow(A, 2) + pow(C, 2));
    double angle4 = atan2(A, C) * 180 / M_PI;
    // speed is in range [0, 1]
    double max = std::max({speed1, speed2, speed3, speed4});
    if (max > 1)
    {
        speed1 = speed1 / max;
        speed2 = speed2 / max;
        speed3 = speed3 / max;
        speed4 = speed4 / max;
    }

    // tell each wheel to do what
    rightFront.move(speed1, angle1, power);
    leftFront.move(speed2, angle2, power);
    leftBack.move(speed3, angle3, power);
    rightBack.move(speed4, angle4, power);
}

void SwerveDrive::reset_position() {
    rightFront.zero();
    leftFront.zero();
    leftBack.zero();
    rightBack.zero();
}

SwerveDrive driveTrain;


// class SwerveDrive
// {
// public:
//     SwerveDriveWheel rightFront;
//     SwerveDriveWheel leftFront;
//     SwerveDriveWheel leftBack;
//     SwerveDriveWheel rightBack;

//     SwerveDrive() :
//     rightFront(rightFrontTopMotor, rightBackBottomMotor, rightFrontEncoder, false, testPID),
//     leftFront(leftFrontTopMotor, leftFrontBottomMotor, leftFrontEncoder, false, testPID),
//     leftBack(leftBackTopMotor, leftBackBottomMotor, leftBackEncoder, false, testPID),
//     rightBack(rightBackTopMotor, rightBackBottomMotor, rightBackEncoder, false, testPID) 
//     {

//     }

//     // anglewrapped [-180, 180], positive is clockwise, zero is straight ahead
//     // +x to the right, +y is downfield, power is scalar multiplier
//     void moveTo(double x, double y, double angle, double power)
//     {
//         double A = x - angle * TRACK_LENGTH / 2;
//         double B = x + angle * TRACK_LENGTH / 2;
//         double C = y - angle * TRACK_LENGTH / 2;
//         double D = y + angle * TRACK_LENGTH / 2;

//         // wheel 1: top right
//         // wheel 2: top left
//         // wheel 3: bottom left
//         // wheel 4: bottom right

//         double speed1 = sqrt(pow(B, 2) + pow(C, 2));
//         double angle1 = atan2(B, C) * 180 / M_PI;
//         double speed2 = sqrt(pow(B, 2) + pow(D, 2));
//         double angle2 = atan2(B, D) * 180 / M_PI;
//         double speed3 = sqrt(pow(A, 2) + pow(D, 2));
//         double angle3 = atan2(A, D) * 180 / M_PI;
//         double speed4 = sqrt(pow(A, 2) + pow(C, 2));
//         double angle4 = atan2(A, C) * 180 / M_PI;

//         // speed is in range [0, 1]
//         double max = std::max({speed1, speed2, speed3, speed4});
//         if (max > 1)
//         {
//             speed1 = speed1 / max;
//             speed2 = speed2 / max;
//             speed3 = speed3 / max;
//             speed4 = speed4 / max;
//         }

//         double power = 1;
//         // tell each wheel to do what
//         rightFront.move(speed1, angle1, power);
//         leftFront.move(speed2, angle2, power);
//         leftBack.move(speed3, angle3, power);
//         rightBack.move(speed4, angle4, power);
//     }
// };