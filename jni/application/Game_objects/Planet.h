#pragma once

#include <zenilib.h>
#include <cmath>
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
	Planet(Zeni::Point3f center_, float rad_mult, Zeni::String p_name="Planet_orange") : center(center_), radius(rad_mult * SPHERE_BASE_RAD),
		                                            scale(rad_mult, rad_mult, rad_mult), g(100.0), Rendered_object(p_name) {
		col_sphere = Zeni::Collision::Sphere(center, radius);
	}

	Zeni::Vector3f get_force(Zeni::Point3f position);
	Zeni::Collision::Sphere get_col_sphere() { return col_sphere; }
	Zeni::Point3f get_position() { return center; }
	float get_radius() { return radius; }
	
	void render();
};
