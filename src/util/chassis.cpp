#include "../include/dec/chassis.h"
#include "../include/dec/odom.h"

pros::Motor mtrBL(10, pros::E_MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS),
						mtrBR(1, pros::E_MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS),
						mtrFR(3, pros::E_MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS),
						mtrFL(8, pros::E_MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);


static Odom odom(4.1, 4.1, 1, 2.765);

// Multithread the positional tracking code with the autonomous code for real time position updates
void positionUpdate(void*){

	std::uint32_t now = pros::millis();
  while(1){

    odom.updatePosition();
    pros::lcd::print(0, "X Position: %f", odom.getX());
    pros::lcd::print(1,"Y Position: %f", odom.getY());
    pros::lcd::print(2, "Theta: %f", odom.getHeadingDeg());
		pros::lcd::print(3, "M Enc Value: %d", odom.getPerpindicular());
    pros::Task::delay_until(&now, 5);

  }
}
