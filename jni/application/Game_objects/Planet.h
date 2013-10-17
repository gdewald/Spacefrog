#pragma once

#include <zenilib.h>
#include "Rendered_object.h"

class Planet : public Rendered_object {
private:
	Zeni::Point3f center;
	Zeni::Vector3f scale;
	float g;

public:
	Planet(Zeni::Point3f center_) : center(center_), scale(1.0f, 1.0f, 1.0f), g(800.0), Rendered_object("Planet") { }
	
	void render(Zeni::Point3f ul, Zeni::Point3f lr);
};
