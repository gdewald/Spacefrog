#include "Food.h"
#include "Planet.h"

using namespace std;
using namespace Zeni;

Food::Food(Planet* p_, Vector3f axis, float angle) : Rendered_object("Dragonfly") {
	attached = true;
	p = p_;
	position = p->get_position() + axis.normalized() * (p->get_radius() + 5.0f);
	orientation = Quaternion::Axis_Angle(axis, angle);
}

void Food::render() {
	Rendered_object::render(position, Vector3f(.3, .3, .3), orientation);
}
