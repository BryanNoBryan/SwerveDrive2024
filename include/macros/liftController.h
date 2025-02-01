#ifndef _LIFT_CONTROLLER
#define _LIFT_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "init/devices.h"
#include "lemlib/pid.hpp"

using namespace std;

class LiftController
{
private:
    // PID Constants
    static constexpr double kP = 6;
    static constexpr double kI = 0;
    static constexpr double kD = 2;

    static constexpr double gearRatio = 0.5; // Lift moves 1/2 as fast as motor
    
    lemlib::PID leftPID;
    lemlib::PID rightPID;

public:
    double currentHeight;
    double targetHeight;

    static constexpr double maximumHeight = 70;

    /**
     * @brief Get current height, 0 is lowest, + is up
     */
    double getHeight();

    /**
     * @brief Go to a set height, 0 is lowest, + is up
     */
	void goToHeight(double height);

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

class LiftHeight {
    int index;
public:
    static constexpr int length() {return 2;}
    LiftHeight() : index(0) {}
    constexpr explicit LiftHeight(int index) : index(index) {}
    constexpr operator int() const { return index; }

    double getHeight() const;
};
constexpr LiftHeight LIFT_DOWN(0);
constexpr LiftHeight LIFT_UP(1);

#endif