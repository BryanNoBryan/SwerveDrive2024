#include "macros/liftController.h"

LiftController::LiftController() : leftPID(kP, kI, kD), rightPID(kP, kI, kD) {
    zeroEncoder();
    currentHeight = 0;
    targetHeight = 0;
}

double LiftController::getHeight() {
    return gearRatio * (liftLeft.get_position() + liftRight.get_position()) / 2;
}

void LiftController::zeroEncoder() {
    liftLeft.set_zero_position(0);
    liftRight.set_zero_position(0);
}

/**
 * Go to a set height, 0 is lowest, + is up
 */
void LiftController::goToHeight(double height) {
    targetHeight = height;
}

// updates PID and power of each motor, call it in driveControl
void LiftController::update() {
    double leftPower = leftPID.update(targetHeight - liftLeft.get_position() * gearRatio);
    double rightPower = rightPID.update(targetHeight - liftRight.get_position() * gearRatio);

    if (targetHeight == 0 && getHeight() < 1) {
        leftPower = 0;
        rightPower = 0;
        liftLeft.move(0);
        liftRight.move(0);
        return;
    }

    liftLeft.move(leftPower + 40);
    liftRight.move(rightPower + 40);
}

double LiftHeight::getHeight() const {
    switch (index) {
        case LIFT_DOWN: return 0;
        case LIFT_UP: return LiftController::maximumHeight;
        default: return 0;
    }
}