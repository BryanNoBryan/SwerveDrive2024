// #include "driveControl.h"
// #include "macros/bucketController.h"
// #include "stdio.h"
// #include "serial/serial_comm.h"

// /**
//  * Takes input from controller joysticks
//  * Controls intakes and macro execution using button presses
//  */
// void driveControl()
// {
//     int fwd, str, rcw;
//     bool idle = false;
//     bool clampToggle = false;
//     bool lastScore = false;

//     const double RADIUS = sqrt(pow(TRACK_LENGTH, 2) + pow(TRACK_WIDTH, 2));
//     lemlib::PID testPID (1, 0, 0, 10, false);

//     SwerveDrive sdrive;
//     // sdrive.reset_position();

//     intake.set_brake_mode(MOTOR_BRAKE_BRAKE);
//     liftLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
//     liftRight.set_brake_mode(MOTOR_BRAKE_BRAKE);

//     LiftController liftController;
//     liftController.zeroEncoder();
//     BucketController bucketController;
//     bucketController.zeroEncoder();

// 	while (true)
// 	{
// 		rxtx_enable.set_value(true);
// 		serial_read(NULL);

// 		// Gets input from controller joysticks
//         fwd = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
//         str = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
// 		rcw = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

// 		bool up = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
//     	bool down = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
//         bool left = controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
//         bool right = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);

//         //up,down,left,right
//         bool Y =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
//         bool A =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
//         bool X =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
//         bool B =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);

//         //left bumper, right bumper
//         bool L1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
//         bool R1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

//         //left trigger, right trigger
//         bool L2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
//         bool R2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
        
        
//         if(abs(fwd) < 10) {
//             fwd = 0;
//         }
//         if(abs(str) < 10) {
//             str = 0;
//         }
//         if(abs(rcw) < 10) {
//             rcw = 0;
//         }

// 		// pros::lcd::print(0, " Left X %d", fwd); 
//         pros::lcd::print(7, " Bucket %.3f", bucket.get_position());
// 		// pros::lcd::print(6, " Left %d", leftPot.get_angle());
// 		// pros::lcd::print(7, " Right %d", rightPot.get_angle()); 

//         //right joystick scaling
//         // rcw = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
//         // int sign = signum(rcw);
//         // double temp_rcw = abs(rcw)/127.0;
//         // //scale input based on a x^3.75 curve
//         // temp_rcw = pow(temp_rcw, 3.75);
//         // temp_rcw = temp_rcw * 127.0 * sign;
//         // rcw = (int)temp_rcw;

// 		// swerve drive!!!!
//     	// if(fwd == 0 && str == 0 && rcw == 0 && !idle) {
//         //     sdrive.move(0, 0, 0.005, 1);
//         //     idle = true;
//         // }else{
//         //     sdrive.move(fwd/127.0, str/127.0, rcw/1600.0, 1);
//         //     idle = false;
//         // }

//         //trigger the PID of the liftController to maintain height

//         //Lift controls
//         liftController.update();
//         if (X) {
//             liftController.goToHeight(LIFT_UP.getHeight());
//         }
//         else if (B) {
//             liftController.goToHeight(LIFT_DOWN.getHeight());
//         }

//         bucketController.update();
//         if (L2) {
//             bucketController.goToPosition(BUCKET_OUT.getPos());
//         }
//         else if (lastScore) {
//             bucketController.goToPosition(BUCKET_IN.getPos());
//             liftController.goToHeight(LIFT_DOWN.getHeight());
//         }
//         lastScore = L2;

//         // if(L2) {
//         //     // pros::lcd::print(4, "Going to ring height");
//         //     pros::Task bucketScore(BucketController().goToHeight, BucketController().ringHeight, "Lower Score Height");
//         //     pros::delay(100);
//         //     // BucketController().goToHeight(BucketController().ringHeight);

//         //     // pros::Task goToIdleHeight(LiftController().goToHeight, LiftController().idleHeight, "Idle Height");
//         //     // pros::delay(10);

//         // }

//         //trigger the PID of the liftController to maintain height
//         // liftController.update();
//         if (up) {
//             lift.move(60);
//         }else if (down) {
//             lift.move(-60);
//         } else {
//             lift.move(15);
//         }


//     	// if (up) {
//     	//     sdrive.reset_position();
// 		// 	pros::lcd::print(3, " up"); 
//     	// }
    
//         if (R2){
//             IntakeController().intakeForward(NULL);
//         }else if (R1){
//             IntakeController().intakeReverse(NULL);
//         }else {
//             IntakeController().stop(NULL);
//         }

// 		pros::delay(10);

//         //Toggle Mogo Clamp

//         if(L1) {
//             //closes clamp if currently toggled
//             if (clampToggle) {
//                 MogoClamp().closeClamp(NULL);
//                 clampToggle = false;
//             }
//             //opens clamp otherwise
//             else {
//                 MogoClamp().openClamp(NULL);
//                 clampToggle = true;
//             }
// 	    }
//     }
// }

