#include "macros/intakeController.h"

/**
 * Powers the intake at 127 (forward direction)
 */
void IntakeController::intakeForward(void* ignore) {
    intake.move(127);
}

/**
 * Powers intake at -127 (reverse direction)
 */
void IntakeController::intakeReverse(void* ignore) {
    intake.move(-127);
}

/**
 * Powers intake at 0 (stop)
 */
void IntakeController::stop(void* ignore) {
    intake.move(0);
}