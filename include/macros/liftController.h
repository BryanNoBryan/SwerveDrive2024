#ifndef _LIFT_CONTROLLER
#define _LIFT_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
// margin of error of height, units: ticks
#define LIFT_MARGIN_OF_ERROR 50
// height where all the elastic bands are extended into a neutral state, units: ticks
#define HEIGHT_WHEN_ELASTIC_BANDS_SLACK 600
#define GRAVITY_MULTIPLER 1
#define ELASTIC_BAND_MULTIPLER 1

#include "api.h"
#include "init/devices.h"

using namespace std;

class LiftController
{
private:
    // PID Constants
    static constexpr double kP = 1.3;
    static constexpr double kI = 0;
    static constexpr double kD = 0;
    
    // Error tracking
    static double lastError;
    static double integral;

    /**
     * @brief calculates power each motor should run at each height, accounts for gravity and elastic bands
     */
    static double calculatePIDF(double target, double current);

public:
    static double currentHeight;
    static double* targetHeight;

    double idleHeightValue = 0;
    double ringHeightValue = -5;
    double lowerScoreHeightValue = -4000;
    double upperScoreHeightValue = 1000;

    double* idleHeight = &idleHeightValue;
    double* ringHeight = &ringHeightValue;
    double* lowerScoreHeight = &lowerScoreHeightValue;
    double* upperScoreHeight = &upperScoreHeightValue;

    /**
     * @brief Get current height, 0 is lowest, + is up
     */
    static double getHeight();

    /**
     * @brief Go to a set height, 0 is lowest, + is up
     */
	static void goToHeight(void* height);

    // /**
    //  * @brief ascend up at a set speed
    //  */
	// void ascend(void* ignore);

    // /**
    //  * @brief descend down at a set speed
    //  */
	// void descend(void* ignore);

    /**
     * @brief updates PID and power of each motor, call it in driveControl
     */
    static void update();

    /**
     * @brief sets zero position of the lift encoder
     */
    static void zeroEncoder();

    // constructor
    LiftController();

};

#endif