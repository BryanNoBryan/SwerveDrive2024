#include "macros/intakeController.h"

/**
 * Powers the intake at 127 (forward direction)
 */
void IntakeController::intakeForward(void* ignore) {
    intakeLeft.move(127);
    intakeRight.move(-127);
}

/**
 * Powers intake at -127 (reverse direction)
 */
void IntakeController::intakeReverse(void* ignore) {
    intakeLeft.move(-127);
    intakeRight.move(127);
}

/**
 * Powers intake at 0 (stop)
 */
void IntakeController::stop(void* ignore) {
    intakeLeft.move(0);
    intakeRight.move(0);
}