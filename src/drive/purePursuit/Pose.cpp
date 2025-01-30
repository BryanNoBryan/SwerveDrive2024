#include "drive/purePursuit/Pose.h"

Pose::Pose(double x, double y, double theta) :
x(x),
y(y),
theta(theta) {

};

double Pose::getX() {return x;}
double Pose::getY() {return y;}
double Pose::getTheta() {return theta;}
double Pose::distanceFrom(Pose pose) {
    double diff_x = pose.getX() - x;
    double diff_y = pose.getY() - y;
    return pow(pow(diff_x,2)+pow(diff_x,2) , 0.5);
}