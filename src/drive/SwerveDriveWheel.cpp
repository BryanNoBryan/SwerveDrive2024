#include "drive/SwerveDriveWheel.h"

// in deg
#define ANGLE_MARGIN_OF_ERROR 0.75
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

    if(abs(error) < ANGLE_MARGIN_OF_ERROR) {
        return 0;
    }
    
    // Integral term
    integral += error;
    
    // Derivative term
    double derivative = error - lastError;
    lastError = error;
    
    // Calculate PID output
    double output_power = (kP * error) + (kI * integral) + (kD * derivative);

    if(output_power > 127) {
        output_power = 127;
    } else if (output_power < -127) {
        output_power = -127;
    }
    
    // Scale output to reasonable motor power
    return output_power;
}

void SwerveDriveWheel::move(double speed, double angle, double power)
{
    target_r = angle;
    //the other angle case, to figure out if it's distance is shorter
    double opp_angle = target_r - 180;
    current_r = getAngle();
    //if it is shorter, negate reverse variable
    //TODO: clean up negative signs 
    bool reverse = true;

    double angleFromTarget = calcAngleDiff(degreesToRadians(getAngle()), degreesToRadians(angle));
    double oppAngleFromTarget = calcAngleDiff(degreesToRadians(getAngle()), degreesToRadians(opp_angle));

    // pros::lcd::print(4, " target_r %.3f", target_r);
    // pros::lcd::print(5, " current_r %.3f", current_r);
    // pros::lcd::print(6, " angleFromTarget %.3f", radiansToDegrees(angleFromTarget));

    //set new variable values if the oppAngle is a shorter distance
    if (abs(oppAngleFromTarget) < abs(angleFromTarget)) {
        angleFromTarget = oppAngleFromTarget;
        target_r = opp_angle;
        reverse = !reverse;
    }

    if (reverse) {
        speed *= -1.0;
    }

    speed *= cos(reverse ? angleFromTarget : oppAngleFromTarget);

    double rPower = calculatePID(target_r, current_r);

    printf("speed %f\n", speed);
    printf("rPower %f\n\n\n", rPower);
    /*
        ALL THE BELOW CODE IS TO OPTIMIZE 
        MOTOR POWER USAGE, AND HANDLE EDGE CASES
    
        abs(speed) > 2, meant to make it so that there's no rapid rotation,
        when the input is 0, causing the angle to be anywhere

        The code segment with sum1, sum2, and delta meant to make the full use
        of the motor power while staying in range [-127, 127], prioritizing rotation

        delta = the overflow of the max mumber above range, which when subtracted
        from either motor power sums, EFFECTIVELY only subtracts from the 
        linear speed, keeping rotational power

        CURRENT SITUATION:
        this delta setup is more unstable than without it, so patch up some instabilities next time

        final configuration:
        SwerveDrive.cpp
            //set multiplers to 127
            rightFront.move(speed1*127.0, angle1, power);

        right now it is at 75 as it's more stable that way for now
    
    */

    if (abs(speed) > 2) {

        //original output for each motors, will scale them accordingly below
        double sum1 = -speed + rPower;
        double sum2 = speed + rPower;

        motor1->move( (-speed + rPower));
        motor2->move( (speed + rPower));

        //delta = the overflow of the max mumber above range, which when subtracted
        //from either motor power sums, EFFECTIVELY only subtracts from the 
        //linear speed, keeping rotational power
        // double delta = 0.0;
        // if (abs(sum1) > abs(sum2)) {
        //     // SUM ONE IS LARGER
        //     if (sum1 > 127.0)
        //     {
        //         delta = sum1 - 127;
        //     }
        //     else if (sum1 < -127)
        //     {
        //         delta = sum1 + 127;
        //     }
        //     motor1->move(sum1 - delta);
        //     motor2->move(sum2 + delta);  
        // } else {
        //     // SUM TWO IS LARGER
        //     if (sum2 > 127)
        //     {
        //         delta = sum2 - 127;
        //     }
        //     else if (sum2 < -127)
        //     {
        //         delta = sum2 + 127;
        //     }
        //     motor1->move(sum1 + delta);
        //     motor2->move(sum2 - delta);
        // }
        
        // pros::lcd::print(6, "motor 1: %f, %f", sum1, delta);
        // pros::lcd::print(7, "motor 2: %f, %f", sum2,  delta);

    } else {
        //when input power is 0, to eliminate rapid angle changes
        motor1->move(0);
        motor2->move(0);    
    }
}