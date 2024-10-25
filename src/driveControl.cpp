#include "driveControl.h"
#include "stdio.h"

/**
 * Takes input from controller joysticks
 * Controls intakes and macro execution using button presses
 */
void driveControl()
{
	int motorSpeedX, motorSpeedY, turnSpeed;

	while (true)
	{
		// Gets input from controller joysticks
        motorSpeedX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        motorSpeedY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		turnSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		bool up = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
    	bool down = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

		//swerve drive!!!!
    	driveTrain.moveTo(motorSpeedX, motorSpeedY, turnSpeed, 1);

    	if (up) {
    	    driveTrain.reset_position();
    	}


        // Strafing with automatic turn


		// Rotation


		//turnSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);


		


		pros::delay(10);
	}
}