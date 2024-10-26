#include "driveControl.h"
#include "stdio.h"

/**
 * Takes input from controller joysticks
 * Controls intakes and macro execution using button presses
 */
void driveControl()
{
	int motorSpeedX, motorSpeedY, turnSpeed;
	double currentHeading, neccesaryHeading;

	while (true)
	{
		// Gets input from controller joysticks
        motorSpeedX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        motorSpeedY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);


        // Strafing with automatic turn


		// Rotation


		//turnSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);


		


		pros::delay(10);
	}
}