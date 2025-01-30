#include "init/utility.h"

Vector2d::Vector2d(double x, double y) : x(x), y(y) {

}

/**
 * Calculates signed difference between two headings, in out radians
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

double distanceFormula(vector<double> currentPosition, vector<double> lookAheadPosition) {
	return sqrt(pow(lookAheadPosition[0] - currentPosition[0], 2) + pow(lookAheadPosition[1] - currentPosition[1], 2));;
}

/**
 * Converts value from m/s to rpm
 */
double convertToRPM(double value, double wheelDiameter) {
	return value / (2 * M_PI * wheelDiameter * 2.54) * (100 * 2 * 60.0);
}

/**
 * Converts value from m/s to rpm
 */
double convertToRPM(int value, double wheelDiameter) {
	return value / (2 * M_PI * wheelDiameter * 2.54) * (100 * 2 * 60.0);
}

/**
 * Calculates dot product of two vectors
 */
double dot(vector<double> a, vector<double> b) {
	return a[0] * b[0] + a[1] * b[1];
}