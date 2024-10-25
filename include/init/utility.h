#ifndef _UTILITY
#define _UTILITY


#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

class Vector2d {
    public:
        double x;
        double y;

        Vector2d(double x, double y);

};

int signum(double x);

double angleWrap(double degrees);

#endif
