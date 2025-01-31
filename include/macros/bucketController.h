#ifndef _BUCKET_CONTROLLER
#define _BUCKET_CONTROLLER

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "init/devices.h"
#include "lemlib/pid.hpp"

using namespace std;

class BucketController
{
private:
    // PID Constants
    static constexpr double kP = 2;
    static constexpr double kI = 0;
    static constexpr double kD = 0;
    
    lemlib::PID pid;

public:
    double currentPos;
    double targetPos;

    static constexpr double maximumPos = 220;
    static constexpr double middlePos = 80;

    /**
     * @brief Get current position, 0 is in, + is out
     */
    double getPosition();

    /**
     * @brief Go to a set height, 0 is in, + is out
     */
	void goToPosition(double height);

    /**
     * @brief updates PID and power of each motor, call it in driveControl
     */
    void update();

    /**
     * @brief sets zero position of the lift encoder
     */
    void zeroEncoder();

    // constructor
    BucketController();

};

class BucketPos {
    int index;
public:
    static constexpr int length() {return 2;}
    BucketPos() : index(0) {}
    constexpr explicit BucketPos(int index) : index(index) {}
    constexpr operator int() const { return index; }

    double getPos() const;
};
constexpr BucketPos BUCKET_IN(0);
constexpr BucketPos BUCKET_OUT(1);
constexpr BucketPos BUCKET_MIDDLE(2);

#endif