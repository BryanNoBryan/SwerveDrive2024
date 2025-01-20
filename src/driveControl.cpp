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
    bool idle = false;

    const double RADIUS = sqrt(pow(TRACK_LENGTH, 2) + pow(TRACK_WIDTH, 2));
    lemlib::PID testPID (1, 0, 0, 10, false);

    SwerveDrive sdrive;
    // sdrive.reset_position();

    intake.set_brake_mode(MOTOR_BRAKE_BRAKE);
    liftLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
    liftRight.set_brake_mode(MOTOR_BRAKE_BRAKE);

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

        //left bumper, right bumper
        bool L1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
        bool R1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

        //left trigger, right trigger
        bool L2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
        bool R2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
        
        
        if(abs(fwd) < 10) {
            fwd = 0;
        }
        if(abs(str) < 10) {
            str = 0;
        }
        if(abs(rcw) < 10) {
            rcw = 0;
        }

		// pros::lcd::print(0, " Left X %d", fwd); 
		// pros::lcd::print(1, " Left Y %d", str);
		// pros::lcd::print(2, " Right X %d", rcw); 

        //right joystick scaling
        rcw = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        int sign = signum(rcw);
        double temp_rcw = abs(rcw)/127.0;
        //scale input based on a x^3.75 curve
        temp_rcw = pow(temp_rcw, 3.75);
        temp_rcw = temp_rcw * 127.0 * sign;
        rcw = (int)temp_rcw;

		//swerve drive!!!!
    	if(fwd == 0 && str == 0 && rcw == 0 && !idle) {
            sdrive.move(0, 0, 0.005, 1);
            idle = true;
        }else{
            sdrive.move(fwd/127.0, str/127.0, rcw/1600.0, 1);
            idle = false;
        }

        //trigger the PID of the liftController to maintain height
        if(L2) {
            pros::Task goToLowerScore(LiftController().goToHeight, LiftController().lowerScoreHeight, "Lower Score Height");
            pros::delay(1000);

            pros::Task goToIdleHeight(LiftController().goToHeight, LiftController().idleHeight, "Idle Height");
            pros::delay(10);

        }

        //trigger the PID of the liftController to maintain height
        // liftController.update();
        if (up) {
            lift.move(60);
        }else if (down) {
            lift.move(-60);
        } else {
            lift.move(0);
        }


    	// if (up) {
    	//     sdrive.reset_position();
		// 	pros::lcd::print(3, " up"); 
    	// }
    
        if (R2){
            IntakeController().intakeForward(NULL);
        }else if (R1){
            IntakeController().intakeReverse(NULL);
        }else {
            IntakeController().stop(NULL);
        }

		pros::delay(10);
	}
}