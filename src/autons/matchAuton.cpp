#include "autons/matchAuton.h"
#include "serial/serial_comm.h"

void matchAuton(){
    leftFrontTopMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    leftFrontBottomMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rightFrontTopMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rightFrontBottomMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    leftBackTopMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    leftBackBottomMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rightBackTopMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rightBackBottomMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);

    // purePursuit purePursuit;
    
    // vector<PPoint> path = vector<PPoint>();
    // path.push_back(PPoint(0, 12.0, 0.0));
    // path.push_back(PPoint(-40.0, 24.0, 0.0));
    // path.push_back(PPoint(-80.0, 40.0, 0.0));
    // path.push_back(PPoint(-80.0, 80.0, 0.0));
    
    // purePursuit.runPath(path);

    // SwerveDrive sdrive;

    // sdrive.move(-0.8, 0, 0, 1);
    // pros::delay(2000);

    // sdrive.move(0, 0, 0.0001, 1);
    // pros::delay(100);

    // sdrive.move(0, 0, 0, 1);

    Pose target(15, 15, 45);
    Pose current_pos = Pose::current_pos();
    Path path(current_pos, target, true);
    CheckpointPursuit auton(path);
    auton.run();
    while (!auton.finished()) {}


    // PathFollowing()
    //     .withPath({{otos_data[0], otos_data[1], otos_data[2]}, {12, otos_data[1], otos_data[2]}}, 1)
    //     .withGains(30, 145)
    //     .withLimits(10, 20)
    //     .withThresholdErrors(0.5, 0.05)
    //     .ppMove();
}