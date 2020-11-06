#pragma once
#include "../include/main.h"

extern pros::ADIEncoder encL, encR, encP; // Left, Right, and Perpindicular tracking wheels

class Odom {

    static int currentLeft, currentRight, currentPerpindicular, prevLeft, prevRight, prevPerpindicular;
    static int deltaLeft, deltaRight, deltaPerpindicular;
    static double headingDeg, deltaHeadingDeg, headingRad, xPos, yPos, encLVelo, encRVelo, encPVelo;
    static double leftToCenter, rightToCenter, perpindicularToCenter, trackingWheelDiameter;

  public:

    int getLeft();
    int getRight();
    int getPerpindicular();
    int getDLeft();
    int getDRight();
    int getDPerpindicular();

    double getHeadingDeg();
    double getHeadingRad();
    double getX();
    double getY();

    Odom(double inchesLeftToCenter, double inchesRightToCenter, double inchesPerpindicularToCenter, double wheelDiameter);
    void tareEncoders();
    void resetPos();
    void updatePosition();

    double degreesToInches(int inches);

};
