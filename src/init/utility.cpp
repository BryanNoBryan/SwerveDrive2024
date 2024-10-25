#include "init/utility.h"

Vector2d::Vector2d(double x, double y) : x(x), y(y) {

}

int signum(double x) {
    if (x > 0) {
        return 1;
    } else if (x < 0) {
        return -1;
    } else {
        return 0;
    }
}

// This function normalizes the angle so it returns a value between -180° and 180° instead of 0° to 360°.
double angleWrap(double degrees) {

    while (degrees > 180) {
        degrees -= 2 * 180;
    }
    while (degrees < -180) {
        degrees += 2 * 180;
    }

    // keep in mind that the result is in degrees
    return degrees;
}
