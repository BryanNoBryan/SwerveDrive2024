#ifndef _INTAKE_CONTROLLER
#define _INTAKE_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"

#include "init/devices.h"

using namespace std;

class IntakeController
{
public:
	/**
     * @brief Spin intake forward at full speed
     */
    void intakeForward(void* ignore);
	/**
     * @brief Spin intake backwards at full speed
     */
	void intakeReverse(void* ignore);
     /**
     * @brief stop intake
     */
	void stop(void* ignore);
};

#endif