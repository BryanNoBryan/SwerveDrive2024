#ifndef _PPOINT
#define _PPOINT

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

class PPoint {
    public:
        double x, y, theta;
        bool strafe = false;
        double radius = 10;
        double maxSpeed = 1, turnSpeed = 0.6;
        bool fieldCentric = false;

        PPoint(double x, double y, double theta) {x = PPoint::x; y = PPoint::y; PPoint::theta;};
        PPoint(double x, double y, double theta, bool strafe) {x = PPoint::x; y = PPoint::y; PPoint::theta; strafe = PPoint::strafe;};
};

#endif