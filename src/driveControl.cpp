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
        
        if(fwd < 10 && fwd > -10) {
            fwd = 0;
        }
        if(str < 10 && str > -10) {
            str = 0;
        }
        if(rcw < 10 && rcw > -10) {
            rcw = 0;
        }

		pros::lcd::print(0, " Left X %d", fwd); 
		pros::lcd::print(1, " Left Y %d", str);
		pros::lcd::print(2, " Right X %d", rcw); 

		//swerve drive!!!!
        // SwerveDriveWheel rightBack(&rightBackTopMotor, &rightBackBottomMotor, rightBackEncoder, testPID, false);
        // rightBack.move(speed4, angle4, 1);

    	sdrive.move(fwd/127.0, str/127.0, rcw/127.0, 1);


    	// if (up) {
    	//     driveTrain.reset_position();
		// 	pros::lcd::print(3, " up"); 
    	// }

		pros::delay(10);
	}
}