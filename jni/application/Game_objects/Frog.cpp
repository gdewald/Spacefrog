#include "Frog.h"
#include "../MVC/Game_model.h"

using namespace std;
using namespace Zeni;

void Frog::move_to_lock() {
	Vector3f center_to_point = position - locked_to->get_position();

	float bump_dist = locked_to->get_radius() - center_to_point.magnitude();
	position += bump_dist * center_to_point.normalized();

	Vector3f up = center_to_point.normalized();
	Vector3f forward = (orientation.space - center_to_point).normalized();
	orientation = Quaternion::Forward_Up(forward, up);
}

void Frog::update(float timestep) {
	switch (move_state) {
	case LOCK:

		break;
	case PREJUMP:
		break;
	case JUMP:	
		//auto p = Game_model::get_model().get_closest_planets(position);
		//Vector3f force = Vector3f();
		//Point3f pos = position;
		//for_each(p.begin(), p.end(), [&force, &pos](Planet* p){ force += p->get_force(pos); });

		//for (auto it = p.begin(); it != p.end(); it++) {
		//	if ((*it)->get_col_sphere.intersects(Collision::Sphere(pos, 1.0f))) {
		//		move_state = LOCK;
		//		locked_to = *it;
		//		move_to_lock();
		//		return;
		//	}
		//}

		//velocity += force * timestep;

		//position += velocity * timestep;
		break;
	}
}

void Frog::render() {
	//Model m = Model("models/")
	Rendered_object::render(position, Vector3f(10, 10, 10), Quaternion());
}

void Frog::turn(float amount) {
	if (move_state == LOCK) {
		orientation = Quaternion::Axis_Angle(orientation.get_rotation().first, orientation.get_rotation().second + amount*0.05);
	}
}

void Frog::move(float amount) {
	if (move_state == LOCK) {
		position -= orientation.get_rotation().first.normalized() * amount * 10.0f;
	}
}
