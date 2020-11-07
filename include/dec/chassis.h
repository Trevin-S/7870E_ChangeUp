#pragma once
#include "../include/main.h"

extern pros::Controller controller;
extern pros::Motor mtrFL; // Front left drive
extern pros::Motor mtrFR; // Front right drive
extern pros::Motor mtrBL; // Back left drive
extern pros::Motor mtrBR; // Back right drive

class Chassis {

  enum moveType : int;
  enum brakeType: int;

  public:

    Chassis();

    double getDriveTemp();
    double getLeftVelo();
    double getRightVelo();
    double getAverageVelo();

    void setDrivePower(int leftPower, int rightPower, enum moveType motorControl);
    void setBrakeType(enum brakeType motorBrake);
    
};
