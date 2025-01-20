#include "driveControl.h"
#include "stdio.h"
#include "serial/serial_comm.h"

/**
 * Takes input from controller joysticks
 * Controls intakes and macro execution using button presses
 */
void driveControl()
{
    int fwd, str, rcw;
    bool clampToggle = false;

    const double RADIUS = sqrt(pow(TRACK_LENGTH, 2) + pow(TRACK_WIDTH, 2));
    lemlib::PID testPID (1, 0, 0, 10, false);

    SwerveDrive sdrive;
    // sdrive.reset_position();

    intakeLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
    intakeRight.set_brake_mode(MOTOR_BRAKE_BRAKE);

    LiftController liftController;

	while (true)
	{
		rxtx_enable.set_value(true);
		serial_read(NULL);

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
    	sdrive.move(fwd/127.0, str/127.0, rcw/254.0, 1);

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


    	if (up) {
    	    sdrive.reset_position();
			pros::lcd::print(3, " up"); 
    	}
    
        if (controller.get_digital(DIGITAL_L2)){
            IntakeController().intakeForward(NULL);
        }else if (controller.get_digital(DIGITAL_L1)){
            IntakeController().intakeReverse(NULL);
        }else {
            IntakeController().stop(NULL);
        }

		pros::delay(10);

        //Toggle Mogo Clamp
        bool L1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);

        if(L1) {
            //closes clamp if currently toggled
            if (clampToggle) {
                MogoClamp().closeClamp(NULL);
                clampToggle = false;
            }
            //opens clamp otherwise
            else {
                MogoClamp().openClamp(NULL);
                clampToggle = true;
            }
	    }
    }
}