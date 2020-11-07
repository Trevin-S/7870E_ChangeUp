#pragma once
#include "../include/main.h"

extern pros::Controller controller;
extern pros::Motor mtrFL; // Front left drive
extern pros::Motor mtrFR; // Front right drive
extern pros::Motor mtrBL; // Back left drive
extern pros::Motor mtrBR; // Back right drive

extern void reset();
extern void positionUpdate(void *);
