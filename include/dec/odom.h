#pragma once
#include "../include/main.h"

extern pros::ADIEncoder encL, encR, encP; // Left, Right, and Perpindicular tracking wheels

class Odom {

<<<<<<< Updated upstream
    int currentLeft, currentRight, currentPerpindicular, prevLeft, prevRight, prevPerpindicular;
    double deltaLeft, deltaRight, deltaPerpindicular;
    double headingDeg, deltaHeadingDeg, headingRad, xPos, yPos;
    double leftToCenter, rightToCenter, perpindicularToCenter, trackingWheelDiameter;
=======
    static int currentLeft, currentRight, currentPerpindicular, prevLeft, prevRight, prevPerpindicular;
    static int deltaLeft, deltaRight, deltaPerpindicular;
    static double headingDeg, deltaHeadingDeg, headingRad, xPos, yPos, encLVelo, encRVelo, encPVelo;
    static double leftToCenter, rightToCenter, perpindicularToCenter, trackingWheelDiameter;
>>>>>>> Stashed changes

  public:

    int getLeft();
    int getRight();
    int getPerpindicular();
<<<<<<< Updated upstream

    double getDLeft();
    double getDRight();
    double getDPerpindicular();
=======
    int getDLeft();
    int getDRight();
    int getDPerpindicular();

>>>>>>> Stashed changes
    double getHeadingDeg();
    double getHeadingRad();
    double getX();
    double getY();

    Odom(double inchesLeftToCenter, double inchesRightToCenter, double inchesPerpindicularToCenter, double wheelDiameter);
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
    void tareEncoders();
    void resetPos();
    void updatePosition();

<<<<<<< Updated upstream
    double degreesToInches(int degrees);
=======
    double degreesToInches(int inches);
>>>>>>> Stashed changes

};
