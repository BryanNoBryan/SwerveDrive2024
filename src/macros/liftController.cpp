#include "macros/liftController.h"

double LiftController::currentHeight = 0;
double* LiftController::targetHeight = nullptr;
double LiftController::lastError = 0;
double LiftController::integral = 0;

LiftController::LiftController() {
    currentHeight = getHeight();
    targetHeight = idleHeight;
    lastError = 0;
    integral = 0;
}

double LiftController::getHeight() {
    return leftPot.get_angle();
}

void LiftController::zeroEncoder() {
    // liftLeftTop.set_zero_position(0);
    // liftLeftBottom.set_zero_position(0);
    // liftRightTop.set_zero_position(0);
    // liftRightBottom.set_zero_position(0);
}

/**
 * Go to a set height, 0 is lowest, + is up
 */
void LiftController::goToHeight(void* height) {
    targetHeight = (double*) height;

    pros::lcd::print(3, "Going to height: %f", *targetHeight);

    while(abs(*targetHeight - currentHeight) > LIFT_MARGIN_OF_ERROR){
        update();

        pros::delay(10);
    }
}

/**
 * PID Controller with feedforward for gravity and elastic bands
 */
double LiftController::calculatePIDF(double target, double current) 
{
    currentHeight = getHeight();

    double error = (target - current)/2;
    pros::lcd::print(1, "Error: %f", error);

    // // downwards force of gravity
    // double gravity_feedforward = 9.81 * GRAVITY_MULTIPLER;

    // // upwards force of elastic band, assuming height never surpasses slack height
    // double elastic_band_feedforward = (HEIGHT_WHEN_ELASTIC_BANDS_SLACK - currentHeight) * ELASTIC_BAND_MULTIPLER;

    // // prove the force necessary to hover, velocity 0
    // if(abs(error) < MARGIN_OF_ERROR) {
    //     return gravity_feedforward - elastic_band_feedforward;
    // }
    
    // Integral term
    integral += error;
    
    // Derivative term
    double derivative = error - lastError;
    lastError = error;
    
    // Calculate PID output
    double output_power = (kP * error) + (kI * integral) + (kD * derivative);

    //feedforward: account for gravity and elastic band forces
    // output_power = output_power + gravity_feedforward - elastic_band_feedforward;

    if(output_power > 100) {
        output_power = 100;
    } else if (output_power < -100) {
        output_power = -100;
    }
    
    // Scale output to reasonable motor power
    return output_power;
}

// updates PID and power of each motor, call it in driveControl
void LiftController::update() {
    double power = calculatePIDF(*targetHeight, currentHeight);

    pros::lcd::print(4, "Power: %f", power);

    lift.move(power);
} 