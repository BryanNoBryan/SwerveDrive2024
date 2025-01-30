#ifndef _UTILITY
#define _UTILITY

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include <cmath>
#include <string>
#include <vector>

using namespace std;

extern std::string robot_problems;

class Vector2d {
    public:
        double x;
        double y;

        Vector2d(double x, double y);

};


/**
 * @brief Returns the sign of a number as an integer (1, 0, or -1)
 * 
 * @param value the number to get the sign of as an integer
 * 
 * @return the sign of the number as an integer
 */
int signum(int value);


/**
 * @brief Returns the sign of a number as a double (1, 0, or -1)
 * 
 * @param value the number to get the sign of as a double
 * 
 * @return the sign of the number as an integer
 */
int signum(double value);

/**
 * @brief Converts degrees to radians
 * 
 * @param degrees the number of degrees to convert to radians
 * 
 * @return the number of degrees in radians
 */
double degreesToRadians(double degrees);

/**
 * @brief Converts radians to degrees
 * 
 * @param radians the number of radians to convert to degrees
 * 
 * @return the number of radians in degrees
 */
double radiansToDegrees(double radians);


double angleWrap(double degrees);

/**
* @brief returns the difference between two angles, each from 0 to 2pi, in radians
*
* @param angle1 first angle
* @param angle2 second angle
* @return the difference between the two specified angles, shifted to the range -pi to pi
*/
double calcAngleDiff(double angle1, double angle2);

/**
 * @brief Calculates the distance between two points represented by vectors
 * 
 * @param currentPosition the first point represented by a vector
 * @param lookAheadPosition the second point represented by a vector
 * 
 * @return the distance between the two points as a double
 */
double distanceFormula(vector<double> currentPosition, vector<double> lookAheadPosition);

/**
 * @brief Converts a speed in meters per second to a speed in rotations per minute
 *
 * @param value the speed in meters per second as an double
 * @param wheelDiameter the diameter of the wheel in inches
 * 
 * @return the speed in rotations per minute
 */
double convertToRPM(double value, double wheelDiameter);


/**
 * @brief Converts a speed in meters per second to a speed in rotations per minute
 *
 * @param value the speed in meters per second as an integer
 * @param wheelDiameter the diameter of the wheel in inches
 * 
 * @return the speed in rotations per minute
 */
double convertToRPM(int value, double wheelDiameter);

/**
 * @brief Calculates the dot product of two vectors
 * 
 * @param a the first vector
 * @param b the second vector
 * 
 * @return the dot product of the two vectors as a double
 */
double dot(vector<double> a, vector<double> b);

#endif