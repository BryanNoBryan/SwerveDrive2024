// #include "drive/purePursuit/pathFollowing.h"
// #include "serial/serial_comm.h"

// //Constructor for PathFollowing, sets all values
// PathFollowing::PathFollowing()
// {
//     initPoints = {};
//     spacing = 1;
//     smoothVal1 = 0;
//     smoothVal2 = 0;
//     smoothTolerance = 0.001;
//     maxVel = 5;
//     maxAccel = 10;
//     turnConstant = 3;
//     lookAheadPointsNum = 10;
//     thresholdError = 0.5;
//     angleThreshold = 0.024;
//     kPDistance = 25;
//     kPAngle = 50;
//     minPower = 30;
//     speedCheckDistance = 5;
//     speedCheckSpeed = 0;
//     speedCheckTime = 1000000000000;
//     coordinateReset = false;
//     angleReset = false;

//     closeIndex = 1;
//     wheelD = 2.5;
// }

// //Setter method for initPoints and spacing variables
// PathFollowing& PathFollowing::withPath(vector<vector<double>> initPoints, double spacing){

//     this->initPoints = initPoints;
// 	this->spacing = spacing;
//     return *this;
// }

// //Setter method for smoothing variables
// PathFollowing& PathFollowing::withSmoothing(double smoothVal1, double smoothVal2, double smoothTolerance){

//     this->smoothVal1 = smoothVal1;
// 	this->smoothVal2 = smoothVal2;
//     this->smoothTolerance = smoothTolerance;
//     return *this;
// }

// //Setter method for maxVel and maxAccel
// PathFollowing& PathFollowing::withLimits(double maxVel, double maxAccel){

//     this->maxVel = maxVel;
// 	this->maxAccel = maxAccel;
//     return *this;
// }

// //Setter method for lookAheadPointsNum variable
// PathFollowing& PathFollowing::withLookAheadPointsNum(double lookAheadPointsNum){

//     this->lookAheadPointsNum = lookAheadPointsNum;
//     return *this;
// }

// //Setter method for the threshold variables
// PathFollowing& PathFollowing::withThresholdErrors(double thresholdError, double angleThreshold){

//     this->thresholdError = thresholdError;
//     this->angleThreshold = angleThreshold;
//     return *this;
// }

// //Setter method for the kPDistance and kPAngle variables
// PathFollowing& PathFollowing::withGains(double kPDistance, double kPAngle){

//     this->kPDistance = kPDistance;
//     this->kPAngle = kPAngle;
//     return *this;
// }

// //Setter method for the turnConstant variable
// PathFollowing& PathFollowing::withTurnConstant(double turnConstant){

//     this->turnConstant = turnConstant;
//     return *this;
// }

// //Setter method for the minPower variable
// PathFollowing& PathFollowing::withMinPower(double minPower){

//     this->minPower = minPower;
//     return *this;
// }

// //Setter method for speed check variables
// PathFollowing& PathFollowing::withSpeedCheck(double speedCheckDistance, double speedCheckSpeed, double speedCheckTime){

//     this->speedCheckDistance = speedCheckDistance;
//     this->speedCheckSpeed = speedCheckSpeed;
//     this->speedCheckTime = speedCheckTime;
//     return *this;
// }

// //Setter method for resetX and resetY variables
// PathFollowing& PathFollowing::withCoordinateReset(double resetX, double resetY){

//     this->resetX = resetX;
//     this->resetY = resetY;

//     coordinateReset = true;

//     return *this;
// }

// //Setter method for resetTheta variable
// PathFollowing& PathFollowing::withAngleReset(double resetTheta){

//     this->resetTheta = resetTheta;

//     angleReset = true;

//     return *this;
// }

// //Setter method for robot wheel diameter
// PathFollowing& PathFollowing::withWheelD(double wheelD){

//     this->wheelD = wheelD;

//     return *this;
// }


// void PathFollowing::ppMove(){

//     SwerveDrive sdrive;

//     vector<double> velList;
//     double timing = 0;

