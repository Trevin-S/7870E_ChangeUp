#include "../include/dec/odom.h"
#include <math.h>

// Tracking wheel encoders
pros::ADIEncoder encL ('C','D', false),
                 encR ('A','B', true),
                 encP ('E','F', true);

Odom::Odom(double inchesLeftToCenter, double inchesRightToCenter, double inchesPerpindicularToCenter, double wheelDiameter){
    leftToCenter = inchesLeftToCenter;
    rightToCenter = inchesRightToCenter;
    perpindicularToCenter = inchesPerpindicularToCenter;
    trackingWheelDiameter = wheelDiameter;
}

int Odom::getLeft(){
  return currentLeft;
}

int Odom::getRight(){
  return currentRight;
}

int Odom::getPerpindicular(){
  return currentPerpindicular;
}

int Odom::getDLeft(){
  return deltaLeft;
}

int Odom::getDRight(){
  return deltaRight;
}

int Odom::getDPerpindicular(){
  return deltaPerpindicular;
}

double Odom::getHeadingDeg(){
  return headingDeg;
}

double Odom::getHeadingRad(){
  return headingRad;
}

double Odom::getX(){
  return xPos;
}

double Odom::getY(){
  return yPos;
}

void Odom::tareEncoders(){
  encL.reset();
  encR.reset();
  encP.reset();
  deltaLeft = deltaRight = deltaPerpindicular = currentLeft = currentRight = prevLeft = prevRight = prevPerpindicular = 0;
}

double Odom::degreesToInches(int degrees){
  double inches = (degrees / 360) * (trackingWheelDiameter * M_PI);
  return inches;
}

void Odom::updatePosition(){

    currentLeft = encL.get_value();
    currentRight = encR.get_value();
    currentPerpindicular = encP.get_value();

    deltaLeft = degreesToInches(currentLeft - prevLeft);
    deltaRight = degreesToInches(currentRight - prevRight);
    deltaPerpindicular = degreesToInches(currentPerpindicular - prevPerpindicular);

    deltaHeadingDeg = (deltaRight - deltaLeft) / ((leftToCenter + rightToCenter) * M_PI);
    headingDeg += deltaHeadingDeg;
		headingRad = (headingDeg * M_PI) / 180;

    deltaPerpindicular -= (deltaHeadingDeg / 360) * (perpindicularToCenter * M_PI);

	  xPos -= (sin(headingRad) * (deltaLeft + deltaRight)) + (cos(headingRad) * deltaPerpindicular);
	  yPos += (cos(headingRad) * (deltaLeft + deltaRight)) - (sin(headingRad) * deltaPerpindicular);

}
