#ifndef _LIFT_CONTROLLER
#define _LIFT_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"

#include "init/devices.h"

using namespace std;

class LiftController
{
private:
    // PID Constants
    double kP = 1.3;
    double kI = 0;
    double kD = 0;
    
    // Error tracking
    double lastError = 0;
    double integral = 0;

    /**
     * @brief calculates power each motor should run at each height, accounts for gravity and elastic bands
     */
    double calculatePIDF(double target, double current);

public:
    double currentHeight;
    double targetHeight;

    /**
     * @brief Get current height, 0 is lowest, + is up
     */
    double getHeight();

    /**
     * @brief Go to a set height, 0 is lowest, + is up
     */
	void goToHeight(double height);

    /**
     * @brief ascend up at a set speed
     */
	void ascend(void* ignore);

    /**
     * @brief descend down at a set speed
     */
	void descend(void* ignore);

    /**
     * @brief updates PID and power of each motor, call it in driveControl
     */
    void update();

    /**
     * @brief sets zero position of the lift encoder
     */
    void zeroEncoder();

    // constructor
    LiftController();

};

#endif