//     //Calls generatePath method using all of the parameter setting methods
//     vector<vector<double>> path = PathGeneration().withPath(initPoints, spacing)
//                                                   .withSmoothing(smoothVal1, smoothVal2, smoothTolerance)
//                                                   .withLimits(maxVel, maxAccel)
//                                                   .withTurnConstant(turnConstant)
//                                                   .generatePath(velList);

//     printf("Path Size: %d\n", path.size());

//     for(int i = 0; i < path.size(); i++){
//         printf("%.3f  %.3f  %.3f\n", path[i][0], path[i][1], path[i][2]);
//     }

//     // for(int i = 0; i < velList.size(); i++){
//     //     printf("%.3f\n", velList[i]);
//     // }

//     // for(int i = 0; i < path.size(); i++){
//     //     printf("%.3f  %.3f  %.3f\n", path[i][0], path[i][1], path[i][2]);
//     // }

//     //Runs while loop until robot position is within threshold to the destination point 
//     while((true)){

//         rxtx_enable.set_value(true);
//         serial_read(nullptr);

//         //Finds current robot position
//         vector<double> xyPos = {-otos_data[0], -otos_data[1]};
//         vector<double> robotPos = {xyPos[0], xyPos[1], -otos_data[2]};

//         printf("\nPosition: %.3f  %.3f  %.3f\n", robotPos[0], robotPos[1], robotPos[2]);
//         //printf("\nAngle Diff: %.3f", abs(calcAngleDiff(robotPos[2], path[path.size() - 1][2])));
//         //printf("\nDist: %.3f", distanceFormula(robotPos, path[path.size() - 1]));

//         //Checks if robot position has reached threshold to destination
//         if((abs(calcAngleDiff(robotPos[2], path[path.size() - 1][2])) <= angleThreshold) 
//             && (distanceFormula(robotPos, path[path.size() - 1]) <= thresholdError)){

//             //printf("\n\n\nthreshold error\n\n\n");

//             break;
//         }

//         //Finds the closest point
//         double closeness = distanceFormula(robotPos, path[closeIndex]);
//         int prevCloseIndex = closeIndex;

//         for(int i = closeIndex+1; i < path.size(); i++){
//             double dist = distanceFormula(robotPos, path[i]);

//             if(dist < closeness){
//                 closeIndex = i;
//                 closeness = dist;
//             }
//         }

//         //printf("Close Index %d\n", closeIndex);
        
//         //Finds the lookahead point
//         double lookAheadDist = spacing*lookAheadPointsNum;

//         vector<double> lookAheadPoint = findLookAheadPoint(robotPos, path, closeIndex, lookAheadPointsNum, lookAheadDist);

//         //printf("\n%.3f  %.3f  %.3f\n", lookAheadPoint[0], lookAheadPoint[1], lookAheadPoint[2]);

//         //Speed Check over a certain time
//         // if(distanceFormula(robotPos, path[path.size() - 1]) < speedCheckDistance && otos_data[3] < speedCheckSpeed && otos_data[4] < speedCheckSpeed){
//         //     timing += 10;
//         // }else{
//         //     timing = 0;
//         // }

//         // if(timing >= speedCheckTime){
//         //     //printf("\n\n\n speed check time \n\n\n");
//         //     break;
//         // }

//         //Calculates error between robot position and lookahead point
//         vector<double> error = getErrors(robotPos, lookAheadPoint);

//         //printf("%.3f  %.3f %.3f\n", error[0], error[1], error[2]);
        
//         //Determines maxPower based on motor gearset
//         // double motorGearset = leftBackMotor1.get_gearing();
//         // double maxRPM = 0;

//         // if(motorGearset == 1){
//         //     maxRPM = 100;
//         // }else if(motorGearset == 2){
//         //     maxRPM = 200;
//         // }else{
//         //     maxRPM = 600;
//         // }
//         double maxRPM = 600;

//         double maxPower = (convertToRPM(maxVel, wheelD) / maxRPM) * 127;

//         if(maxPower > 127){
//             maxPower = 127;
//         }

//         //Moves the robot
//         moveRobot(error, kPDistance, kPAngle, minPower, maxPower);

//         //Delay for end of while loop
//         pros::delay(10);
//     }

