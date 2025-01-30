#include "drive/purePursuit/PID.h"

double PID::update(double error) {
    // Calculate integral with anti-windup
    if (windupRange == 0 || std::abs(error) < windupRange) {
        integral += error;
    }

    // Calculate derivative
    double derivative = error - prevError;
    
    // Store current error for next iteration
    prevError = error;

    // Return PID output
    return kP * error + kI * integral + kD * derivative;
}

void PID::reset() {
    integral = 0;
    prevError = 0;
}