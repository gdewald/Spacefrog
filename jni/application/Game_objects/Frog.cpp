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

void Frog::adjust_perspective() {
	Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
	Vector3f plane_normal = (position - locked_to->get_position()).normalized();
	Vector3f proj = forward - (forward*plane_normal)*plane_normal;
	proj = proj.normalized();
	orientation = Quaternion::Forward_Up(proj, plane_normal);
}

void Frog::update(float timestep) {
	switch (move_state) {
	case LOCK:
		velocity = Vector3f();

		break;
	case PREJUMP:

		break;
	case JUMP:	
		auto p = Game_model::get_model().get_closest_planets(position);
		Vector3f force = Vector3f();
		Point3f pos = position;
		for_each(p.begin(), p.end(), [&force, &pos](Planet* p){ force += p->get_force(pos); });

		Colors& cr = get_Colors();
		Vertex3f_Color v1(pos - Point3f(10.0f, 0, 0), cr["yellow"]);
		Vertex3f_Color v2(pos + Point3f(10.0f, 0, 0), cr["green"]);
		Line_Segment<Vertex3f_Color> l(v1, v2);
		get_Video().render(l);

		velocity += force * timestep;

		position += velocity * timestep;
		reset_camera(Game_model::get_model().get_camera());

		for (auto it = p.begin(); it != p.end(); it++) {
			if ((*it)->get_col_sphere().intersects(get_col_sphere())) {
				locked_to = *it;
				move_to_lock();
				adjust_perspective();
				reset_camera(Game_model::get_model().get_camera());
				move_state = LOCK;
				return;
			}
		}
		break;
	}
}

void Frog::render() {
	Rendered_object::render(position, Vector3f(.3, .3, .3), orientation);
}

void Frog::turn(float amount) {
	adjust_yaw(amount);
	return;
	//if (move_state == LOCK) {
	//	auto axis = orientation.get_rotation().first;
	//	auto angle = orientation.get_rotation().second;
	//	Vector3f up = orientation * Vector3f(0.0f, -1.0f, 0.0f);

	//	orientation *= Quaternion::Axis_Angle(, amount)
	//}
	//else if (move_state == JUMP) {
	//}
}

void Frog::move(float amount) {
	if (move_state == LOCK) {
		Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
		position += forward * amount * -5.0f;
		move_to_lock();
		adjust_perspective();
	}
	else if (move_state == JUMP) {
		adjust_pitch(amount);
	}
}

void Frog::thrust(float amount)  {
	if (move_state == LOCK)
		return;

	Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
	velocity += forward.normalized() * amount;
}

void Frog::jump(float amount) {
	if (move_state != LOCK)
		return;

	Vector3f left = orientation * Vector3f(0.0f, 1.0f, 0.0f);
	orientation = Quaternion::Axis_Angle(left, -3.14f/8.0f) * orientation;
	Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
	velocity += forward.normalized() * amount * 500.0f;
	position += 50.0 * forward.normalized();
	move_state = JUMP;
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
	if (move_state == JUMP) {
		Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
		orientation = Quaternion::Axis_Angle(forward, amount) * orientation;
	}
}

void Frog::reset_camera(Zeni::Camera* c) {
	c->orientation = orientation;
	Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
	Vector3f up = orientation * Vector3f(0.0f, 0.0f, 1.0f);
	c->position = position - (forward.normalized() * 30.0f) + (up.normalized() * 20.0f);
}
