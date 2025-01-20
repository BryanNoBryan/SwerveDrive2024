#ifndef _MOGO_CLAMP
#define _MOGO_CLAMP

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"

using namespace std;

class MogoClamp
{
public:
	/**
     * @brief Open claw and extend piston
     */
    void openClamp(void* ignore);
    /**
     * @brief Close claw and retract piston
     */
    void closeClamp(void* ignore);
};

#endif