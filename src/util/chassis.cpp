#include "../include/dec/chassis.h"
#include "../include/dec/odom.h"

pros::Motor mtrBL(10, pros::E_MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS),
						mtrBR(1, pros::E_MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS),
						mtrFR(3, pros::E_MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS),
						mtrFL(8, pros::E_MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);

enum moveType {
	VOLTAGE, VELOCITY
};

void setDrivePower(int leftPower, int rightPower, enum moveType motorControl){
	switch (motorControl){
		case VOLTAGE:
			mtrFR.move_voltage(rightPower);
			mtrFL.move_voltage(leftPower);
			mtrBR.move_voltage(rightPower);
			mtrBL.move_voltage(leftPower);
		case VELOCITY:
			mtrFR.move_velocity(rightPower);
			mtrFL.move_velocity(leftPower);
			mtrBR.move_velocity(rightPower);
			mtrBL.move_velocity(leftPower);
	}
}

enum brakeType {
	COAST, BRAKE, HOLD
};

void setBrakeType(enum brakeType motorBrake){
	switch (motorBrake){
		case COAST:
			mtrFR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			mtrFL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			mtrBR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			mtrBL.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		case BRAKE:
			mtrFR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			mtrFL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			mtrBR.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			mtrBL.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
		case HOLD:
			mtrFR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			mtrFL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			mtrBR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			mtrBL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	}
}
