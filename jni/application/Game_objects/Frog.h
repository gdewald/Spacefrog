#pragma once

#include <zenilib.h>
#include <utility>
#include "Rendered_object.h"
#include "Planet.h"

//A frog can be:
// on the surface of a planet - LOCK
// lifting off the surface - PREJUMP
// in the air - JUMP
enum MOVEMENT_STATE {LOCK, PRELOCK, PREJUMP, JUMP};

const float MAX_TURN = 0.05f;
const float MAX_MOVE = 5.0f;
const float MAX_FUEL = 3.5f;

class Frog : public Rendered_object{
private:
	Zeni::Point3f position;
	Zeni::Vector3f velocity;
	Zeni::Quaternion orientation;

	MOVEMENT_STATE move_state;
	Planet* locked_to;

	float fuel;

	//Animation

public:
	float keyframe_step;
	Frog(Zeni::Point3f position_, Zeni::Quaternion orientation_) : position(position_), orientation(orientation_),
		                                                           velocity(Zeni::Vector3f()), Rendered_object("Frog_jump"),
																   move_state(JUMP), fuel(MAX_FUEL), keyframe_step(1.0f) { }

	Frog(Planet*, Zeni::Vector3f axis = Zeni::Vector3f(1.0f, 0.0f, 0.0f), float angle = 0.0f);

	//"Bumps" the colliding frog to surface
	void move_to_lock();
	//Makes the view "loop around"
	std::pair<Zeni::Vector3f, float> adjust_perspective();

	void update(float timestep);

	std::pair<Zeni::Vector3f, float> turn(float amount);
	std::pair<Zeni::Vector3f, float> move(float amount);
	void thrust(float amount);
	void jump(float amount);

	Zeni::Quaternion get_orientation() { return orientation; }
	Zeni::Point3f get_position() { return position; }
	Zeni::Collision::Sphere get_col_sphere() { return Zeni::Collision::Sphere(position, 10.0f); }
	float get_fuel_percent() { return fuel / MAX_FUEL; }

	bool locked() { return (move_state == LOCK); }

	std::pair<Zeni::Vector3f, float> adjust_pitch(float amount);
	std::pair<Zeni::Vector3f, float> adjust_yaw(float amount);
	void rotate(float amount);

	void reset_camera(Zeni::Camera* c);
	void reset_camera_pos(Zeni::Camera* c);
	//Returns orientation meant for camera
	//Zeni::Quaternion get_adj_orientation();

	//Animation

	void render();
};
