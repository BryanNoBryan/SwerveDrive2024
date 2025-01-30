#include "drive/purePursuit/CheckpointPursuit.h"

#define  max_lin_accel 1
#define max_lin_vel 1
#define max_angular_accel 1
#define max_angular_vel 1

    CheckpointPursuit::CheckpointPursuit(Path path) : path(path) {

    };

    void CheckpointPursuit::run() {
        PID pid(1, 0, 0, 0);
        //the vector that we need to traverse to finish the path
        Pose diffPose = path.end_pos.vectorDiff(path.start_pos);
        double headingOfVector = angleWrap(atan2(diffPose.y, diffPose.x)*180/M_PI);

        double error = headingOfVector - otos_data[2];
        while (error > 10) { //degrees
            error = headingOfVector - otos_data[2];
            driveTrain.move(0,0, pid.update(error), 1);
        }
        
        
        // 1. move heading in direction of vector
        // PID(1, 0, 0, 0).update(diffPose.getTheta());


        // 2. move to end_pos


        // 3. move heading to final_pos
    }

    bool CheckpointPursuit::finished() {
       path.reachedTarget();
    }
