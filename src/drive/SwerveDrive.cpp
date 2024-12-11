#include "drive/SwerveDrive.h"

// Physical constants
#define TRACK_LENGTH 14.5f
#define TRACK_WIDTH 14.5f
#define MAX_SPEED_CONSTRAINT 1

// radius from center to each wheel
const double RADIUS = sqrt(pow(TRACK_LENGTH, 2) + pow(TRACK_WIDTH, 2));

lemlib::PID testPID (1, 0, 0, 10, false);

SwerveDrive::SwerveDrive() :
    rightFront(&rightFrontTopMotor, &rightFrontBottomMotor, &rightFrontEncoder, testPID, true),
    leftFront(&leftFrontTopMotor, &leftFrontBottomMotor, &leftFrontEncoder, testPID, true),
    leftBack(&leftBackTopMotor, &leftBackBottomMotor, &leftBackEncoder, testPID, false),
    rightBack(&rightBackTopMotor, &rightBackBottomMotor, &rightBackEncoder, testPID, false) 
{}

// anglewrapped [-180, 180], positive is clockwise, zero is straight ahead
// +x to the right, +y is downfield, power is scalar multiplier
void SwerveDrive::move(double x, double y, double angle, double power)
{
    double A = x - angle * TRACK_LENGTH / 2;
    double B = x + angle * TRACK_LENGTH / 2;
    double C = y - angle * TRACK_WIDTH / 2;
    double D = y + angle * TRACK_WIDTH / 2;

    // wheel 1: top right
    // wheel 2: top left
    // wheel 3: bottom left
    // wheel 4: bottom right
    double speed1 = sqrt(pow(B, 2) + pow(C, 2));
    double angle1 = -atan2(B, C) * 180 / M_PI;
    double speed2 = sqrt(pow(B, 2) + pow(D, 2));
    double angle2 = -atan2(B, D) * 180 / M_PI;
    double speed3 = sqrt(pow(A, 2) + pow(D, 2));
    double angle3 = -atan2(A, D) * 180 / M_PI;
    double speed4 = sqrt(pow(A, 2) + pow(C, 2));
    double angle4 = -atan2(A, C) * 180 / M_PI;

    // speed is in range [0, 1]
    double maxVel = 0.7;
    double maxSpeed = max(abs(speed1), max(abs(speed2), max(abs(speed3), abs(speed4))));

    printf("maxSpeed %f\n", maxSpeed);

    if (maxSpeed > maxVel){
        speed1 = speed1 * (maxVel/maxSpeed);
        speed2 = speed2 * (maxVel/maxSpeed);
        speed3 = speed3 * (maxVel/maxSpeed);
        speed4 = speed4 * (maxVel/maxSpeed);
    }

    rightFront.move(speed1*127.0, angle1, power);
    leftFront.move(speed2*127.0, angle2, power);
    leftBack.move(speed3*127.0, angle3, power);
    rightBack.move(speed4*127.0, angle4, power);
}

void SwerveDrive::reset_position() {
    rightFront.zero();
    leftFront.zero();
    leftBack.zero();
    rightBack.zero();
}