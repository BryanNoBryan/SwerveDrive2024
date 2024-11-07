#ifndef _DRIVE_CONTROL
#define _DRIVE_CONTROL

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/utility.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/misc.h"
#include "drive/driveTrain.h"
#include "macros/intakeController.h"

void driveControl();

#endif