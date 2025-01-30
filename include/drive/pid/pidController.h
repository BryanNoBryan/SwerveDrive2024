#ifndef _PID_CONTROLLER
#define _PID_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

class PIDController {
private:
    double kP;
    double kI;
    double kD;
    double integral;
    double previousError;
    double setpoint;

public:
    PIDController(double kP, double kI, double kD);

    /**
     * @brief Set the target setpoint for the PID controller
     * @param setpoint The desired setpoint
     */
    void setSetpoint(double setpoint);

    /**
     * @brief Calculate the output of the PID controller
     * @param current The current value
     * @return The output value
     */
    double calculate(double current);

    /**
     * @brief Reset the PID controller
     */
    void reset();
};

#endif
