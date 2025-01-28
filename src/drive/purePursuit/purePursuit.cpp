#include "drive/purePursuit/purePursuit.h"
#include "serial/serial_comm.h"

void purePursuit::runPath(vector<PPoint> path) {
    purePursuit::pointer = 1;
    purePursuit::endCount = 0;
    purePursuit::endTheta = 1000;

    purePursuit::setVels = {0, 0, 0};

    run(path);
}

void purePursuit::runPath(vector<PPoint> path, double endTheta) {
    purePursuit::pointer = 1;
    purePursuit::endCount = 0;
    purePursuit::endTheta = endTheta;

    purePursuit::setVels = {0, 0, 0};

    run(path);
}

void purePursuit::run(vector<PPoint> path) {
    purePursuit::curXVel = 0;
    purePursuit::curYVel = 0;
    purePursuit::curThetaVel = 0;

    purePursuit::xPID.reset();
    purePursuit::yPID.reset();
    purePursuit::thetaPID.reset();

    lemlib::Pose pos(otos_data[0], otos_data[1], otos_data[2]);

    path.insert(path.begin(), PPoint(pos.x, pos.y, pos.theta));
    purePursuit::lastPosition = vector<double> {pos.x, pos.y, pos.theta};

    bool overshot = false;

    auto startTime = chrono::steady_clock::now();
    auto loopTime = chrono::steady_clock::now();
    
    while (purePursuit::endCount < 3) {
        lemlib::Pose pos(otos_data[0], otos_data[1], otos_data[2]);

        // Ensures the target point is not the last point
        if (path.size() - 1 > pointer) {
            // Checks if the target point is within the radius of the robot
            if (hypot(path[pointer].x - pos.x, path[pointer].y - pos.y) < path[pointer].radius) {
                // Proceeds to the next point
                pointer += 1;
            }
        }

        vector<double> target = purePursuit::robotToLine(path[pointer - 1], path[pointer], vector<double> {pos.x, pos.y});
        
        // Checks error condition
        bool error = false;
        if (target[0] == 1E10) {
            target = vector<double> {path[pointer].x, path[pointer].y};
            error = true;
        }

        double xSpeed = 0, ySpeed = 0;
        // Checks if the target is the last point in the path or if we have already passed the last point
        if (path[pointer].strafe && ((target[0] == path[path.size() - 1].x && target[1] == path[path.size() - 1].y && !error) || overshot || path[pointer].fieldCentric)){
            // Calculate x speed
            double x = purePursuit::limitValue((target[0] - pos.x) / path[pointer].radius, 0, -1, 0, 1);
            x *= purePursuit::limitValue((abs(target[0] - pos.x) / divider), 0, -1, 0, 1);
            x = purePursuit::limitValue(-x, -minSpeed, -path[pointer].maxSpeed, minSpeed, path[pointer].maxSpeed);

            // Calculate y speed
            double y = purePursuit::limitValue((target[1] - pos.y) / path[pointer].radius, 0, -1, 0, 1);
            y *= purePursuit::limitValue((abs(target[1] - pos.y) / divider), 0, -1, 0, 1);
            y = purePursuit::limitValue(-y, -minSpeed, -path[pointer].maxSpeed, minSpeed, path[pointer].maxSpeed);

            // Set field centric speed
            xSpeed = x * cos(pos.theta) - y * sin(pos.theta);
            xSpeed = y * cos(pos.theta) + x * sin(pos.theta);

            // Always use this if statement
            overshot = true;
        } else {
            // Get hypot of the x and y error
            double relativeDist = sqrt(pow(target[0] - pos.x, 2) + pow(target[1] - pos.y, 2));
            
            // Calculate speed
            double speed = purePursuit::limitValue(abs(relativeDist) / path[pointer].radius, 0, -1, 0, 1);
            speed *= purePursuit::limitValue((abs(relativeDist) / ((divider / 10) * path[pointer].radius)), 0, -1, 0, 1);
            speed = purePursuit::limitValue(speed, -minSpeed, -path[pointer].maxSpeed, minSpeed, path[pointer].maxSpeed);
            
            xSpeed = speed * sin(path[pointer].theta);
            ySpeed = speed * cos(path[pointer].theta);
        }


        double relativePointAngle;
        // Checks if the target is the last point in the path or if we have already passed the last point
        if (path[pointer].strafe && ((target[0] == path[path.size() - 1].x && target[1] == path[path.size() - 1].y && !error) || overshot || path[pointer].fieldCentric)) {
            double angleToPoint;

            if (purePursuit::endTheta == 1000) {
                // Target the angle for robot to "follow line" with the path offset
                angleToPoint = atan2(path[pointer - 1].x - path[pointer - 2].x, path[pointer - 1].y - path[pointer - 2].y) + path[pointer].theta;
            } else {
                // Target the ending theta
                angleToPoint = endTheta;
            }
            relativePointAngle = -purePursuit::angleWrap(angleToPoint + pos.theta);
            
            overshot = true;
        } else {
            // Calculate angle for robot to follow the line
            double angleToPoint = atan2(target[0] - pos.x, target[1] - pos.y) + path[pointer].theta;
            relativePointAngle = -purePursuit::angleWrap(angleToPoint + pos.theta);
        }

        double turnSpeed = purePursuit::limitValue(relativePointAngle / 70.0, 0, -path[pointer].turnSpeed, 0, path[pointer].turnSpeed);

        // Sets the max velocity of the robot (x and y in inches, angle in degrees)
        xSpeed *= 48;
        ySpeed *= 48;
        turnSpeed *= 180;

        double xVel = (pos.x - purePursuit::lastPosition[0]) * (1000.0 / (chrono::steady_clock::now() - loopTime).count());
        double yVel = (pos.y - purePursuit::lastPosition[1]) * (1000.0 / (chrono::steady_clock::now() - loopTime).count());
        double thetaVel = (pos.theta - purePursuit::lastPosition[2]) * (1000.0 / (chrono::steady_clock::now() - loopTime).count());

        purePursuit::curXVel += xPID.update(xSpeed - xVel);
        purePursuit::curYVel += yPID.update(ySpeed - yVel);
        purePursuit::curThetaVel += thetaPID.update(thetaVel - turnSpeed);

        purePursuit::curXVel = purePursuit::limitValue(curXVel, 0, -1, 0, 1);
        purePursuit::curYVel = purePursuit::limitValue(curYVel, 0, -1, 0, 1);
        purePursuit::curThetaVel = purePursuit::limitValue(curThetaVel, 0, -1, 0, 1);

        printf("Current Y Position: %f", pos.y);

        //chassis.arcade(curYVel * 127, curThetaVel * 127);
        purePursuit::sDrive.move(curXVel, curYVel, curThetaVel, 1);



        // Is the path finished?
        double xError = path[path.size() - 1].x - pos.x;
        double yError = path[path.size() - 1].y - pos.y;
        double thetaError = endTheta - pos.theta;

        // Check theta
        bool theta = false;
        if (endTheta == 1000 || abs(thetaError) < tolerance[2]) {
            theta = true;
        }

        if ((abs(xError) < tolerance[0] && abs(yError) < tolerance[1] && theta && pointer == path.size() - 1) ||
        (timeout != -1 && (chrono::steady_clock::now() - startTime).count() > purePursuit::timeout) ||
        (purePursuit::stopAtWall && hypot(xVel, yVel) < 2 && pointer == path.size() - 1 && (chrono::steady_clock::now() - startTime).count() > 500)){
            purePursuit::endCount += 1;
        } else {
            purePursuit::endCount = 0;
        }

        purePursuit::lastPosition = vector<double> {pos.x, pos.y, pos.theta};
        loopTime = chrono::steady_clock::now();
    }
    
    // Stop
    //chassis.arcade(0, 0);
    purePursuit::sDrive.move(0, 0, 0, 1);
}

