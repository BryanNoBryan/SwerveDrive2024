#include "drive/purePursuit/CheckpointPursuit.h"

#define  max_lin_accel 1
#define max_lin_vel 1
#define max_angular_accel 1
#define max_angular_vel 1

class CheckpointPursuit {
    Path path;
    Timer timer;

    CheckpointPursuit(Path path) : path(path) {

    };

    void run() {
        //the vector that we need to traverse to finish the path
        Pose diffPose = path.end_pos.vectorDiff(path.start_pos);

        // 1. move heading in direction of vector



        // 2. move to end_pos



        // 3. move heading to final_pos
    }

    bool finished() {
       path.reachedTarget();
    }
};