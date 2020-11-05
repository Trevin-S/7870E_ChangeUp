#pragma once
#include "main.h"

//Controller & Motor declarations
extern pros::Controller controller; // V5 controller
extern pros::Motor FL_mtr; // Front left drive
extern pros::Motor FR_mtr; // Front right drive
extern pros::Motor BL_mtr; // Back left drive
extern pros::Motor BR_mtr; // Back right drive
extern pros::ADIEncoder L_enc; // Left side tracking wheel
extern pros::ADIEncoder R_enc; // Right side tracking wheel
extern pros::ADIEncoder M_enc; // Middle (Perpindicular) tracking wheel

// Global position/angle/distance tracking variables
extern float x_pos;
extern float y_pos;
extern float degrees_facing;

// Global velocities of tracking wheels
extern float L_enc_velo;
extern float R_enc_velo;
extern float M_enc_velo;
