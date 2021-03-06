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

double Odom::getDLeft(){
  return deltaLeft;
}

double Odom::getDRight(){
  return deltaRight;
}

double Odom::getDPerpindicular(){
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
  deltaLeft = deltaRight = deltaPerpindicular = deltaHeadingDeg = 0.0;
  currentLeft = currentRight = currentPerpindicular = prevLeft = prevRight = prevPerpindicular = 0;
}

void Odom::resetPos(){
  xPos = yPos = headingDeg = headingRad = 0;
}

double Odom::degreesToInches(int degrees){
  return (((double) degrees) / 360) * (trackingWheelDiameter * M_PI);
}

void Odom::updatePosition(){

    currentLeft = encL.get_value();
    currentRight = encR.get_value();
    currentPerpindicular = encP.get_value();

    deltaLeft = degreesToInches(currentLeft - prevLeft);
    deltaRight = degreesToInches(currentRight - prevRight);
    deltaPerpindicular = degreesToInches(currentPerpindicular - prevPerpindicular);

    if (deltaLeft > 1 || deltaRight > 1 || deltaPerpindicular > 1){
      deltaLeft = deltaRight = deltaPerpindicular = 0;
    }

    headingDeg += deltaHeadingDeg = ((deltaRight - deltaLeft) * 360) / ((leftToCenter + rightToCenter) * M_PI) / 2;
		headingRad = (headingDeg * M_PI) / 180;

    if (headingDeg < 0){
      headingDeg += (trunc(fabs(headingDeg) / 360) + 1) * 360;
    } else if (headingDeg > 360){
      headingDeg -= trunc(headingDeg / 360) * 360;
    }

    deltaPerpindicular -= (deltaHeadingDeg / 360) * (perpindicularToCenter * M_PI);

	  xPos -= (sin(headingRad) * (deltaLeft + deltaRight) / 2) + (cos(headingRad) * deltaPerpindicular);
	  yPos += (cos(headingRad) * (deltaLeft + deltaRight) / 2) - (sin(headingRad) * deltaPerpindicular);

    prevLeft = currentLeft;
    prevRight = currentRight;
    prevPerpindicular = currentPerpindicular;

}