//     //Stops all robot motion
//     sdrive.move(0, 0, 0, 1);

//     //Resets coordinate and angle if reset variables
//     // if(coordinateReset){
//     //     PositionController().setPosition(resetX, resetY);
//     // }
    
//     // if(angleReset){
//     //     PositionController().setTheta(resetTheta);
//     // }
    
// }


// vector<double> PathFollowing::findLookAheadPoint(vector<double> coord, vector<vector<double>> pointsList, double closeIndex, double lookAheadPointsNum, double lookAheadDist){
    
//     vector<double> lookAheadPoint;

//     //Base case is if it reaches the end without finding an intersection
//     if((closeIndex + lookAheadPointsNum) >= pointsList.size()){
//         return pointsList[pointsList.size()-1];
//     }

//     //Creates initial variables
//     vector<double> E = pointsList[closeIndex];
//     vector<double> L = pointsList[closeIndex + lookAheadPointsNum];
//     vector<double> C = {coord[0], coord[1]};
//     double r = lookAheadDist;

//     //Establishing vectors from line segment
//     vector<double> d = {L[0]-E[0], L[1]-E[1]};
//     vector<double> f = {E[0]-C[0], E[1]-C[1]};

//     //Discriminant calculations
//     double a = dot(d, d);
//     double b = 2 * dot(f, d);
//     double c = dot(f, f) - r*r;
//     double discrim = b*b - 4*a*c;

//     //Determines if there is a lookahead point or not 
//     //using the discriminant value and t-values
//     if(discrim < 0){
//         //Recursive call to find the next lookahead points based on where this lookahead point was
//         lookAheadPoint = findLookAheadPoint(coord, pointsList, closeIndex, lookAheadPointsNum + 1, lookAheadDist);
//     }else{
//         double t1 = (-b-sqrt(discrim))/(2*a);
//         double t2 = (-b+sqrt(discrim))/(2*a);

//         if(0 <= t1 && t1 <= 1){
//             lookAheadPoint = {E[0] + t1*d[0], E[1] + t1*d[1], pointsList[closeIndex][2]};
//         }else if(0 <= t2 && t2 <= 1){
//             lookAheadPoint = {E[0] + t2*d[0], E[1] + t2*d[1], pointsList[closeIndex][2]};
//         }else{
//             //Recursive call to find the next lookahead points based on where this lookahead point was
//             lookAheadPoint = findLookAheadPoint(coord, pointsList, closeIndex, lookAheadPointsNum + 1, lookAheadDist);
//         }
//     }

//     return lookAheadPoint;
// }


// vector<double> PathFollowing::getErrors(vector<double> position, vector<double> lookAheadPoint){

//     vector<double> tempLook = {lookAheadPoint[0], lookAheadPoint[1], lookAheadPoint[2]};
    
//     //Initializes vector relError and calculates the diff in headings using the calcAngleDiff method
//     vector<double> relError = {0, 0, calcAngleDiff(tempLook[2], position[2])};

//     //Shifts lookAhead point based on the current robot position so
//     //the robot position is at (0,0)
//     tempLook[0] -= position[0];
//     tempLook[1] -= position[1];

//     //Adjusts lookAhead point values based on the heading of the robot
//     //which gives the relative error
//     relError[0] = tempLook[0]*cos(position[2]) - tempLook[1]*sin(position[2]);
//     relError[1] = tempLook[1]*cos(position[2]) + tempLook[0]*sin(position[2]);

//     return relError;
// }


// double PathFollowing::findPercentage(double xError, double yError)
// {
// 	if(abs(xError) < abs(yError)){
// 		return (1 - abs(xError / yError));
// 	}else{
// 		return (1 - abs(yError / xError));
// 	}
// }

// void PathFollowing::moveRobot(vector<double> errors, double kPDistance, double kPAngle, double minPower, double maxPower) {

//     SwerveDrive sdrive;

//     // Finds the new maximum power limit
// 	maxPower = min(kPDistance*sqrt((pow(errors[0], 2) + pow(errors[1], 2))), maxPower);

