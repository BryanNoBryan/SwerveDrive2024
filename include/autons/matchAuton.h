#ifndef _MATCH_AUTO
#define _MATCH_AUTO

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"
#include "init/devices.h"
#include "init/utility.h"
#include "drive/SwerveDrive.h"
#include "drive/purePursuit/purePursuit.h"
#include "drive/purePursuit/pathFollowing.h"
#include "drive/purePursuit/pathGeneration.h"
#include "drive/purePursuit/Pose.h"
#include "drive/purePursuit/Path.h"
#include "drive/purePursuit/CheckpointPursuit.h"


void matchAuton();

#endif