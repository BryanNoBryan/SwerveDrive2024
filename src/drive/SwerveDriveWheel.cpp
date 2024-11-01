#include "SwerveDriveWheel.h"

// in deg
#define ANGLE_MARGIN_OF_ERROR 1000
// max velocity of motors, in RPM ticks
#define MAX_MOTOR_SPEED_TICKS 3

SwerveDriveWheel::SwerveDriveWheel(pros::Motor* motor1, pros::Motor* motor2, pros::Rotation rotateEncoder, lemlib::PID &pid, bool reverseRotEncoder) : 
motor1(motor1),
motor2(motor2),
rotateEncoder(rotateEncoder),
reverseRotEncoder(reverseRotEncoder),
PIDr(pid)
{    
    if (reverseRotEncoder)
    {
        rotateEncoder.reverse();
    }
    current_r = getAngle(); // adiaewajwiod
}

double SwerveDriveWheel::getAngle()
{
    // measured in centidegrees [0, 360]
    double angle = rotateEncoder.get_angle();
    return angleWrap(angle / 100.0);
}

/** Zeroes the wheel by updating the offset, and returns the new offset */
void SwerveDriveWheel::zero()
{
    rotateEncoder.reset_position();
}

void SwerveDriveWheel::move(double speed, double angle, double power)
{
    // leftFrontTopMotor.move(speed);
    // pros::lcd::print(4, " rightfrontwheel move speed, %f", speed); 
    // rightFrontTopMotor.move(100);
    // pros::lcd::print(0, " speed1 after %f", speed); 
    // motor1->move(speed*127);
    // motor2->move(100);
    // pros::lcd::print(6, " motor 1 port %d", motor1->get_port());
    // pros::lcd::print(7, " motor 1 speed %f", speed);

    target_r = angle;
    current_r = getAngle();
    pros::lcd::print(5, " leftFront angle %f", current_r);
    pros::lcd::print(0, " is changing %f", speed);
    double oppAngle = angleWrap(current_r + 180); // opp side

    double angleFromTarget = angleWrap(target_r - current_r);
    double oppAngleFromTarget = angleWrap(target_r - oppAngle);

    double rPower;
    if (fabs(angleFromTarget) > fabs(oppAngleFromTarget))
    {
        rPower = PIDr.update(oppAngleFromTarget);
    }
    else
    {
        rPower = PIDr.update(angleFromTarget);
    }

    if (fabs(oppAngleFromTarget) < ANGLE_MARGIN_OF_ERROR)
    {
        speed = -speed;
    }
    else if (fabs(angleFromTarget) > ANGLE_MARGIN_OF_ERROR)
    {
        speed = 0;
    }

    motor1->move_velocity(((-speed * power) + rPower) * MAX_MOTOR_SPEED_TICKS);
    motor2->move_velocity(((speed * power) + rPower) * MAX_MOTOR_SPEED_TICKS);

    pros::lcd::print(6, " motor 1 %f", ((-speed * power) + rPower) * MAX_MOTOR_SPEED_TICKS); 
    pros::lcd::print(7, " motor 2 %f", ((speed * power) + rPower) * MAX_MOTOR_SPEED_TICKS);
}

// class SwerveDriveWheel
// {
// public:
//     //motor1 is top
//     //motor2 is bottom
//     pros::Motor motor1;
//     pros::Motor motor2;
//     //  ASSUMPTIONS:
//     //motor encoder is built-in
//     //in-built motor PID should be sufficent for differential swerve

//     pros::Rotation rotateEncoder;
//     //PID for rotation
//     lemlib::PID PIDr;
//     bool reverseRotEncoder;

//     //rotation angle in deg, for PID
//     double current_r;
//     double target_r;

//     SwerveDriveWheel(pros::Motor motor1, pros::Motor motor2, int rotationPort, bool reverseRotEncoder = false, lemlib::PID &pid) :
//     motor1(motor1),
//     motor2(motor2),
//     rotateEncoder(rotationPort),
//     reverseRotEncoder(reverseRotEncoder),
//     PIDr(pid)
//     {
//         if (reverseRotEncoder) {
//             rotateEncoder.reverse();
//         }
//         current_r = getAngle(); //adiaewajwiod
//     }

//     double getAngle() {
//         //measured in centidegrees [0, 360]
//         double angle = rotateEncoder.get_angle();
//         return angleWrap(angle / 100.0);
//     }

//     /** Zeroes the wheel by updating the offset, and returns the new offset */
//     void zero()
//     {
//         rotateEncoder.reset_position();
//     }

//     void move(double speed, double angle, double power) {
//         target_r = angle;
//         current_r = getAngle();
//         double oppAngle = angleWrap(current_r + 180); //opp side

//         double angleFromTarget = angleWrap(target_r - current_r);
//         double oppAngleFromTarget = angleWrap(target_r - oppAngle);

//         double rPower;
//         if (fabs(angleFromTarget) > fabs(oppAngleFromTarget)) {
//             rPower = PIDr.update(oppAngleFromTarget);
//         } else {
//             rPower = PIDr.update(angleFromTarget);
//         }

//         if (fabs(oppAngleFromTarget) < ANGLE_MARGIN_OF_ERROR) {
//             speed = -speed;
//         }
//         else if (fabs(angleFromTarget) > ANGLE_MARGIN_OF_ERROR) {
//             speed = 0;
//         }

//         motor1.move_velocity(((-speed * power) + rPower) * MAX_MOTOR_SPEED_TICKS);
//         motor2.move_velocity(((speed * power) + rPower) * MAX_MOTOR_SPEED_TICKS);
//     }

//     //BELOW IS FUTURE IMPLEMENTATION, running in separate thread allows for faster PID

//     // void runAnglePID()
//     // {
//     //     pros::Task screen_task([&]() {
//     //         while (true)
//     //             {
//     //                 doPIDCalc();
//     //                 pros::delay(50);
//     //             }
//     //     });
//     // }

// };