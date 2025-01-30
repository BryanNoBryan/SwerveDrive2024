// #include "drive/purePursuit/pathGeneration.h"

// PathGeneration::PathGeneration() {
// 	initPoints = {};
// 	spacing = 1;
// 	smoothVal1 = 0;
// 	smoothVal2 = 0;
// 	smoothTolerance = 0.001;
// 	maxVel = 5;
// 	maxAccel = 10;
// 	turnConstant = 3;
// }

// PathGeneration& PathGeneration::withPath(vector<vector<double>> initPoints, double spacing) {
// 	this->initPoints = initPoints;
// 	this->spacing = spacing;
// 	return *this;
// }

// PathGeneration& PathGeneration::withSmoothing(double smoothVal1, double smoothVal2, double smoothTolerance) {
// 	this->smoothVal1 = smoothVal1;
// 	this->smoothVal2 = smoothVal2;
// 	this->smoothTolerance = smoothTolerance;
// 	return *this;
// }

// PathGeneration& PathGeneration::withLimits(double maxVel, double maxAccel){
// 	this->maxVel = maxVel;
// 	this->maxAccel = maxAccel;
// 	return *this;
// }

// PathGeneration& PathGeneration::withTurnConstant(double turnConstant){
// 	this->turnConstant = turnConstant;
// 	return *this;
// }

// vector<vector<double>> PathGeneration::generateLinearPath(double initX, double initY, double initTheta, double finalX, double finalY, double finalTheta, double spacing) {
// 	vector<vector<double>> pointsList = { {0.0} };
// 	pointsList = {};

// 	//Finds the vector drawn from the start point to the end point
// 	vector<double> changeVector = { finalX - initX, finalY - initY };

// 	//Uses Pythagorean theorem to calculate magnitude of changeVector
// 	double magnitude = sqrt(pow(changeVector[0], 2) + pow(changeVector[1], 2));

// 	//Calculates the number of waypoints that need to be drawn
// 	double numPoints = ceil(magnitude / spacing);

// 	//Find the unit vector and multiply by spacing
// 	changeVector[0] = changeVector[0] * spacing / magnitude;
// 	changeVector[1] = changeVector[1] * spacing / magnitude;

// 	//Traverse through each point and save each point into vector
// 	for (int i = 0; i < numPoints; i++) {
// 		vector<double> newVector = { initX + changeVector[0] * i, initY + changeVector[1] * i, 10 };
// 		pointsList.push_back(newVector);
// 	}

// 	//Add the ending point to the list
// 	vector<double> finalVector{ finalX, finalY, finalTheta };
// 	pointsList.push_back(finalVector);


// 	double totalChange = calcAngleDiff(finalTheta, initTheta);
// 	double maxChange = totalChange / (pointsList.size() - 1);

// 	for (int i = 0; i < pointsList.size(); i++) {
// 		pointsList[i][2] = initTheta + i * maxChange;
// 	}

// 	return pointsList;
// }

// vector<vector<double>> PathGeneration::smooth(vector<vector<double>> pointsList, double a, double b, double tolerance){
// 	//Copy vector
// 	vector<vector<double>> newPointsList = pointsList;

// 	double change = tolerance;

// 	//Loops until change is within the acceptable tolerance
// 	while (change >= tolerance)
// 	{
// 		change = 0.0;

// 		//Loops through all points
// 		for (int i = 1; i < pointsList.size() - 1; i++)
// 		{
// 			//Loops through x and y coordinates for each point
// 			for (int j = 0; j < 2; j++)
// 			{
// 				//Creates an auxiliary variable for manipulation
// 				double aux = newPointsList[i][j];

// 				//Creates new point based on weight data and weight of smoothing
// 				newPointsList[i][j] += a * (pointsList[i][j] - newPointsList[i][j]) + b * (newPointsList[i - 1][j] + newPointsList[i + 1][j] - (2.0 * newPointsList[i][j]));

// 				//Updates change based on new point
// 				change += abs(aux - newPointsList[i][j]);
// 			}
// 		}
// 	}
// 	return newPointsList;
// }

// vector<double> PathGeneration::calculateCurve(vector<vector<double>> pointsList) {
// 	//Initialize curve list as vector with the first value as 0.0
// 	vector<double> curveList = { 0.0 };
// 	curveList = {};
// 	curveList.push_back(0.0);

