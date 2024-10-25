#include "auton/matchAuton.h"

double WHEEL_DIAMETER = 2.79;
double DISTANCE_TO_RIGHT_ENCODER = 2.75;
double DISTANCE_TO_BACK_ENCODER = 4.75;


void initializeAuto() {
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            // pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            // pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            // pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading

            // pros::lcd::print(3, "leftFrontMotor: %f", leftFrontMotor.get_position()); // heading
            // pros::lcd::print(4, "leftBackMotor: %f", leftBackMotor.get_position()); // heading
            // pros::lcd::print(5, "rightFrontMotor: %f", rightFrontMotor.get_position()); // heading
            // pros::lcd::print(6, "rightBackMotor: %f", rightBackMotor.get_position()); // heading

            // printf("leftFrontMotor: %f \n", leftFrontMotor.get_position()); 
            // printf("leftBackMotor: %f \n", leftBackMotor.get_position()); 
            // printf("rightFrontMotor: %f \n", rightFrontMotor.get_position());
            // printf("rightBackMotor: %f \n", rightBackMotor.get_position()); 

            // double pitch = imu.get_pitch();
            // double roll = imu.get_roll();
            // double yaw = imu.get_yaw();

            // pros::lcd::print(4, "pitch: %f", pitch); 
            // pros::lcd::print(5, "roll: %f", roll); 
            // pros::lcd::print(6, "yaw: %f", yaw); 

            // printf("pitch:%f \n", pitch); 
            // printf("roll: %f \n", roll);
            // printf("yaw: %f \n", yaw); 

            // delay to save resources
            pros::delay(100);
        }
    });
}

void auton() {
    // chassis.moveToPoint(0, 24, 4000);
	// chassis.waitUntilDone();
	// chassis.moveToPoint(0, 0, 4000);
}
