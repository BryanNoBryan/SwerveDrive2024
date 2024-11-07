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
#include "drive/SwerveDrive.h"
#include "init/devices.h"
#include <cmath>
#include <algorithm>

using namespace std;

#define TRACK_LENGTH 11.625f
#define TRACK_WIDTH 11.625f

void driveControl();


#endif