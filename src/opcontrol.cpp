#include "../include/main.h"
#include "declarations.h"

void split_arcade(){

	// Get the left Y axis and right Y axis joystick values
	int left_raw = controller.get_analog(ANALOG_LEFT_Y);
	int right_raw = controller.get_analog(ANALOG_RIGHT_X);

	// Motor Power are nonlinear. Setting the motor power directly proportional to the joystick is inneficient.
	// The motors output too low of power at the beginning of the joystick throw and are too quick to accelerate with movement.
	// Finite control is not possible this way, and the driver will struggle to make subtle slow movements
	// By inputting the joystick powers into a quadratic equation whose curve is much closer to that of the torque output of motors,
	// and has a much lower slope at the beginning of the curve allows for lower end motor control while preserving the maximum power values.
	//
	// By remapping the joysticks this way, precise driving and smoother movements are much easier to acheive,
	// and the robot feels easier and more natural to drive.
	int left = (-0.0085 * pow(left_raw,2)) * (left_raw / std::abs(left_raw));
	int right =  (0.0085 * pow(right_raw,2)) * (right_raw / std::abs(right_raw));


	// Combine the outputs of the quadratic equations for both joysticks,
	// and multiply by a proportional to get the max/min quadratic outputs to equal motor max/min
	FL_mtr = ((-left + right) * -.95);
	BL_mtr = ((left - right) * -.95);
	FR_mtr = ((left + right) * -.95);
	BR_mtr = ((-left - right) * -.95);

}

void opcontrol() {
	FL_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	BL_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	FR_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	BR_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	while (true) {

	  split_arcade(); // Joystick drive control
		pros::delay(20);

	}
}