// 	if (maxPower > 127){
// 		maxPower = 127;
// 	}else if (maxPower < -127){
// 		maxPower = -127;
// 	}
// 	double xError = errors[0];
// 	double yError = errors[1];
// 	double angleError = errors[2];

// 	double leftFrontPower;
// 	double leftBackPower;
// 	double rightFrontPower;
// 	double rightBackPower;

//     // If the x and y errors have the same sign
// 	if (signum(xError) == signum(yError)){
// 		leftFrontPower = maxPower * signum(xError);
// 		rightBackPower = maxPower * signum(xError);
        

//         // if the magnitude of the x error is greater than the magnitude of y error
// 		//Check if this is supposed to be absolute value in condition
//         if (xError > yError){ 
// 			leftBackPower = -1 * maxPower * findPercentage(xError, yError);
// 			rightFrontPower = -1 * maxPower * findPercentage(xError, yError);
// 		}
//         // if the magnitude of x error is less than the magnitude of y error
//         else {
// 			leftBackPower = maxPower * findPercentage(xError, yError);
// 			rightFrontPower = maxPower * findPercentage(xError, yError);
// 		}
//     //If x and y errors have opposite signs
// 	}else {
//         // Left Back and Right Front should move at the max power in the direction of y
// 		leftBackPower = maxPower * signum(yError);
// 		rightFrontPower = maxPower * signum(yError);

//         /* 
//         int sgnLarger = signum(error[0] + error[1]);
//         lfm = sgnLarger * finalMaxPower * ratio;
//         rbm = sgnLarger * finalMaxPower * ratio;
//         */

//         // Left Front and Right Back should move at max power times the ratio with the sign of the larger error
// 		if (abs(xError) > abs(yError)) {
// 			leftFrontPower = signum(xError) * maxPower * findPercentage(xError, yError);
// 			rightBackPower = signum(xError) * maxPower * findPercentage(xError, yError);
// 		} else {
// 			leftFrontPower = signum(yError) * maxPower * findPercentage(xError, yError);
// 			rightBackPower = signum(yError) * maxPower * findPercentage(xError, yError);
// 		}
// 	}

//     //Changes power to left and right sides based on the angle error and kPAngle
// 	double anglePower = angleError * kPAngle;

// 	//printf("kPAngle: %.3f\n", kPAngle);

//     //increasing right power and decreasing left power by kpAngle * angle error 
// 	leftFrontPower += anglePower;
// 	leftBackPower += anglePower;
// 	rightFrontPower -= anglePower;
// 	rightBackPower -= anglePower;

// 	//Limits voltage of each motor under threshold and scales accordingly
// 	double maxCurrSpeed = max(max(abs(leftFrontPower), abs(leftBackPower)), max(abs(rightFrontPower), abs(rightBackPower)));
// 	if (maxCurrSpeed > maxPower){
//         //Rescales all powers to be within max limits
// 		leftFrontPower = leftFrontPower * (maxPower / maxCurrSpeed);
// 		leftBackPower = leftBackPower * (maxPower / maxCurrSpeed);
// 		rightFrontPower = rightFrontPower * (maxPower / maxCurrSpeed);
// 		rightBackPower = rightBackPower * (maxPower / maxCurrSpeed);
// 	}
// 	if (abs(leftFrontPower) < minPower && abs(leftBackPower) < minPower && abs(rightFrontPower) < minPower && abs(rightBackPower) < minPower){
//         //Rescales all powers to be within min and max limits
// 		leftFrontPower = leftFrontPower * (minPower / maxCurrSpeed);
// 		leftBackPower = leftBackPower * (minPower / maxCurrSpeed);
// 		rightFrontPower = rightFrontPower * (minPower / maxCurrSpeed);
// 		rightBackPower = rightBackPower * (minPower / maxCurrSpeed);
// 	}

//     //Moves the motors based on the powers calculated and scaled above
//     sdrive.move(maxPower/12 * -yError, maxPower/12 * -xError, 0, 1);
//     printf("%.3f %.3f\n\n", yError, xError);

