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
	Zeni::Vector3f direction;
	float velocity;

	Zeni::Vector3f force;

public:
	Frog(Zeni::Point3f position_) : position(position_), direction(Zeni::Vector3f()), Rendered_object("Frog") { }

	void update(float timestep);

	void render();
};
