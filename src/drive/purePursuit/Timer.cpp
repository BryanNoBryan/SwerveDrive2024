#include "drive/purePursuit/Timer.h"

void Timer::start() {
    start_time = pros::millis();
}

double Timer::elapsed_time() {
    return pros::millis() - start_time;
}
