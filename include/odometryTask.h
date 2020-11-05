#pragma once
#include "declarations.h"

// Zero out tracking wheel encoder values
void reset_encoders(){

  L_enc.reset();
  R_enc.reset();
  M_enc.reset();

}

void encoder_velo(){

  float L_enc_distance;
  float R_enc_distance;
  static float L_enc_initial;
  static float R_enc_initial;
  float L_enc_new;
  float R_enc_new;

  L_enc_initial = (L_enc.get_value() / 41.67); //Left side chassis distance covered in inches
  R_enc_initial = (R_enc.get_value() / 41.67); // Right side chassis distance covered in inches

  pros::delay(10);
  L_enc_new = (L_enc.get_value() / 41.67);
  R_enc_new = (R_enc.get_value() / 41.67); // Find difference in movement over a 10ms sample rate

  // Calculate encoder velocity in rpm -- convert the change in inches to some number of rotations
  // (8.63 in per rotation) and multiply by 6000 for conversion of milliseconds to minutes
  L_enc_velo = (((L_enc_new - L_enc_initial) / 8.63) * 6000);
  R_enc_velo = (((R_enc_new - R_enc_initial) / 8.63) * 6000);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Track and update the robot's position and orientation on the field
// This function uses unpowered tracking wheels connected to rotary encoders
// The usage of these wheels, along with some triginometry and other math
// allows us to track and update the robot's position and angle
// on the field in real time.
// When the robot knows where it is at, a new element of autonomous can be introduced.
//
// Self correction.
//
// When the robot knows where it is at, and where it wants to be, it can map its own path,
// recalculating this path in real time in order to ensure it reaches the target point/angle.
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void record_robot_state(){

	const float tuned_distance_constant = 1.0416;
	const float tracking_wheel_base = 8.175; // As this number goes up, the change in degrees facing is lower per encoder change
	const float degrees_to_inches = 41.59;
	const double turn_proportion = (360 / (tracking_wheel_base * 3.14159)); // Degrees per inch of turn
  static float R_enc_last_state;
  static float L_enc_last_state;
	static float M_enc_last_state;
	static float L_enc_distance_change;
	static float R_enc_distance_change;
	static float M_enc_distance_change;
	static float previous_x;
	static float previous_y;
	static bool reset = false;
	int turn_manager;
  float L_enc_distance;
	float R_enc_distance;
	float M_enc_distance;
	float average_parallel_change; // The change in position parallel to the direction the robot is facing
	float perpindicular_change;
	float radians_facing;

  encoder_velo();

    L_enc_distance = (L_enc.get_value() / degrees_to_inches); //Left side chassis distance covered in inches
    R_enc_distance = (R_enc.get_value() / degrees_to_inches); // Right side chassis distance covered in inches
		M_enc_distance = (M_enc.get_value() / degrees_to_inches);

    // Calculate the angle of the robot based on encoder distance and tuned proportionals
    degrees_facing = ((R_enc_distance - L_enc_distance) * turn_proportion / 2);  // proportion of encoder to turn, being combined with last turn state to find current turn angle
		radians_facing = degrees_facing / (180/3.14159);

    // Take the change in distance of each side of the robot
    L_enc_distance_change = L_enc_distance - L_enc_last_state;
    R_enc_distance_change = R_enc_distance - R_enc_last_state;
		M_enc_distance_change = M_enc_distance - M_enc_last_state;

    // Average the change of the two tracking wheels multiplied by a constant for accurate distances
    average_parallel_change = ((L_enc_distance_change + R_enc_distance_change) / 2) * tuned_distance_constant;
		perpindicular_change = (M_enc_distance - M_enc_last_state);

		// Look for unrealistically high changes that indicates noise in the encoders
		// that sometimes happens at the start of the program.
    if (fabs(average_parallel_change) > 5){

    	average_parallel_change = 0;

    }
		if (fabs(perpindicular_change) > 5){

			perpindicular_change = 0;

		}

    // If degrees facing has passed over 360 (1 full rotation)
    if (degrees_facing > 360){

    	turn_manager = trunc((degrees_facing / 360));
    	degrees_facing -= turn_manager * 360;

    // If degrees facing is a negative value
    } else if (degrees_facing < 0){

      turn_manager = (trunc((fabs(degrees_facing) / 360)) + 1);
      degrees_facing += turn_manager * 360;

  	}

    // If the turn value is within 0.1 degrees of 0, reset encoders and turn value to 0
    if (fabs(360 - degrees_facing) < 0.05 || fabs(degrees_facing) < 0.05){

      // Zero out the encoders
      reset_encoders();

      // Set the reset boolean to true to prevent false change
      reset = true;

      // Reset turn value
      degrees_facing = 360;

      //Set previous state to 0 to prevent false "value change"
      L_enc_last_state = 0;
      R_enc_last_state = 0;
			M_enc_last_state = 0;
      L_enc_distance_change = 0;
      R_enc_distance_change = 0;
			M_enc_distance_change = 0;

    } else {

			reset = false;
	    // Convert degree value to radians, then multiply by hypotenuse length (average parallel change)
	    // Hypotenuse length is the distance traveled by the robot, and the output is a change in X or Y
	    x_pos -= (sin(radians_facing) * average_parallel_change) + (cos(radians_facing) * perpindicular_change);
	    y_pos += (cos(radians_facing) * average_parallel_change) + (sin(radians_facing) * perpindicular_change);

    }

  	if (reset == false){

	    // Update the last state of distance
	    L_enc_last_state = L_enc_distance;
	    R_enc_last_state = R_enc_distance;
      M_enc_last_state = M_enc_distance;
	    previous_x = x_pos;
	    previous_y = y_pos;

	  } else {

	    L_enc_last_state = 0;
	    R_enc_last_state = 0;
      M_enc_last_state = 0;
	    reset = false;

	  }
// Finally, the end of the robot positional tracking function!!
}

// Multitasking: Multithread the positional tracking code with the autonomous code for real time position updates
void record_robot_state_task(void*){

	std::uint32_t now = pros::millis();

  while(1){

    record_robot_state();
    pros::lcd::print(0, "X Position: %f", x_pos);
    pros::lcd::print(1,"Y Position: %f", y_pos);
    pros::lcd::print(2, "Theta: %f", degrees_facing);
		pros::lcd::print(3, "M Enc Value: %d", M_enc.get_value());
    pros::Task::delay_until(&now, 5);

  }
}
