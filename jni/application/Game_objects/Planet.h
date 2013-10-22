#pragma once

#include <zenilib.h>
#include "Rendered_object.h"

const float SPHERE_BASE_RAD = 5.0f;

class Planet : public Rendered_object {
private:
	Zeni::Point3f center;
	Zeni::Vector3f scale;
	Zeni::Collision::Sphere col_sphere;
	float g;
	float radius;

public:
	Planet(Zeni::Point3f center_, float rad_mult) : center(center_), radius(rad_mult * SPHERE_BASE_RAD),
		                                           col_sphere(center, radius), 
		                                           scale(1.0f, 1.0f, 1.0f), g(800.0), Rendered_object("Planet") { }

	Zeni::Vector3f get_force(Zeni::Point3f position);
	Zeni::Collision::Sphere get_col_sphere() { return col_sphere; }
	Zeni::Point3f get_position() { return center; }
	float get_radius() { return radius; }
	
	void render();
};
