#include "macros/mogoClamp.h"

/**
 * Piston extends
 */
void MogoClamp::openClamp(void* ignore) {
    mogoClamp.set_value(true);
}

/**
 * Piston retracts
 */
void MogoClamp::closeClamp(void* ignore) {
    mogoClamp.set_value(false);
}