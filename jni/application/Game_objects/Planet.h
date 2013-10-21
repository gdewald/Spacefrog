#pragma once

#include <zenilib.h>
#include "Rendered_object.h"

class Planet : public Rendered_object {
private:
	Zeni::Point3f center;
	Zeni::Vector3f scale;
	Zeni::Collision::Sphere col_sphere;
	float g;
	float radius;

public:
	Planet(Zeni::Point3f center_, float radius_) : center(center_), col_sphere(center_, radius_), 
		                                           scale(2.0f, 2.0f, 2.0f), g(800.0), Rendered_object("Planet") { }

	Zeni::Vector3f get_force(Zeni::Point3f position);
	Zeni::Collision::Sphere get_col_sphere() { return col_sphere; }
	Zeni::Point3f get_position() { return center; }
	float get_radius() { return radius; }
	
	void render();
};
