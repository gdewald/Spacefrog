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

	axis.normalize();
	//Set orientation based on axis and angle
	Quaternion orientation_in = Quaternion::Axis_Angle(axis, angle);
	Vector3f left = orientation_in * Vector3f(0.0f, 1.0f, 0.0f);
	orientation_in = Quaternion::Axis_Angle(left, 3.14 / 2) * orientation_in;
	set_orientation(orientation_in);

	//Place the food above surface
	Vector3f up = orientation_in * Vector3f(0.0f, 0.0f, 1.0f);
	Point3f pos = p->get_position() + up.normalized() * (p->get_radius() + 5.0f);
	set_position(pos);

	food_ss.stop();
	food_ss.set_position(position);
	food_ss.set_looping(true);
	food_ss.set_buffer(get_Sounds()["dragonfly_flutter"]);
	food_ss.set_gain(1.0f);
	food_ss.set_max_distance(200.0f);
	food_ss.set_rolloff(1.0f);
	food_ss.play();
}

void Food::render() {
	Rendered_object::render(position, Vector3f(.2, .2, .2), orientation);
}

void Food::update(float timestep) {
	Rendered_object::advance_keyframe(timestep, 20.0f);
	//Flutter sound
}
