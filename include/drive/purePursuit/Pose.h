#ifndef _POSE
#define _POSE

#include <cmath>

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS


class Pose {
    public:
        double x, y, theta;

        Pose(double x, double y, double theta);

        double getX();
        double getY();
        double getTheta();
        double distanceFrom(Pose pose);
        Pose vectorDiff(Pose pose);
};

#endif