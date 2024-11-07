#include "init/utility.h"

Vector2d::Vector2d(double x, double y) : x(x), y(y) {

}

/**
 * Calculates signed difference between two headings
 */
double calcAngleDiff(double angle1, double angle2){
	double diff = angle1 - angle2;

	if (diff > M_PI) {
		return diff - 2 * M_PI;
	}
	else if (diff < -M_PI) {
		return diff + 2 * M_PI;
	}
	else {
		return diff;
	}
}

/**
 * Returns sign of integer value
 */
int signum(int value) {
	return signum((double)value);
}

/**
 * Returns sign of double value
 */
int signum(double value) {
	return (value > 0) - (value < 0);
}

/**
 * Converts degrees to radians
 */
double degreesToRadians(double degrees) {
    return degrees * M_PI / 180;
}

/**
 * Converts radians to degrees
 */
double radiansToDegrees(double radians) {
    return radians * 180 / M_PI;
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
