#pragma once

#include <zenilib.h>
#include "Rendered_object.h"

class Planet;

class Food : public Rendered_object {
private:
	Zeni::Point3f position;
	Zeni::Quaternion orientation;

	Zeni::Collision::Sphere col_sphere;

	bool attached;
	Planet* p;

	//Sound
	Zeni::Sound_Source food_ss;

	//Light
	Zeni::Light food_l;

public:
	~Food() { stop_sound(); }

	//Attached to position
	Food(Zeni::Point3f position_, Zeni::Quaternion orientation_) : position(position_), orientation(orientation_), Rendered_object("Dragonfly") { }
	Food(Planet*, Zeni::Vector3f axis = Zeni::Vector3f(1.0f, 0.0f, 0.0f), float angle = 0.0f);

	void set_position(Zeni::Point3f position_) { position = position_; col_sphere = Zeni::Collision::Sphere(position, 5.0f); }
	void set_orientation(Zeni::Quaternion orientation_) { orientation = orientation_; }
	void set_planet(Planet*, Zeni::Vector3f axis = Zeni::Vector3f(1.0f, 0.0f, 0.0f), float angle = 0.0f);

	Zeni::Point3f get_position() { return position; };
	Zeni::Quaternion get_orientation() { return orientation; }
	Zeni::Collision::Sphere get_col_sphere() { return col_sphere; }

	void update(float timestep);

	void render();

	//Stop sound
	void stop_sound() { food_ss.stop(); }
};