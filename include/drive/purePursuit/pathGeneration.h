// #ifndef _PATH_GENERATION
// #define _PATH_GENERATION

// #define PROS_USE_SIMPLE_NAMES
// #define PROS_USE_LITERALS
// #include "api.h"
// #include "init/utility.h"
// #include <vector>

// using namespace std;

// class PathGeneration {
// public:
// 	PathGeneration();

// 	/**
// 	* @brief sets the 2D vector of points, and the spacing
// 	* 
// 	* @param initPoints, desired 2D vector of points; spacing, the distance between points
// 	* @return a reference to the object
// 	*/
// 	PathGeneration& withPath(vector<vector<double>> initPoints, double spacing);
	
// 	/**
// 	* @brief sets smoothing values and tolerance
// 	*
// 	* @param smoothVal1 smoothing value 1
// 	* @param smoothVal2 smoothing value 2
// 	* @param smoothTolerance smooth tolerance
// 	* @return a reference to the object
// 	*/
// 	PathGeneration& withSmoothing(double smoothVal1, double smoothVal2, double smoothTolerance);
	
// 	/**
// 	* @brief limits the robot's velocity and acceleration
// 	* 
// 	* @param maxVel maximum velocity
// 	* @param maxAccel maximum acceleration
// 	* @return a reference to the object
// 	*/
// 	PathGeneration& withLimits(double maxVel, double maxAccel);
	
// 	/**
// 	* @brief sets the turnConstant
// 	* 
// 	* @param turnConstant the turning constant
// 	* @return a reference to the object
// 	*/
// 	PathGeneration& withTurnConstant(double turnConstant);

// 	/**
//      * @brief Generates a smooth path between a start and end using the waypoints as guidance
//      * 
//      * @param velList Reference to velList
//      * 
//      * @return list of points along the waypoints
//      */
// 	vector<vector<double>> generatePath(vector<double> &velList);

// private:
// 	/**
//      * @brief Generates a list of points and thetas between a given initial and final point/theta
//      *
//      * @param initX the x value of the initial point
//      * @param initY the y value of the initial point
//      * @param initTheta the direction of the robot at the initial point
//      * @param finalX the x value of the final point
//      * @param finalY the y value of the final point
//      * @param finalTheta the direction of the robot at the final point
//      * @param spacing distance between each point needed to be calculated between initial and final points
//      *
//      * @return 2d double vector containing all the points between the initial and final point, including both initial/final
//      */
// 	vector<vector<double>> generateLinearPath(double initX, double initY, double initTheta, double finalX, double finalY, double finalTheta, double spacing);
	
// 	/**
//      * @brief Converts the given list of points into a smooth path
//      * 
//      * @param path original list of points that needs to be smoothed
//      * @param weight_data data about weight used in smoothing calculations
//      * @param weight_smooth smoothing weight variable using in smoothing calculations
//      * @param tolerence variable using in smoothing calculations
//      * 
//      * @return list of all path points converted to smooth line
//      */
// 	vector<vector<double>> smooth(vector<vector<double>> pointsList, double a, double b, double tolerance);
	
// 	/**
//      * @brief Calculates and returns list of curvatures along sections of points along the robot's path 
//      * 
//      * @param pointsList list of points along the path of the robot
//      * 
//      * @return list of curvatures corresponding to each point along the path
//      */
// 	vector<double> calculateCurve(vector<vector<double>> pointsList);
	
// 	/**
//      * @brief Calculates and returns list of velocities for points along the path of the robot
//      * 
//      * @param pointsList list of points along the path of the robot
//      * @param curveList list of curvatures corresponding to each point along the path
//      * @param maxVelocity maximum velocity defined for the path
//      * @param maxAccel maximum acceleration defined for the path
//      * @param turnConstant value based on how slow the robot should go around turns
//      *
//      * @return list of target velocities corresponding to each point along the path of the robot
//      */
// 	vector<double> calculateVelocity(vector<vector<double>> pointsList, vector<double> curveList, double maxVelocity, double maxAccel, double turnConstant);
	
//     //initPoints: points that make up the path of motion; spacing: distance between consecutive points
// 	vector<vector<double>> initPoints;
// 	double spacing;

//     //constants related to smoothing out a path
// 	double smoothVal1;
// 	double smoothVal2;
// 	double smoothTolerance;

//     //maximum velocity and acceleration
// 	double maxVel;
// 	double maxAccel;

//     //constant relating to finding velocity when turning
// 	double turnConstant;
// };

// #endif