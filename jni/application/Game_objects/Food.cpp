#include "Food.h"
#include "Planet.h"

using namespace std;
using namespace Zeni;

Food::Food(Planet* p_, Vector3f axis, float angle) : Rendered_object("Dragonfly") {
	set_planet(p_, axis, angle);
}

void Food::set_planet(Planet* p_, Vector3f axis, float angle) {
	attached = true;
	p = p_;

	//Place the food above surface
	Point3f pos = p->get_position() + axis.normalized() * (p->get_radius() + 5.0f);
	set_position(pos);
	//Point it away from planet at and rotate it by the angle
	Quaternion orientation_in = Quaternion::Axis_Angle(axis, angle);
	//Face the food parallel to the plane
	Vector3f left = orientation_in * Vector3f(0.0f, 1.0f, 0.0f);
	orientation_in = Quaternion::Axis_Angle(left, 3.14 / 2) * orientation_in;
	set_orientation(orientation_in);
}

void Food::render() {
	Rendered_object::render(position, Vector3f(.2, .2, .2), orientation);
}
