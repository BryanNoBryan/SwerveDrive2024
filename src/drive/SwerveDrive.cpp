#include "drive/SwerveDrive.h"

// Physical constants
#define TRACK_LENGTH 11.625f
#define TRACK_WIDTH 11.625f
#define MAX_SPEED_CONSTRAINT 1

// radius from center to each wheel
const double RADIUS = sqrt(pow(TRACK_LENGTH, 2) + pow(TRACK_WIDTH, 2));

lemlib::PID testPID (1, 0, 0, 10, false);

/*
 LESSON LEARNED:
    MOTORS MUST BE BY REFERENCE

    NEXT TARGET:
    ENCODERS OUTPUT A CONSTANT VALUE
    POTENTIALLY HAVE TO DO ENCODER BY REFERENCE TOO
    HOWEVER, I DID IT REFERENCE THE SAME WAY AS WITH MOTORS, BUT GIVE DAEMON ERRORS
    Strangely it compiles fine, therefore it is a runtime error

*/

SwerveDrive::SwerveDrive() :
    rightFront(&rightFrontTopMotor, &rightBackBottomMotor, &rightFrontEncoder, testPID, false),
    leftFront(&leftFrontTopMotor, &leftFrontBottomMotor, &leftFrontEncoder, testPID, false),
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
    double angle1 = atan2(B, C) * 180 / M_PI;
    double speed2 = sqrt(pow(B, 2) + pow(D, 2));
    double angle2 = atan2(B, D) * 180 / M_PI;
    double speed3 = sqrt(pow(A, 2) + pow(D, 2));
    double angle3 = atan2(A, D) * 180 / M_PI;
    double speed4 = sqrt(pow(A, 2) + pow(C, 2));
    double angle4 = atan2(A, C) * 180 / M_PI;

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

    printf("speed1 %f\n", speed1*127.0);
    printf("speed2 %f\n", speed2*127.0);
    printf("speed3 %f\n", speed3*127.0);
    printf("speed4 %f\n", speed4*127.0);

    printf("angle1 %f\n", angle1);
    printf("angle2 %f\n", angle2);
    printf("angle3 %f\n", angle3);
    printf("angle4 %f\n", angle4);
		

    // tell each wheel to do what
    rightFront.move(speed1*75.0, angle1, power);
    leftFront.move(speed2*75.0, angle2, power);
    leftBack.move(speed3*75.0, angle3, power);
    rightBack.move(speed4*75.0, angle4, power);
}

void SwerveDrive::reset_position() {
    rightFront.zero();
    leftFront.zero();
    leftBack.zero();
    rightBack.zero();
}

// pros::lcd::print(0, " x %f", x);
// pros::lcd::print(1, " y %f", y);
// pros::lcd::print(2, " angle %f", angle);

// pros::lcd::print(1, " max %f", max); 
// pros::lcd::print(2, " speed1 before %f", speed1);

// pros::lcd::print(0, " speed1 before %f", speed1); 

// pros::lcd::print(6, " rightFront %d", speed1); 
// pros::lcd::print(7, " leftFront %d", speed2); 
// pros::lcd::print(5, " leftBack %f", speed3); 
// pros::lcd::print(9, " rightBack %f", speed4); 


// pros::lcd::print(5, " angle %f", angle);
// pros::lcd::print(5, " angle %f", angle);
// pros::lcd::print(5, " angle %f", angle);

// pros::lcd::print(6, " A %f", A); 
// pros::lcd::print(7, " B %f", B); 