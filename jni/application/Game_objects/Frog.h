#pragma once

#include <zenilib.h>
#include "Rendered_object.h"

class Frog : public Rendered_object{
private:
	Zeni::Point3f position;
	Zeni::Vector3f direction;
	float velocity;

public:
	Frog(Zeni::Point3f position_) : position(position_), direction(Zeni::Vector3f()), Rendered_object("Frog") { }

	void render();
};
