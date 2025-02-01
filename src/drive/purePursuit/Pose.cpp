#include "drive/purePursuit/Pose.h"

Pose::Pose(double x, double y, double theta) :
x(x),
y(y),
theta(theta) { //THETA DEFINED IN DEGREES

};

double Pose::getX() {return x;}
double Pose::getY() {return y;}
double Pose::getTheta() {return theta;}

double Pose::distanceFrom(Pose pose) {
    double diff_x = pose.getX() - x;
    double diff_y = pose.getY() - y;
    return pow(pow(diff_x,2)+pow(diff_y,2), 0.5);
}

Pose Pose::vectorDiff(Pose pose) {
    double diff_x = x - pose.getX();
    double diff_y = y - pose.getY();
    double diff_theta = theta - pose.getTheta(); //THETA DEFINED IN DEGREES
    return Pose(diff_x, diff_y, diff_theta); //THETA DEFINED IN DEGREES
}

double Pose::length() {
    return pow(pow(x,2)+pow(y,2), 0.5);
}

Pose Pose::current_pos() {
    rxtx_enable.set_value(HIGH);
    serial_read(nullptr);

    return Pose(-otos_data[0], -otos_data[1], -otos_data[2]);
}