vector<double> purePursuit::robotToLine(PPoint p1, PPoint p2, vector<double> pos) {
    double slope = (p2.y - p1.y) / ((p2.x - p1.x == 0 ? 1e-10 : p2.x - p1.x));
    double yIntercept = p2.y - (slope * p2.x);
    double x = pos[0];
    double y = pos[1];

    double a = 1 + pow(slope, 2);
    double b = (slope * yIntercept * 2) + (-x * 2) + (-y * 2 * slope);
    double c = pow(yIntercept, 2) + (-y * 2 * yIntercept) - pow(p2.radius, 2) + pow(x, 2) + pow(y, 2);
    
    // Start calculating the quadratic formula
    double d = pow(b, 2) - (4 * a * c);
    if (d >= 0) {
        // Find the x values where the path intercepts with the robot's radius
        double sol1 = (-b - sqrt(d) / (2 * a));
        double sol2 = (-b + sqrt(d) / (2 * a));

        // Find the y values for the x solutions
        double y1 = slope * sol1 + yIntercept;
        double y2 = slope * sol2 + yIntercept;

        // Catch to ensure the solutions are within the path
        if ((y1 - p1.y < 0 && y1 - p2.y < 0) || (p1.y - y1 < 0 && p2.y - y1 < 0)) {
            if ((y2 - p1.y < 0 && y2 - p2.y < 0) || (p1.y - y2 < 0 && p2.y - y2 < 0)) {
                return vector<double> {1E10, 1E10, 1E10};
            }
        }
        if ((sol1 - p1.x < 0 && sol1 - p2.x < 0) || (p1.x - sol1 < 0 && p2.x - sol1 < 0)) {
            if ((sol2 - p1.x < 0 && sol2 - p2.x < 0) || (p1.x - sol2 < 0 && p2.x - sol2 < 0)) {
                return vector<double> {1E10, 1E10, 1E10};
            }
        }

        // Calculates the error to from the solution to the path point
        double error1 = abs(p2.x - sol1) + abs(p2.y - y1);
        double error2 = abs(p2.x - sol2) + abs(p2.y - y2);

        if (error1 < error2) {
            return vector<double> {sol1, y1};
        } else {
            return vector<double> {sol2, y2};
        }
    } else {
        return vector<double> {1E10, 1E10};
    }
}

double purePursuit::limitValue(double num, double minNeg, double maxNeg, double minPos, double maxPos) {
    if (num < 0) {
        if (num < maxNeg) {
            return maxNeg;
        } else if (num > minNeg) {
            return minNeg;
        }
    } else {
        if (num < minPos) {
            return minPos;
        } else if (num > maxPos) {
            return maxPos;
        }
    }

    return num;
}

double purePursuit::angleWrap(double angle) {
    if (angle > M_PI){
        return angle - M_PI * 2;
    }else if (angle < -M_PI){
        return angle + M_PI * 2;
    }
    return angle;
}