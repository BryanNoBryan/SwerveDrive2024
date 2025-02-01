#include "drive/purePursuit/CheckpointPursuit.h"

#define max_lin_accel 1.75
#define max_lin_vel 0.9
#define max_angular_accel 1
#define max_angular_vel 1

void CheckpointPursuit::run(bool turn, bool backwards, bool useX, bool clamp) {
    //the vector that we need to traverse to finish the path
    Pose diffPose = path.end_pos.vectorDiff(path.start_pos);
    double error;
    SwerveDrive sDrive;
    // bool backwards = false;

    rxtx_enable.set_value(HIGH);
    serial_read(nullptr);

    // double offsetX = otos_data[0];
    // double offsetY = otos_data[1];
    // double offsetTheta = -otos_data[2];

    Pose current_pos = Pose(-otos_data[0], -otos_data[1], -otos_data[2]);

    // double cosH = cos(current_pos.getTheta()*M_PI/180);
    // double sinH = sin(current_pos.getTheta()*M_PI/180);
    // double fieldX = current_pos.getX() * cosH - current_pos.getY() * sinH;
    // double fieldY = current_pos.getX() * sinH + current_pos.getY() * cosH;

    // current_pos = Pose(fieldX, fieldY, current_pos.getTheta());

    // printf("current_pos %f %f\n", current_pos.getX(), current_pos.getY());







    // 1. move heading in direction of vector
    PID pidRot1(0.5, 0.010, 0.000, 0);
    // double headingOfVector = angleWrap(90 - (atan2(diffPose.y, diffPose.x)*180/M_PI));
    // double headingOfVector = (atan2(diffPose.y, diffPose.x)*180/M_PI);
    double headingOfVector = path.end_pos.getTheta();
    error = headingOfVector - (-otos_data[2]);

    // if ((error > 165 || error < -165) && current_pos.distanceFrom(path.end_pos) > 2) {
    //     backwards = true;
    // }
    
    printf("start_pos %f %f\n", path.start_pos.getX(), path.start_pos.getY());
    printf("end_pos %f %f\n", path.end_pos.getX(), path.end_pos.getY());
    printf("diffPose %f %f\n", diffPose.getX(), diffPose.getY());
    printf("headingOfVector %f\n", headingOfVector);
    printf("error %f\n", error);

    while(abs(error) > 3) { //degrees
        rxtx_enable.set_value(HIGH);
        serial_read(nullptr);

        pros::lcd::print(0, "PosX %4.2f PosY %4.2f PosH %4.2f", -otos_data[0], -otos_data[1], -otos_data[2]);

        error = headingOfVector - (-otos_data[2]);
        
        printf("start_pos %f %f\n", path.start_pos.getX(), path.start_pos.getY());
        printf("end_pos %f %f\n", path.end_pos.getX(), path.end_pos.getY());
        printf("diffPose %f %f\n", diffPose.getX(), diffPose.getY());
        printf("headingOfVector %f\n", headingOfVector);
        printf("otos_data[2] %f\n", -otos_data[2]);
        printf("error %f\n", error);
        
        sDrive.move(0,0, pidRot1.update(error)/1000, 1);

        pros::delay(10);
    }

    printf("done\n\n\n\n\n\n\n\n\n\n\n");

    Timer afterDone;
    afterDone.start();

    while (afterDone.elapsed_time() < 750) {
        rxtx_enable.set_value(HIGH);
        serial_read(nullptr);

        error = headingOfVector - (-otos_data[2]);

        sDrive.move(0,0, pidRot1.update(error)/1000, 1);
        pros::delay(10);
    }







    // int past_count = 0;
    // double prev_t_error;
    if(!turn) {
        // 2. move to end_pos
        rxtx_enable.set_value(HIGH);
        serial_read(nullptr);

        PID pidLinear(1.5, 0.007, 0, 10);
        // PID pidLinear2(1.05, 0.001, 0, 5);
        // PID pidRot3(1, 0, 0, 0);
        timer = Timer();
        timer.start();
        Pose initial_pos = path.current_pos();
        current_pos = Pose(-otos_data[0], -otos_data[1], -otos_data[2]);
        double length = diffPose.length();

        error = current_pos.distanceFrom(path.end_pos);

        printf("error %f\n", error);
        // printf("timer.elapsed_time() %f\n", timer.elapsed_time());

        while (!path.reachedTarget(current_pos)) {
            rxtx_enable.set_value(HIGH);
            serial_read(nullptr);

            if(clamp){
                if(mogoOptical.get_proximity() > 253){
                    mogoClamp.set_value(HIGH);
                }
                pros::delay(10);
            }

            double position = path.motion_profile(max_lin_accel, max_lin_vel, length, timer.elapsed_time());

            Pose target_pos = Pose(initial_pos.getX() + diffPose.getX()*(position/length), initial_pos.getY() + diffPose.getY()*(position/length), path.end_pos.getTheta());

            current_pos = Pose(-otos_data[0], -otos_data[1], -otos_data[2]);

            Pose vectorDiff = target_pos.vectorDiff(current_pos); 

            // double xError = vectorDiff.getX();
            // double yError = vectorDiff.getY();

            // double newX = xError*cos((atan2(diffPose.y, diffPose.x)) - x*sin();
            // double newY = yError*sin() + y*cos();
            
            //* cos(angleWrap(90 - (atan2(diffPose.y, diffPose.x)*180/M_PI)) * M_PI/180)
            error = vectorDiff.length() * (backwards ? -1 : 1);
            bool sign = current_pos.distanceFrom(path.end_pos) > target_pos.distanceFrom(path.end_pos);

            error *= sign ? 1 : -1;
            // prev_t_error = error;

            // if (prev_t_error < error) {
            //     past_count++;
            // }

            // if (past_count > 5) {
            //     break;
            // }

            double xError = vectorDiff.getX();
            double yError = vectorDiff.getY();

            // printf("current_pos %f %f\n", current_pos.getX(), current_pos.getY());
            // printf("target_pos %f %f\n", target_pos.getX(), target_pos.getY());
            // printf("moving error %f\n\n", error);

            // bool sign = current_pos.distanceFrom(path.end_pos) > target_pos.distanceFrom(path.end_pos);

            // error *= backwards ? -1 : 1;

            printf("vectorDiff length %f\n", vectorDiff.length());
            printf("vectorDiff theta %f\n", vectorDiff.getTheta());
            printf("current_pos %f %f\n", current_pos.getX(), current_pos.getY());
            printf("target_pos %f %f\n", target_pos.getX(), target_pos.getY());
            printf("end_pos %f %f\n", path.end_pos.getX(), path.end_pos.getY());
            printf("headingdiff %f\n", angleWrap(90 - (atan2(diffPose.y, diffPose.x)*180/M_PI)));
            printf("error %f\n", error);
            printf("sign %d\n", sign);
            printf("current_pos.distanceFrom(path.end_pos) %f\n", current_pos.distanceFrom(path.end_pos));
            printf("target_pos.distanceFrom(path.end_pos) %f\n", target_pos.distanceFrom(path.end_pos));
            printf("xError %f\n", xError);
            printf("yError %f\n\n\n", yError);

            if(useX){ //pidLinear.update(xError)/45
                sDrive.move(-pidLinear.update(xError)/45, 0, 0, 1);
            } else {
                sDrive.move(pidLinear.update(yError)/45, 0, 0, 1);
            } //pidLinear.update(xError)/55

            // sDrive.move(pidLinear.update(error)/50, 0, 0, 1);

            pros::delay(10);
        }

        printf("done\n\n\n\n\n\n\n\n\n\n\n");


        // 3. move heading to final_pos
        // PID pidRot2(0.7, 0.007, 0, 0);

        // double final_heading = path.end_pos.getTheta();
        // error = final_heading - (-otos_data[2]);

        // printf("final_heading %f\n", final_heading);
        // printf("otos_data[2] %f\n", -otos_data[2]);
        // printf("error %f\n", error);

        // while (abs(error) > 3) { //degrees
        //     rxtx_enable.set_value(HIGH);
        //     serial_read(nullptr);

        //     error = final_heading - (otos_data[2]);

        //     printf("final_heading %f\n", final_heading);
        //     printf("otos_data[2] %f\n", otos_data[2]);
        //     printf("error %f\n\n", error);
            
        //     sDrive.move(0,0, -pidRot2.update(error)/1000, 1);

        //     pros::delay(10);
        // }

        // printf("done\n\n\n\n\n\n\n\n\n\n\n");
    }

    finishedPath = true;

}

bool CheckpointPursuit::finished() {
    return finishedPath;
}