// 	// leftFrontMotor1 = leftFrontPower;
// 	// //leftFrontMotor2 = leftFrontPower;
// 	// leftBackMotor1 = leftBackPower;
// 	// //leftBackMotor2 = leftBackPower;
// 	// rightFrontMotor1 = rightFrontPower;
// 	// //rightFrontMotor2 = rightFrontPower;
// 	// rightBackMotor1 = rightBackPower;
// 	// //rightBackMotor2 = rightBackPower;

// 	// printf("Motor speeds: %.3f, %.3f, %.3f, %.3f\n", leftFrontPower, rightBackPower, rightFrontPower, leftBackPower);
// }

// // void PathFollowing::moveRobot(vector<double> error, double kPDistance, double kPAngle, double minPower, double maxPower){

// //     double LF = 0;
// //     double LB = 0;
// //     double RF = 0;
// //     double RB = 0;

// //     double maxError = max(abs(error[0]), abs(error[1]));

// //     //Finds the new maximum power limit
// //     maxPower = min(kPDistance*sqrt((pow(error[0], 2) + pow(error[1], 2))), maxPower);

//     // if (maxPower > 127){
// 	// 	maxPower = 127;
// 	// }else if (maxPower < -127){
// 	// 	maxPower = -127;
// 	// }

// //     //Defines the ratio 
// //     double ratio = 1 - min(abs(error[0]), abs(error[1]))/maxError;

// //     //If the x and y errors have the same sign
// //     if((error[0] < 0 && error[1] < 0) || (error[0] > 0 && error[1] > 0)){
// //         LF += maxPower * signum(error[0]);
// //         RB += maxPower * signum(error[1]);

// //         if(error[0] < error[1]){
// //             LB += maxPower*ratio;
// //             RF += maxPower*ratio;
// //         }else if(error[0] >= error[1]){
// //             LB -= maxPower*ratio;
// //             RF -= maxPower*ratio;
// //         }
    
// //     //If x and y errors have opposite signs
// //     }else{
// //         LB += maxPower * signum(error[1]);
// //         RF += maxPower * signum(error[1]);

// //         double signE = 0;

// //         if(maxError == abs(error[0])){
// //             signE = signum(error[0]);
// //         }else{
// //             signE = signum(error[1]);
// //         }

// //         LF += abs(maxPower*ratio) * signE;
// //         RB += abs(maxPower*ratio) * signE;
// //     }

// //     //Changes power to left and right sides based on the angle error and kPAngle
// //     double changePower = error[2] * kPAngle;

// //     LF += changePower;
// //     LB += changePower;
// //     RF -= changePower;
// //     RB -= changePower;
    
// //     //Defines variables needed for scaling power values
// //     double scalingFactor = 1;
// //     vector<double> powerList = {LF, LB, RF, RB};

// //     //Finds the max and min power in the list of motor powers
// //     double maxPowerInList = *max_element(powerList.begin(), powerList.end());
// //     double minPowerInList = *min_element(powerList.begin(), powerList.end());

// //     //If the max or min is outside limits, creates a scaling factor to increase/decrease the powers
// //     if(maxPowerInList > maxPower) {
// //         scalingFactor = maxPowerInList / maxPower;

// //         //Rescales all powers to be within max limits
// //         powerList[0] /= scalingFactor;
// //         powerList[1] /= scalingFactor;
// //         powerList[2] /= scalingFactor;
// //         powerList[3] /= scalingFactor;
// //     }
    
// //     if(minPowerInList < minPower) {
// //         scalingFactor = minPowerInList / minPower;

// //         //Rescales all powers to be within min and max limits
// //         powerList[0] /= scalingFactor;
// //         powerList[1] /= scalingFactor;
// //         powerList[2] /= scalingFactor;
// //         powerList[3] /= scalingFactor;
// //     }
    
// //     //Moves the motors based on the powers calculated and scaled above
// //     leftFrontMotor1 = powerList[0];
// //     leftBackMotor1 = powerList[1];
// //     rightFrontMotor1 = powerList[2];
// //     rightBackMotor1 = powerList[3];

// //     printf("%.3f %.3f %.3f %.3f\n\n", powerList[0], powerList[1], powerList[2], powerList[3]);
// // }