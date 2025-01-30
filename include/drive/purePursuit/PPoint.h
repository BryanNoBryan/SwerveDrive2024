#ifndef _PPOINT
#define _PPOINT

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

class PPoint {
    public:
        double x, y, theta;
        bool strafe = true;
        double radius = 10;
        double maxSpeed = 0.9, turnSpeed = 0.4;
        bool fieldCentric = true;

        PPoint(double inputX, double inputY, double inputTheta) {x = inputX; y = inputY; theta = inputTheta;};
        PPoint(double inputX, double inputY, double inputTheta, bool inputStrafe) {x = inputX; y = inputY; theta = inputTheta; strafe = inputStrafe;};
        double getX() {return x;};
        double getY() {return y;};
        double getTheta() {return theta;};
};

#endif