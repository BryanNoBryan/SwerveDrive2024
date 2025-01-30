#include "drive/purePursuit/Pose.h"

Pose::Pose(double x, double y, double theta) :
x(x),
y(y),
theta(theta) {

};

double Pose::getX() {return x;}
double Pose::getY() {return y;}
double Pose::getTheta() {return theta;}