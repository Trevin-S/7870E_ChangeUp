#include "../include/main.h"
#include "../include/dec/chassis.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Team 7870E");
	pros::task_t RecordPosition = pros::c::task_create(positionUpdate, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "RecordPosition");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
