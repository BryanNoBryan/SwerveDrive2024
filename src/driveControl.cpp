#include "driveControl.h"

void driveControl() {
    bool up = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
    bool down = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

    int32_t left_y = -1 * controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int32_t left_x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    int32_t right_x = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //swerve drive!!!!
    driveTrain.moveTo(left_x, left_y, right_x, 1);

    if (up) {
        driveTrain.reset_position();
    }




    // if (up) {
    //     LiftController::liftUp(0);
    //     //as opposed to , which creates a new obj every time
    //     //LiftController().liftUp(0);
    // }
    // if (down) {
    //     LiftController::liftDown(0);
    // }
}