// 	//Calculate curvature at each point excluding the first and last points
// 	for (int i = 1; i < pointsList.size() - 1; i++){
// 		//Gets the x-coordinates of the current point and previous point
// 		double x1 = pointsList[i][0];
// 		double x2 = pointsList[i - 1][0];

// 		//Prevents error when dividing by (x1-x2)
// 		if (x1 == x2){
// 			x1 += 0.001;
// 		}

// 		//Gets the x-coordinate of the next point
// 		double x3 = pointsList[i + 1][0];

// 		//Gets the y-coordinate of the current, previous, and next points
// 		double y1 = pointsList[i][1];
// 		double y2 = pointsList[i - 1][1];
// 		double y3 = pointsList[i + 1][1];

// 		//Intermediate constants used for calculations
// 		double k1 = 0.5 * (pow(x1, 2) + pow(y1, 2) - pow(x2, 2) - pow(y2, 2)) / (x1 - x2);
// 		double k2 = (y1 - y2) / (x1 - x2);
// 		double b = 0.5 * (pow(x2, 2) - 2 * x2 * k1 + pow(y2, 2) - pow(x3, 2) + 2 * x3 * k1 - pow(y3, 2)) / (x3 * k2 - y3 + y2 - x2 * k2);
// 		double a = k1 - k2 * b;

// 		//Push curvature value to vector
// 		curveList.push_back(1 / sqrt(pow(x1 - a, 2) + pow(y1 - b, 2)));
// 	}

// 	//Add curvature at last point as 0.0
// 	curveList.push_back(0.0);
// 	return curveList;
// }

// vector<double> PathGeneration::calculateVelocity(vector<vector<double>> pointsList, vector<double> curveList, double maxVelocity, double maxAccel, double turnConstant){
// 	int num_pts = pointsList.size();

//     // set last velocity to 0
//     vector<double> velList(num_pts);
//     velList[num_pts - 1] = 0;

//     for(int i = num_pts - 2; i >= 0; i--) {
//         // distance between point and next point, in inches
//         double dist = distanceFormula(pointsList[i+1], pointsList[i]);

// 		// convert inches to meters
// 		dist *= 0.0254;

//         // target velocity of current point, in m/s
// 		double correction = 0;
// 		if (curveList[i] == 0.0)
// 			correction = 0.001;
// 		double vel = min(maxVelocity, turnConstant / (curveList[i] + correction));
//         velList[i] = min(vel, sqrt(pow(velList[i+1], 2) + 2*maxAccel*dist*0.0254));

//     }
//     return velList;
// }

// vector<vector<double>> PathGeneration::generatePath(vector<double> &velList){
// 	//Gets the waypoints for robot path
//     vector<vector<double>> waypoints = initPoints;

//     //Initializes vector for all points on path
//     vector<vector<double>> allPoints;

//     //Initializes vector for curvature of all points on path
//     vector<double> curvatureOfPoints;

//     //Finds the number of waypoints
//     int numWP = waypoints.size();

//     //Runs for the number of paths that need to be created
//     for(int i = 1; i < numWP; i++){
//         //Initializest the two waypoints the linear path will be between
//         vector<double> wp1 = waypoints[i-1];
//         vector<double> wp2 = waypoints[i];

//         //Gets list of points between the waypoints
//         vector<vector<double>> betweenPoints = generateLinearPath(wp1[0], wp1[1], wp1[2], wp2[0], wp2[1], wp2[2], spacing);

//         //Adds the points for this lienar path to the list of all points
//         allPoints.insert(allPoints.end(), betweenPoints.begin(), betweenPoints.end());

//         //Removes the last point since that will be added again in the next iteration
//         allPoints.pop_back();
//     }

//     //Adds the last point that was deleted in the last iteration of the for loop
//     allPoints.push_back(waypoints[numWP-1]);

//     //Smooths the entire path
//     allPoints = smooth(allPoints, smoothVal1, smoothVal2, smoothTolerance);

//     //Calculates curvature of smoothed points
//     curvatureOfPoints = calculateCurve(allPoints);

//     //Calculates the velocity at each point on the path
//     velList = calculateVelocity(allPoints, curvatureOfPoints, maxVel, maxAccel, turnConstant);

//     return allPoints;
// }