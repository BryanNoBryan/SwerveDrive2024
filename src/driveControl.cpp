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

    intakeLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
    intakeRight.set_brake_mode(MOTOR_BRAKE_BRAKE);

    LiftController liftController;

	while (true)
	{
		// Gets input from controller joysticks
        motorSpeedX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        motorSpeedY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

        bool up = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
    	bool down = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
        bool left = controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
        bool right = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);

        //up,down,left,right
        bool Y =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
        bool A =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
        bool X =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
        bool B =  controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);

        //trigger the PID of the liftController to maintain height
        liftController.update();
        if (up) {
            liftController.ascend(NULL);
        } 
        if (down) {
            liftController.descend(NULL);
        }
        if (right) {
            liftController.zeroEncoder();
        }

        // Strafing with automatic turn


		// Rotation


		//turnSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        if (controller.get_digital(DIGITAL_L2))
        {
            IntakeController().intakeForward(NULL);
        }
        else if (controller.get_digital(DIGITAL_L1))
        {
            IntakeController().intakeReverse(NULL);
        }
        else
        {
            IntakeController().stop(NULL);
        }

		pros::delay(10);
	}
}