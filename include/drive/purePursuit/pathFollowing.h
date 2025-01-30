// #ifndef _PATH_FOLLOWING
// #define _PATH_FOLLOWING

// #define PROS_USE_SIMPLE_NAMES
// #define PROS_USE_LITERALS

// #include "api.h"
// #include <vector>
// #include "drive/purePursuit/pathGeneration.h"
// #include "init/utility.h"
// #include "init/devices.h"
// #include "drive/swerveDrive.h"
// // #include "positioning/positionController.h"

// using namespace std;

// class PathFollowing
// {
// public:
// 	PathFollowing();

//     //Setter methods for all parameters relating to robot path
//     //Allows user to change parameters before calling ppMove

//     PathFollowing& withPath(vector<vector<double>> initPoints, double spacing);
//     PathFollowing& withSmoothing(double smoothVal1, double smoothVal2, double smoothTolerance);
//     PathFollowing& withLimits(double maxVel, double maxAccel);
//     PathFollowing& withLookAheadPointsNum(double lookAheadPointsNum);
//     PathFollowing& withThresholdErrors(double thresholdError, double angleThreshold);
//     PathFollowing& withGains(double kPDistance, double kPAngle);
//     PathFollowing& withTurnConstant(double turnConstant);
//     PathFollowing& withMinPower(double minPower);
//     PathFollowing& withSpeedCheck(double speedCheckDistance, double speedCheckSpeed, double speedCheckTime);
//     PathFollowing& withCoordinateReset(double resetX, double resetY);
//     PathFollowing& withAngleReset(double resetTheta);
//     PathFollowing& withWheelD(double wheelD);

//     /**
//      * @brief Calls the generatePath method from pathGeneration using the inputted parameters
//      */
//     void ppMove();

//     /**
//      * @brief Recursively goes through the robot path and finds the lookahead point
//      * 
//      * @param coord vector with the x, y, and theta of the robot's current position
//      * @param pointsList list of points on the robot's path
//      * @param closeIndex index of the current closest point to the robot
//      * @param lookAheadPointsNum number of points the robot is looking ahead
//      * @param lookAheadDist radius of the lookahead circle
//      * 
//      * @return lookAheadPoint, next lookahead point for the robot
//      */
//     vector<double> findLookAheadPoint(vector<double> coord, vector<vector<double>> pointsList, double closeIndex, double lookAheadPointsNum, double lookAheadDist);

//     /**
//      * @brief Finds the relative error between the current robot position and the lookahead point
//      * 
//      * @param position coordinate of the current robot position
//      * @param lookAheadPoint coordinate of the lookahead point
//      * 
//      * @return relError, a vector of doubles with the signed right/left distance, 
//      * signed foward/backward distance, and clockwise/counterclockwise angle between the two coordiantes
//      */
//     vector<double> getErrors(vector<double> position, vector<double> lookAheadPoint);

//     /**
//      * @brief Moves the robot according to motor powers calculated and scaled
//      * 
//      * @param error a vector of doubles from the getErrors method
//      * @param kPDistance distance
//      * @param kPAngle angle
//      * @param minPower minimum power limit
//      * @param maxPower maximum power limit
//      */
//     void moveRobot(vector<double> error, double kPDistance, double kPAngle, double minPower, double maxPower);
    

// private:
//     // initPoints: points that make up the path of motion; spacing: distance between consecutive points
//     vector<vector<double>> initPoints;
//     double spacing;

//     // constants related to smoothing out a path
//     double smoothVal1;
//     double smoothVal2;
//     double smoothTolerance;

//     // maximum velocity and acceleration
//     double maxVel;
//     double maxAccel;
    
//     // constant relating to finding velocity when turning
//     double turnConstant;
    
//     // number of points to look ahead when following a path
//     int lookAheadPointsNum;

//     // threshold error: distance from destination needed to stop; angleThreshold: maximum angle difference from destination needed to stop
//     double thresholdError;
//     double angleThreshold;

//     // constants related to robot motion
//     double kPDistance;
//     double kPAngle;

//     //minimum power allowed
//     double minPower;
    
//     //Distance threshold to check the distance between the robot position and endpoint over speedCheckTime
//     //Speed threshold to check current robot speed over speedCheckTime
//     double speedCheckDistance;
//     double speedCheckSpeed;
//     double speedCheckTime;

//     //Used to determine if x, y, and theta should be reset at the end 
//     bool coordinateReset;
//     bool angleReset;

//     //Values to set x, y, and theta when they are being reset
//     double resetX;
//     double resetY;
//     double resetTheta;

//     //Refers to the index of the closest point in the path vector
//     int closeIndex;
    
//     //Refers to the set wheel diameter
//     double wheelD;

//     /**
//      * @brief determines the ratio: one minus the unsigned ratio between the smaller error and the larger error
//      * 
//      * @param xError the relative x error between the current robot position and lookAheadPoint
//      * @param yError the relative y error between the current robot position and lookAheadPoint
//      * @return the calculated ratio
//      */
//     double findPercentage(double xError, double yError);
// };

// #endif