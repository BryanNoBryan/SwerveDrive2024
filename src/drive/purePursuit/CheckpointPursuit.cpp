#include "drive/purePursuit/CheckpointPursuit.h"

class CheckpointPursuit {
    Path path;
    Timer timer;

    CheckpointPursuit(Path path) : path(path) {};

    void run() {
        //the vector that we need to traverse to finish the path
        Pose diffPose = path.start_pos - path.end_pos;

        // 1. move heading in direction of vector



        // 2. move to end_pos



        // 3. move heading to final_pos
    }

    bool finished() {
       path.reachedTarget();
    }
}