#include "../include/main.h"
#include "declarations.h"
#include "odometryTask.h"

// Array for motor ports
// FR, FL, BR, BL
const int motorPorts[4] = {10,1,3,8};

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor BL_mtr(motorPorts[3]);
pros::Motor BR_mtr(motorPorts[2]);
pros::Motor FR_mtr(motorPorts[1], pros::E_MOTOR_GEARSET_18, true);
pros::Motor FL_mtr(motorPorts[0], pros::E_MOTOR_GEARSET_18, true);

// Tracking wheel encoders
pros::ADIEncoder L_enc ('C','D', false);
pros::ADIEncoder R_enc ('A','B', true);
pros::ADIEncoder M_enc ('E','F', true);

// Global position/angle/distance tracking variables
float x_pos = 0;
float y_pos = 0;
float degrees_facing = 0;

// Global velocities of tracking wheels
float L_enc_velo = 0;
float R_enc_velo = 0;

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Team 7870E");
	pros::task_t RecordPosition = pros::c::task_create(record_robot_state_task, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "RecordPosition");
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
