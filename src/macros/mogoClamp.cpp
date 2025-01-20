#include "macros/mogoClamp.h"

/**
 * Piston extends
 */
void MogoClamp::openClamp(void* ignore) {
    clampLeft.set_value(true);
    clampRight.set_value(true);
}

/**
 * Piston retracts
 */
void MogoClamp::closeClamp(void* ignore) {
    clampLeft.set_value(false);
    clampRight.set_value(false);
}