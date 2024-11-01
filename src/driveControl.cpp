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

		// pros::lcd::print(0, " leftx %d", motorSpeedX); 
		// pros::lcd::print(1, " leftx %d", motorSpeedY);
		// pros::lcd::print(2, " leftx %d", turnSpeed); 

		

		//swerve drive!!!!
    	driveTrain.moveTo(motorSpeedX, motorSpeedY, turnSpeed, 1);

    	if (up) {
    	    driveTrain.reset_position();
			pros::lcd::print(3, " up"); 
    	}


        // Strafing with automatic turn


		// Rotation


		//turnSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);


		


		pros::delay(10);
	}
}