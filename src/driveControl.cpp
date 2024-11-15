#include "driveControl.h"

/**
 * Takes input from controller joysticks
 * Controls intakes and macro execution using button presses
 */
void driveControl()
{
	int fwd, str, rcw;

    const double RADIUS = sqrt(pow(TRACK_LENGTH, 2) + pow(TRACK_WIDTH, 2));
    lemlib::PID testPID (1, 0, 0, 10, false);

    SwerveDrive sdrive;
    // sdrive.reset_position();

	while (true)
	{
		// Gets input from controller joysticks
        fwd = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        str = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		rcw = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		bool up = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
    	bool down = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
        bool left = controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
        bool right = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);

        //up,down,left,right
        bool Y =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
        bool A =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
        bool X =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
        bool B =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
        
        
        
        if(abs(fwd) < 10) {
            fwd = 0;
        }
        if(abs(str) < 10) {
            str = 0;
        }
        if(abs(rcw) < 10) {
            rcw = 0;
        }

		pros::lcd::print(0, " Left X %d", fwd); 
		pros::lcd::print(1, " Left Y %d", str);
		pros::lcd::print(2, " Right X %d", rcw); 

		//swerve drive!!!!
        // SwerveDriveWheel rightFront(&rightFrontTopMotor, &rightBackBottomMotor, &rightFrontEncoder, testPID, true);

        // rightFront.move(100, 0, 1);


        // rightBack.move(speed4, angle4, 1);

    	sdrive.move(fwd/127.0, str/127.0, rcw/127.0, 1);


        
//         if (up) {
//             intake.move(127);
//         } else if (down) {
//             intake.move(-127);
//         } else {
//             intake.move(0);
//         }

        

//         if (right) {
            
// leftFrontTopMotor.move(Y ? -127 : 0);
// leftFrontBottomMotor.move(Y ? 127 : 0);

// // Left Back
// leftBackTopMotor.move(X ? -127 : 0);
// leftBackBottomMotor.move(X ? 127 : 0);

// // Right Front
// rightFrontTopMotor.move(A ? -127 : 0);
// rightFrontBottomMotor.move(A ? 127: 0);

// // Right Back
// rightBackTopMotor.move(B ? -127 : 0);
// rightBackBottomMotor.move(B ? 127 : 0);

// leftFrontTopMotor.move(-127);
// leftFrontBottomMotor.move(127);

// // Left Back
// leftBackTopMotor.move(-127);
// leftBackBottomMotor.move(127);

// // Right Front
// // rightFrontTopMotor.move(-127);
// // rightFrontBottomMotor.move(127);

// // Right Back
// rightBackTopMotor.move(-127);
// rightBackBottomMotor.move(127);

//         } else {
// leftFrontTopMotor.move(0);
// leftFrontBottomMotor.move(0);

// // Left Back
// leftBackTopMotor.move(0);
// leftBackBottomMotor.move(0);

// // Right Front
// rightFrontTopMotor.move(0);
// rightFrontBottomMotor.move(0);

// // Right Back
// rightBackTopMotor.move(0);
// rightBackBottomMotor.move(0);
//         }

    	// if (up) {
    	//     driveTrain.reset_position();
		// 	pros::lcd::print(3, " up"); 
    	// }

		pros::delay(10);
	}
}