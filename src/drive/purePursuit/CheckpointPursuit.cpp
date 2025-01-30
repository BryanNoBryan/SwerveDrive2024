#include "drive/purePursuit/CheckpointPursuit.h"

#define  max_lin_accel 1
#define max_lin_vel 1
#define max_angular_accel 1
#define max_angular_vel 1

    CheckpointPursuit::CheckpointPursuit(Path path) : path(path) {

    };

    void CheckpointPursuit::run() {
        //the vector that we need to traverse to finish the path
        Pose diffPose = path.end_pos.vectorDiff(path.start_pos);
        double error;
        SwerveDrive sDrive;

        // 1. move heading in direction of vector
        PID pidRot1(1, 0, 0, 0);
        double headingOfVector = angleWrap(90 - (atan2(diffPose.y, diffPose.x)*180/M_PI));

        error = headingOfVector - otos_data[2];
        while (error > 10) { //degrees
            error = headingOfVector - otos_data[2];
            sDrive.move(0,0, pidRot1.update(error), 1);
        }
        

        // 2. move to end_pos
        PID pidLinear(1, 0, 0, 0);
        timer = Timer();
        timer.start();
        Pose initial_pos = path.current_pos();
        double length = diffPose.length();
        while (!path.reachedTarget()) {
            double position = path.motion_profile(max_lin_accel, max_lin_vel, length, timer.elapsed_time());
            Pose target_pos = Pose(initial_pos.getX() + diffPose.getX()*(position/length), initial_pos.getY() + diffPose.getY()*(position/length), target_pos.getTheta());
            Pose current_pos = path.current_pos();
            error = current_pos.distanceFrom(target_pos); 
            bool sign = current_pos.distanceFrom(path.end_pos) > target_pos.distanceFrom(path.end_pos);
            error *= sign ? 1 : -1;
            sDrive.move(0,pidLinear.update(error), 0, 1);
        }
        

        // 3. move heading to final_pos
        PID pidRot2(1, 0, 0, 0);
        double final_heading = path.end_pos.getTheta();

        error = final_heading - otos_data[2];
        while (error > 10) { //degrees
            error = final_heading - otos_data[2];
            sDrive.move(0,0, pidRot2.update(error), 1);
        }
    }

    bool CheckpointPursuit::finished() {
       return path.reachedTarget();
    }
