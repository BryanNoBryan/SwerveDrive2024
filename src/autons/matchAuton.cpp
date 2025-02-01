#include "autons/matchAuton.h"
#include "serial/serial_comm.h"

//Return the current reference position based on the given motion profile times, maximum acceleration, velocity, and current time
double motion_profile(double max_acceleration, double max_velocity, double distance, double elapsed_time) {

    if(distance < 0){
        max_velocity *= -1;
        max_acceleration *= -1;
    }

    // Calculate the time it takes to accelerate to max velocity
    double acceleration_dt = max_velocity / max_acceleration;

    // If we can't accelerate to max velocity in the given distance, we'll accelerate as much as possible
    double halfway_distance = distance / 2;
    double acceleration_distance = 0.5 * max_acceleration * pow(acceleration_dt, 2);

    if (acceleration_distance > halfway_distance) {
        acceleration_dt = sqrt(halfway_distance / (0.5 * max_acceleration));
    }

    acceleration_distance = 0.5 * max_acceleration * pow(acceleration_dt, 2);

    // recalculate max velocity based on the time we have to accelerate and decelerate
    max_velocity = max_acceleration * acceleration_dt;

    // we decelerate at the same rate as we accelerate
    double deceleration_dt = acceleration_dt;

    // calculate the time that we're at max velocity
    double cruise_distance = distance - 2 * acceleration_distance;
    double cruise_dt = cruise_distance / max_velocity;
    double deceleration_time = acceleration_dt + cruise_dt;

    // check if we're still in the motion profile
    double entire_dt = acceleration_dt + cruise_dt + deceleration_dt;
    if (elapsed_time > entire_dt) {
        return distance;
    }

    // if we're accelerating
    if (elapsed_time < acceleration_dt) {
        // use the kinematic equation for acceleration
        return 0.5 * max_acceleration * pow(acceleration_dt, 2);
    }

    // if we're cruising
    else if (elapsed_time < deceleration_time) {
        acceleration_distance = 0.5 * max_acceleration * pow(acceleration_dt, 2);
        double cruise_current_dt = elapsed_time - acceleration_dt;

        // use the kinematic equation for constant velocity
        return acceleration_distance + max_velocity * cruise_current_dt;
    }

    // if we're decelerating
    else {
        acceleration_distance = 0.5 * max_acceleration * pow(acceleration_dt, 2);
        cruise_distance = max_velocity * cruise_dt;
        deceleration_time = elapsed_time - deceleration_time;

        // use the kinematic equations to calculate the instantaneous desired position
        return acceleration_distance + cruise_distance + max_velocity * deceleration_time - 0.5 * max_acceleration * pow(acceleration_dt, 2);
    }
}

void matchAuton(){
    leftFrontTopMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    leftFrontBottomMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rightFrontTopMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rightFrontBottomMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    leftBackTopMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    leftBackBottomMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rightBackTopMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rightBackBottomMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);



    // Pose target(15, 15, 45);
    // Pose current_pos = Pose::current_pos();
    // Path path(current_pos, target, true);
    // CheckpointPursuit auton(path);
    // auton.run();
    // while (!auton.finished()) {}


    //ON THE LEFT TILE OF THE MIDDLE POST, IN THE CENTER OF THE TILE, WITH INTAKE FACING FORWARDS

    SwerveDrive sdrive;

    BucketController bucketController;
    bucketController.zeroEncoder();

    LiftController liftController;
    liftController.zeroEncoder();

    //IntakeController().intakeForward(NULL);
    // IntakeController().intakeReverse(NULL);
    //IntakeController().stop(NULL);

    Timer timer;
    timer.start();
    while (timer.elapsed_time() < 600) {
        sdrive.move(-0.15, 0, 0, 1);
    }

    sdrive.move(0, 0, 0, 1);
    pros::delay(500);

    timer.start();
    while (timer.elapsed_time() < 2550) {
        sdrive.move(0, -0.13, 0, 1);
    }

    sdrive.move(0, 0, 0, 1);
    pros::delay(500);


    
    timer.start();
    while (timer.elapsed_time() < 1000) {
        liftController.goToHeight(20);
        bucketController.goToPosition(BUCKET_MIDDLE.getPos());
        bucketController.update();
        liftController.update();
    }
    timer.start();
    while (timer.elapsed_time() < 1000) {
        bucketController.goToPosition(BUCKET_OUT.getPos());
        bucketController.update();
        liftController.update();
    }
    timer.start();
    while (timer.elapsed_time() < 1000) {
        bucketController.goToPosition(BUCKET_IN.getPos());
        liftController.goToHeight(LIFT_DOWN.getHeight());
        bucketController.update();
        liftController.update();
    }

    timer.start();
    while (timer.elapsed_time() < 2550) {
        sdrive.move(0, 0.13, 0, 1);
    }

    sdrive.move(0, 0, 0, 1);
    pros::delay(500);

    timer.start();
    while (timer.elapsed_time() < 600) {
        sdrive.move(0.15, 0, 0, 1);
    }

    sdrive.move(0, 0, 0, 1);
    pros::delay(500);
    
    

    // sdrive.move(0, 0, 0, 1);
    // pros::delay(10);

    // //Start intake
    // IntakeController().intakeForward(NULL);
    // pros::delay(10);

    // //Move to first stack
    // Pose target(0, 18, 0);
    // Pose current_pos = Pose::current_pos();
    // Path path(current_pos, target, true);
    // CheckpointPursuit auton(path);
    // auton.run(false, true, false, false);
    // // while (!auton.finished()) {}
    // pros::delay(500);

    
}