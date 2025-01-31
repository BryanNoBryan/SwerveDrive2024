#include "drive/SwerveDrive.h"

// Physical constants
#define TRACK_LENGTH 14.5f
#define TRACK_WIDTH 14.5f
#define MAX_SPEED_CONSTRAINT 1

// radius from center to each wheel
const double R = sqrt(pow(TRACK_LENGTH, 2) + pow(TRACK_WIDTH, 2));

lemlib::PID testPID(1, 0, 0, 10, false);

const double rotKP = 1.5;
const double rotKI = 0;
const double rotKD = 0;

lemlib::PID rightFrontPID (0.7, rotKI, rotKD, 10, false);
lemlib::PID leftFrontPID (1.3, rotKI, rotKD, 10, false);
lemlib::PID leftBackPID (0.8, rotKI, rotKD, 10, false);
lemlib::PID rightBackPID (1, rotKI, rotKD, 10, false);

SwerveDrive::SwerveDrive() :
    rightFront(&rightFrontTopMotor, &rightFrontBottomMotor, &rightFrontEncoder, rightFrontPID, true),
    leftFront(&leftFrontTopMotor, &leftFrontBottomMotor, &leftFrontEncoder, leftFrontPID, true),
    leftBack(&leftBackTopMotor, &leftBackBottomMotor, &leftBackEncoder, leftBackPID, false),
    rightBack(&rightBackTopMotor, &rightBackBottomMotor, &rightBackEncoder, rightBackPID, false) 
{}

// anglewrapped [-180, 180], positive is clockwise, zero is straight ahead
// +x to the right, +y is downfield, power is scalar multiplier
void SwerveDrive::move(double x, double y, double angle, double power)
{
    double C = x - angle * TRACK_LENGTH / 2;
    double D = x + angle * TRACK_LENGTH / 2;
    double A = y - angle * TRACK_WIDTH / 2;
    double B = y + angle * TRACK_WIDTH / 2;

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
    double maxVel = 0.9;
    double maxSpeed = max(abs(speed1), max(abs(speed2), max(abs(speed3), abs(speed4))));

    // printf("maxSpeed %f\n", maxSpeed);
    // printf("angle1 %f\n", angle1);
    // printf("angle2 %f\n", angle2);
    // printf("angle3 %f\n", angle3);
    // printf("angle4 %f\n", angle4);
    // printf("\n\n");

    float velocity = pow(pow(otos_data[3], 2)+ pow(otos_data[4], 2), 0.5);
    
    maxVel = min(velocity + 0.6, maxVel);

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