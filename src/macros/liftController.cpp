#include "macros/liftController.h"

//static keyword unnecessary in implementation, 
//use scope operator to define static functions of a class
double LiftController::fourBarPosition = 0;
double LiftController::targetPosition = 0;


void LiftController::liftUp(void *ignore)
{
    // fourBar.move_relative(100, 50);
    LiftController::targetPosition += 10;
}

void LiftController::liftDown(void *ignore)
{
    // fourBar.move_relative(-100, 50);
    LiftController::targetPosition -= 10;
    
}

lemlib::PID barPID (1,0,0, 10.0F, false);

void LiftController::PIDInit() {
    LiftController::fourBarPosition = fourBar.set_zero_position(0);
}

void LiftController::updatePID() {
    LiftController::fourBarPosition = fourBar.get_position();
    double error = LiftController::targetPosition - LiftController::fourBarPosition;
    float power = barPID.update(error);
    fourBar.move(power);
}