#include "driveControl.h"
#include "serial/serial_comm.h"

/**
 * Takes input from controller joysticks
 * Controls intakes and macro execution using button presses
 */
void driveControl()
{
    // leftFrontTopMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    // leftFrontBottomMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    // rightFrontTopMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    // rightFrontBottomMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    // leftBackTopMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    // leftBackBottomMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    // rightBackTopMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    // rightBackBottomMotor.set_brake_mode(MOTOR_BRAKE_COAST);

    intake.set_brake_mode(MOTOR_BRAKE_COAST);
    liftLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
    liftRight.set_brake_mode(MOTOR_BRAKE_BRAKE);
    bucket.set_brake_mode(MOTOR_BRAKE_BRAKE);

    SwerveDrive sdrive;

    bool idle = false;
    lemlib::PID headingPID (100, 0, 400, 10, false);

    double holdAngle = 0;
    bool wasZero = false;

    LiftController liftController;
    liftController.zeroEncoder();
    BucketController bucketController;
    bucketController.zeroEncoder();

    bool lastScore = false;

    bool clampState = false;
    bool lastToggle = false;

    //Reset position
    // otos_offset[0] = -otos_data[0];
    // otos_offset[1] = -otos_data[1];
    // otos_offset[2] = -otos_data[2];

    bool intakeIn, intakeOut, score, toggleClamp, liftUp, liftDown, doink;

    imu.reset();

    bool doinkState = false;
    bool lastDoink = false;

	while (true)
	{
		// Gets input from controller joysticks
        float fwd = -controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        float str = -controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		float rcw = -controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // double robotHeading = -imu.get_heading() * M_PI/180;//Get Heading
        // double desiredDirection = atan2f(fwd, str) - M_PI/2;
        // double relativeDirection = -calcAngleDiff(desiredDirection, robotHeading);

        // double magnitude = sqrt(fwd*fwd+str*str);

        // double relFwd = magnitude * sin(relativeDirection);
        // double relStr = magnitude * cos(relativeDirection);

        // Scoring controls
        intakeIn = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
        intakeOut = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
        score = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
        toggleClamp = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
        liftUp =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
        liftDown =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
        doink = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);

        bool resetPosition = controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

		//right joystick scaling
        // int sign = signum(rcw);
        // double temp_rcw = abs(rcw)/127.0;
        // //scale input based on a x^3 curve
        // temp_rcw = pow(temp_rcw, 3);
        // temp_rcw = temp_rcw * 127.0 * sign;
        // rcw = (int)temp_rcw;

        // if (abs(rcw) < 5) {
        //     if (!wasZero) {
        //         wasZero = true;
        //         holdAngle = robotHeading;
        //         headingPID.reset();
        //     }
            
        //     rcw = -headingPID.update(calcAngleDiff(holdAngle, robotHeading));
        // }
        // else {
        //     wasZero = false;
        // }

        // if (resetPosition) {
        //     otos_offset[0] = -otos_data[0];
        //     otos_offset[1] = -otos_data[1];
        //     otos_offset[2] = -otos_data[2];

        //     imu.tare();
        // }

		//swerve drive!!!!
        // if(fwd == 0 && str == 0 && rcw == 0 && !idle) {
        //     sdrive.move(0, 0, 0.5, 1);
        //     idle = true;
        // }else{
        //     sdrive.move(fwd/127.0, str/127.0, rcw/1600.0, 1);
        //     idle = false;
        // }

        sdrive.move(fwd/127.0, str/127.0, rcw/1600.0, 1);


        //Lift controls
        liftController.update();
        if (liftUp) {
            liftController.goToHeight(LIFT_UP.getHeight());
        }
        else if (liftDown) {
            liftController.goToHeight(LIFT_DOWN.getHeight());
        }

        //Bucket controls
        bucketController.update();
        if (score) {
            bucketController.goToPosition(BUCKET_OUT.getPos());
        }
        else if (lastScore) {
            bucketController.goToPosition(BUCKET_IN.getPos());
            liftController.goToHeight(LIFT_DOWN.getHeight());
        }
        lastScore = score;

        if (intakeIn) {
            intake.move(127);
        }
        else if (intakeOut) {
            intake.move(-127);
        }
        else {
            intake.move(0);
        }

        if (toggleClamp && !lastToggle) {
            if (clampState) {
                mogoClamp.set_value(LOW);
            }
            else {
                mogoClamp.set_value(HIGH);
            }

            clampState = !clampState;
        }
        lastToggle = toggleClamp;

        // if (doink && !lastDoink) {
        //     if (doinkState) {
        //         doinker.set_value(LOW);
        //     }
        //     else {
        //         doinker.set_value(HIGH);
        //     }

        //     doinkState = !doinkState;
        // }
        // lastDoink = doink;

		pros::delay(10);
	}
}