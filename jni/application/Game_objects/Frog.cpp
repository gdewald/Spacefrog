#include "Frog.h"
#include "../MVC/Game_model.h"

using namespace std;
using namespace Zeni;

void Frog::move_to_lock() {
	Vector3f center_to_point = position - locked_to->get_position();

	float bump_dist = locked_to->get_radius() - center_to_point.magnitude();
	position += bump_dist * center_to_point.normalized();

	//Vector3f up = center_to_point.normalized();
	//Vector3f forward = (orientation.space - center_to_point).normalized();
	//orientation = Quaternion::Forward_Up(forward, up);
}

void Frog::update(float timestep) {
	switch (move_state) {
	case LOCK:

		break;
	case PREJUMP:
		break;
	case JUMP:	
		auto p = Game_model::get_model().get_closest_planets(position);
		Vector3f force = Vector3f();
		Point3f pos = position;
		for_each(p.begin(), p.end(), [&force, &pos](Planet* p){ force += p->get_force(pos); });

		for (auto it = p.begin(); it != p.end(); it++) {
			if ((*it)->get_col_sphere.intersects(Collision::Sphere(pos, 1.0f))) {
				move_state = LOCK;
				locked_to = *it;
				move_to_lock();
				return;
			}
		}

		//velocity += force * timestep;

		//position += velocity * timestep;
		break;
	}
}

void Frog::render() {
	//Model m = Model("models/")
	Rendered_object::render(position, Vector3f(.5, .5, .5), orientation);
}

void Frog::turn(float amount) {
	if (move_state == LOCK) {
		//auto axis = orientation.get_rotation().first;
		//auto angle = orientation.get_rotation().second;
		//Vector3f up = orientation * Vector3f(0.0f, -1.0f, 0.0f);

		//orientation *= Quaternion::Axis_Angle(, amount)
	}
	else if (move_state == JUMP) {

	}
}

void Frog::move(float amount) {
	if (move_state == LOCK) {
		//position -= orientation.get_rotation().first.normalized() * amount * 10.0f;
	}
	else if (move_state == JUMP) {

	}
}

void Frog::adjust_pitch(float amount) {
	Vector3f left = orientation * Vector3f(0.0f, 1.0f, 0.0f);
	orientation = Quaternion::Axis_Angle(left, amount) * orientation;
}

void Frog::adjust_yaw(float amount) {
	Vector3f up = orientation * Vector3f(0.0f, 0.0f, 1.0f);
	orientation = Quaternion::Axis_Angle(up, amount) * orientation;
}

void Frog::rotate(float amount) {
	Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
	orientation = Quaternion::Axis_Angle(forward, amount) * orientation;
}
