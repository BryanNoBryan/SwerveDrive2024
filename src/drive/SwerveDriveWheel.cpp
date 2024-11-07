#include "drive/SwerveDriveWheel.h"

// in deg
#define ANGLE_MARGIN_OF_ERROR 2
// max velocity of motors, in RPM ticks
#define MAX_MOTOR_SPEED_TICKS 3

SwerveDriveWheel::SwerveDriveWheel(pros::Motor* motor1, pros::Motor* motor2, pros::Rotation* rotateEncoder, lemlib::PID &pid, bool reverseRotEncoder) : 
    motor1(motor1),
    motor2(motor2),
    rotateEncoder(rotateEncoder),
    reverseRotEncoder(reverseRotEncoder),
    PIDr(pid)
{    
    if (reverseRotEncoder)
    {
        rotateEncoder->reverse();
    }
    current_r = getAngle();
}

double SwerveDriveWheel::getAngle()
{
    // measured in centidegrees [0, 360]
    return (rotateEncoder->get_angle()/100.0);
}

/** Zeroes the wheel by updating the offset, and returns the new offset */
void SwerveDriveWheel::zero()
{
    rotateEncoder->reset_position();
    rotateEncoder->set_position(0);
}

double SwerveDriveWheel::calculatePID(double target, double current) 
{
    double error = calcAngleDiff(degreesToRadians(current), degreesToRadians(target));
    error = radiansToDegrees(error); // Convert back to degrees for PID math

    if(error < ANGLE_MARGIN_OF_ERROR) {
        return 0;
    }
    
    // Integral term
    integral += error;
    
    // Derivative term
    double derivative = error - lastError;
    lastError = error;
    
    // Calculate PID output
    double output_power = (kP * error) + (kI * integral) + (kD * derivative);

    if(output_power > 100) {
        output_power = 100;
    }

    if(output_power < 0) {
        output_power = 0;
    }
    
    // Scale output to reasonable motor power
    return output_power;
}

void SwerveDriveWheel::move(double speed, double angle, double power)
{
    target_r = angle;
    current_r = getAngle();

    double angleFromTarget = calcAngleDiff(degreesToRadians(getAngle()), degreesToRadians(angle));

    pros::lcd::print(3, " target_r %.3f", target_r);
    pros::lcd::print(4, " current_r %.3f", current_r);
    pros::lcd::print(5, " angleFromTarget %.3f", radiansToDegrees(angleFromTarget));

    double rPower = calculatePID(target_r, current_r);

    printf("speed %f\n", speed);
    printf("rPower %f\n\n\n", rPower);

    motor1->move(-speed);
    motor2->move(speed + rPower);

    // motor1->move((-speed * power + rPower));
    // motor2->move((speed * power + rPower));

    // pros::lcd::print(5, " motor 1 %f", ((-speed * power) + rPower) * MAX_MOTOR_SPEED_TICKS); 
    // pros::lcd::print(6, " motor 2 %f", ((speed * power) + rPower) * MAX_MOTOR_SPEED_TICKS);
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