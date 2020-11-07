#pragma once
#include "../include/main.h"

extern pros::ADIEncoder encL, encR, encP; // Left, Right, and Perpindicular tracking wheels

class Odom {

    int currentLeft, currentRight, currentPerpindicular, prevLeft, prevRight, prevPerpindicular;
    double deltaLeft, deltaRight, deltaPerpindicular;
    double headingDeg, deltaHeadingDeg, headingRad, xPos, yPos;
    double leftToCenter, rightToCenter, perpindicularToCenter, trackingWheelDiameter;

  public:

    int getLeft();
    int getRight();
    int getPerpindicular();

    double getDLeft();
    double getDRight();
    double getDPerpindicular();
    double getHeadingDeg();
    double getHeadingRad();
    double getX();
    double getY();

    Odom(double inchesLeftToCenter, double inchesRightToCenter, double inchesPerpindicularToCenter, double wheelDiameter);

    void tareEncoders();
    void resetPos();
    void updatePosition();

    double degreesToInches(int degrees);

};
