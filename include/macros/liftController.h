#ifndef _LIFT_CONTROLLER
#define _LIFT_CONTROLLER


#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "lemlib/pid.hpp"

class LiftController
{
public:
    /**
     * @brief Rotate lift mechanism up
     */
    static void liftUp(void* ignore);
    /**
     * @brief Rotate lift mechanism down
     */
    static void liftDown(void* ignore);

    static void PIDInit();

    static void updatePID();

    // static lemlib::PID barPID(float x, float y , float z , float a , bool b);

    static double fourBarPosition;
    static double targetPosition;  
};




#endif