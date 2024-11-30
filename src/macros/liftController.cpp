#include "macros/liftController.h"

// margin of error of height, units: ticks
#define MARGIN_OF_ERROR 20
// height where all the elastic bands are extended into a neutral state, units: ticks
#define HEIGHT_WHEN_ELASTIC_BANDS_SLACK 600
#define GRAVITY_MULTIPLER 1
#define ELASTIC_BAND_MULTIPLER 1

LiftController::LiftController() {
    currentHeight = LiftController::getHeight();
    targetHeight = 0;
}

double LiftController::getHeight() {
    return intakeLeft.get_position();
}

void LiftController::zeroEncoder() {
    intakeLeft.set_zero_position(intakeLeft.get_position());
}

/**
 * Go to a set height, 0 is lowest, + is up
 */
void LiftController::goToHeight(double height) {
    targetHeight = height;
}

/**
 * Ascend up at a set speed
 */
void LiftController::ascend(void* ignore) {
    targetHeight += 1;
}

/**
 * Descend down at a set speed
 */
void LiftController::descend(void* ignore) {
    targetHeight -= 1;
}

/**
 * PID Controller with feedforward for gravity and elastic bands
 */
double LiftController::calculatePIDF(double target, double current) 
{
    currentHeight = LiftController::getHeight();

    double error = target - current;

    // downwards force of gravity
    double gravity_feedforward = 9.81 * GRAVITY_MULTIPLER;

    // upwards force of elastic band, assuming height never surpasses slack height
    double elastic_band_feedforward = (HEIGHT_WHEN_ELASTIC_BANDS_SLACK - currentHeight) * ELASTIC_BAND_MULTIPLER;

    // prove the force necessary to hover, velocity 0
    if(abs(error) < MARGIN_OF_ERROR) {
        return gravity_feedforward - elastic_band_feedforward;
    }
    
    // Integral term
    integral += error;
    
    // Derivative term
    double derivative = error - lastError;
    lastError = error;
    
    // Calculate PID output
    double output_power = (kP * error) + (kI * integral) + (kD * derivative);

    //feedforward: account for gravity and elastic band forces
    output_power = output_power + gravity_feedforward - elastic_band_feedforward;

    if(output_power > 127) {
        output_power = 127;
    } else if (output_power < -127) {
        output_power = -127;
    }
    
    // Scale output to reasonable motor power
    return output_power;
}

// updates PID and power of each motor, call it in driveControl
void LiftController::update() {
    double power = calculatePIDF(targetHeight, currentHeight);

    intakeLeft.move(power);
    intakeRight.move(-power);
} 