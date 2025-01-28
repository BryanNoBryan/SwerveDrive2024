#ifndef _PUREPURSUIT
#define _PUREPURSUIT

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "drive/purePursuit/PPoint.h"
#include "drive/SwerveDrive.h"

using namespace std;

class purePursuit{
    public:
        void runPath(vector<PPoint> path);
        void runPath(vector<PPoint> path, double endTheta);

    private:
        void run(vector<PPoint> path);
        vector<double> robotToLine(PPoint p1, PPoint p2, vector<double> pos);

        SwerveDrive sDrive;

        double clamp(double num, double min, double max);
        double limitValue(double num, double minNeg, double maxNeg, double minPos, double maxPos);
        double angleWrap(double angle);

        int pointer;
        int endCount;
        int const divider = 6;
        double const minSpeed = 0.15;
        vector<double> lastPosition;

        vector<double> setVels {0, 0, 0};

        double curXVel = 0;
        double curYVel = 0;
        double curThetaVel = 0;

        lemlib::PID xPID = lemlib::PID(1, 0, 0);
        lemlib::PID yPID = lemlib::PID(1, 0, 0);
        lemlib::PID thetaPID = lemlib::PID(1, 0, 0);

        double endTheta;
        // Tolerance of 2 inches in x and y and 3 degress in theta
        vector<double> tolerance {2, 2, M_PI/60};

        double timeout = -1; // In milliseconds (-1 means no timeout)
        bool stopAtWall = false; // Should the robot stop when it hits a wall (velocity is 0)
};

#endif