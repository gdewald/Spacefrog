#pragma once

#include <zenilib.h>
#include "Rendered_object.h"
#include "Planet.h"

//A frog can be:
// on the surface of a planet - LOCK
// lifting off the surface - PREJUMP
// in the air - JUMP
enum MOVEMENT_STATE {LOCK, PREJUMP, JUMP};

class Frog : public Rendered_object{
private:
	Zeni::Point3f position;
	Zeni::Vector3f velocity;
	Zeni::Quaternion orientation;

	MOVEMENT_STATE move_state;
	Planet* locked_to;

	float fuel;

	const float MAX_TURN = 0.05f;
	const float MAX_MOVE = 5.0f;
	const float MAX_FUEL = 3.5f;

public:
	Frog(Zeni::Point3f position_, Zeni::Quaternion orientation_) : position(position_), orientation(orientation_),
		                                                           velocity(Zeni::Vector3f()), Rendered_object("Frog"),
																   move_state(JUMP), fuel(MAX_FUEL) { }

	Frog(Planet*, Zeni::Vector3f axis = Zeni::Vector3f(1.0f, 0.0f, 0.0f), float angle = 0.0f);

	//"Bumps" the colliding frog to surface
	void move_to_lock();
	//Makes the view "loop around"
	void adjust_perspective();

	void update(float timestep);

	void turn(float amount);
	void move(float amount);
	void thrust(float amount);
	void jump(float amount);

	Zeni::Quaternion get_orientation() { return orientation; }
	Zeni::Point3f get_position() { return position; }
	Zeni::Collision::Sphere get_col_sphere() { return Zeni::Collision::Sphere(position, 10.0f); }
	float get_fuel_percent() { return fuel / MAX_FUEL; }

	void adjust_pitch(float amount);
	void adjust_yaw(float amount);
	void rotate(float amount);

	void reset_camera(Zeni::Camera* c);

	void render();
};
