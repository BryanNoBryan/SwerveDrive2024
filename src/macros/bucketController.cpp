#include "macros/bucketController.h"

BucketController::BucketController() : pid(kP, kI, kD) {
    zeroEncoder();
    currentPos = 0;
    targetPos = 0;
}

double BucketController::getPosition() {
    return bucket.get_position();
}

void BucketController::zeroEncoder() {
    bucket.set_zero_position(0);
}

/**
 * Go to a set height, 0 is lowest, + is up
 */
void BucketController::goToPosition(double pos) {
    targetPos = pos;
}

// updates PID and power of each motor, call it in driveControl
void BucketController::update() {
    double bucketPower = pid.update(targetPos - bucket.get_position());

    bucket.move(bucketPower);
}

double BucketPos::getPos() const {
    switch (index) {
        case BUCKET_IN: return 0;
        case BUCKET_OUT: return BucketController::maximumPos;
        default: return 0;
    }
}