#pragma once

#include <zenilib.h>
#include "Rendered_object.h"

//A frog can be:
// on the surface of a planet - LOCK
// lifting off the surface - PREJUMP
// in the air - JUMP
//enum MOVEMENT_STATE {LOCK, PREJUMP, JUMP};

class Frog : public Rendered_object{
private:
	Zeni::Point3f position;
	Zeni::Vector3f velocity;
	Zeni::Quaternion orientation;

public:
	Frog(Zeni::Point3f position_, Zeni::Quaternion orientation_) : position(position_), orientation(orientation_),
		                                                           velocity(Zeni::Vector3f()), Rendered_object("Frog") { }

	void update(float timestep);

	void render();
};
