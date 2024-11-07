#include "macros/intakeController.h"

/**
 * Powers the intake at 127 (forward direction)
 */
void IntakeController::intakeForward(void* ignore) {
    intakeMotor.move(127);
}

/**
 * Powers intake at -127 (reverse direction)
 */
void IntakeController::intakeReverse(void* ignore) {
    intakeMotor.move(-127);
}
