#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

    controller.rumble(".");
    //Initialize chassis
	chassis.calibrate();
    chassis.setPose(0, 0, 0);

    // Start serial on desired port
    vexGenericSerialEnable(SERIALPORT - 1, 0);

    // Set BAUD rate
    vexGenericSerialBaudrate(SERIALPORT - 1, VEX_BAUD_RATE);

    //Print to brain's screen
    pros::Task screenTask([&]()
                          {

        while (true) {
            // rxtx_enable.set_value(true);
            //pros::Task arduinoData(serial_read);
            // print robot location to the brain screen
            pros::lcd::print(0, "PosX %4.2f PosY %4.2f PosH %4.2f", otos_data[0], otos_data[1], otos_data[2]);
            pros::lcd::print(1, "VelX %4.2f VelY %4.2f VelH %4.2f", otos_data[3], otos_data[4], otos_data[5]);
            pros::lcd::print(2, "AccX %4.2f AccY %4.2f AccH %4.2f", otos_data[6], otos_data[7], otos_data[8]);
            //pros::lcd::print(4, "%s", max485_data.substr(0, max485_data.size()/3));
            //pros::lcd::print(5, "%s", max485_data.substr(max485_data.size()/3, max485_data.size()/3));
            //pros::lcd::print(6, "%s", max485_data.substr(2 * max485_data.size() / 3, max485_data.size() / 3));
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        } });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    matchAuton();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    driveControl();
}