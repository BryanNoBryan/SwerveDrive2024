#ifndef _UTILITY
#define _UTILITY

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include <cmath>

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

#endif
