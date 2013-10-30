#include "Frog.h"
#include "../MVC/Game_model.h"
#include "../Utility.h"

using namespace std;
using namespace Zeni;

Frog::Frog(Planet* p, Zeni::Vector3f axis, float angle) : Rendered_object("Frog_lock") {
	move_state = LOCK;
	locked_to = p;

	axis.normalize();
	//Set orientation based on axis and angle
	orientation = Quaternion::Axis_Angle(axis, angle);
	Vector3f left = orientation * Vector3f(0.0f, 1.0f, 0.0f);
	orientation = Quaternion::Axis_Angle(left, 3.14 / 2) * orientation;

	//Place the frog above surface
	Vector3f up = orientation * Vector3f(0.0f, 0.0f, 1.0f);
	position = p->get_position() + up.normalized() * (p->get_radius());

	//Set fuel
	fuel = MAX_FUEL;

	//Initial animation state
	keyframe_step = 1.0f;
}

void Frog::move_to_lock() {
	Vector3f center_to_point = position - locked_to->get_position();

	float bump_dist = locked_to->get_radius() - center_to_point.magnitude();
	position += bump_dist * center_to_point.normalized();

	//Vector3f up = center_to_point.normalized();
	//Vector3f forward = (orientation.space - center_to_point).normalized();
	//orientation = Quaternion::Forward_Up(forward, up);
}

pair<Vector3f, float> Frog::adjust_perspective() {
	Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
	Vector3f plane_normal = (position - locked_to->get_position()).normalized();
	Vector3f proj = forward - (forward*plane_normal)*plane_normal;
	proj = proj.normalized();
	Quaternion old_orientation = orientation;
	orientation = Quaternion::Forward_Up(proj, plane_normal);

	//Return axis-angle of the perspective adjustment
	return (old_orientation * inverse(orientation)).get_rotation();
}

void Frog::update(float timestep) {
	switch (move_state) {
	case PRELOCK:
		move_state = LOCK;
		//Set locked model
		Rendered_object::swap_model("Frog_lock");
		Rendered_object::reset_keyframe();
		keyframe_step = 1.0f;
	case LOCK:
		velocity = Vector3f();

		//Advance animation if needed
		if (keyframe_step < 1.0f) {
			Rendered_object::advance_keyframe(timestep, 100.0f);
			keyframe_step += timestep;
		}

		fuel += timestep;
		if (fuel > MAX_FUEL)
			fuel = MAX_FUEL;



		break;
	case PREJUMP:

		//Jump sound

		//position += velocity * timestep;
		//reset_camera(Game_model::get_model().get_camera());
		move_state = JUMP;
		//Set jumping model, start animation
		Rendered_object::swap_model("Frog_jump");
		Rendered_object::reset_keyframe();
		keyframe_step = 0.0f;
	case JUMP:
		//Regenerate fuel
		fuel += timestep * 0.1;
		if (fuel > MAX_FUEL)
			fuel = MAX_FUEL;

		//Advance animation if needed
		if (keyframe_step < 1.0f) {
			Rendered_object::advance_keyframe(timestep, 100.0f);
			keyframe_step += timestep;
		}

		auto p = Game_model::get_model().get_closest_planets(position);
		Vector3f force = Vector3f();
		Point3f pos = position;
		for_each(p.begin(), p.end(), [&force, &pos, &timestep](Planet* p){ force += p->get_force(pos); });

		Colors& cr = get_Colors();
		Vertex3f_Color v1(pos - Point3f(10.0f, 0, 0), cr["yellow"]);
		Vertex3f_Color v2(pos + Point3f(10.0f, 0, 0), cr["green"]);
		Line_Segment<Vertex3f_Color> l(v1, v2);
		get_Video().render(l);

		velocity += force * timestep;

		position += velocity * timestep;
		reset_camera_pos(Game_model::get_model().get_camera());

		for (auto it = p.begin(); it != p.end(); it++) {
			if ((*it)->get_col_sphere().intersects(get_col_sphere())) {
				locked_to = *it;
				move_to_lock();
				adjust_perspective();
				reset_camera_pos(Game_model::get_model().get_camera());

				//Landing sound

				move_state = PRELOCK;
				return;
			}
		}
		break;
	}
}

void Frog::render() {
	Rendered_object::render(position, Vector3f(.3, .3, .3), orientation);
}

pair<Vector3f, float> Frog::turn(float amount) {
	return adjust_yaw(amount);
	
	//if (move_state == LOCK) {
	//	auto axis = orientation.get_rotation().first;
	//	auto angle = orientation.get_rotation().second;
	//	Vector3f up = orientation * Vector3f(0.0f, -1.0f, 0.0f);

	//	orientation *= Quaternion::Axis_Angle(, amount)
	//}
	//else if (move_state == JUMP) {
	//}
}

pair<Vector3f, float> Frog::move(float amount) {
	if (move_state == LOCK || move_state == PRELOCK) {
		//Start/continue jumping animation
		if (keyframe_step >= 1.0f) {
			keyframe_step = 0.0f;
			//Ribbit sound
		}

		Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
		position += forward * amount * -10.0f;
		move_to_lock();
		return adjust_perspective();
	}
	else if (move_state == JUMP) {
		return adjust_pitch(amount);
	}
}

void Frog::thrust(float amount)  {
	if (move_state == LOCK)
		return;

	amount = amount * 0.01;

	//Check for any fuel
	if (fuel <= 0) {
		fuel = 0;
		return;
	}

	//Use correct amount of fuel
	if (amount > fuel) {
		amount = fuel;
		fuel = 0;
	}
	else fuel -= amount;

	Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
	velocity += forward.normalized() * amount * 100;
}

void Frog::jump(float amount) {
	if (move_state != LOCK)
		return;

	Vector3f left = orientation * Vector3f(0.0f, 1.0f, 0.0f);
	orientation = Quaternion::Axis_Angle(left, -3.14f/8.0f) * orientation;
	Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
	velocity += forward.normalized() * amount * 25.0f;
	position += 20.0 * forward.normalized();
	move_state = PREJUMP;
}

pair<Vector3f, float> Frog::adjust_pitch(float amount) {
	Vector3f left = orientation * Vector3f(0.0f, 1.0f, 0.0f);
	Quaternion rot = Quaternion::Axis_Angle(left, amount);
	orientation = rot * orientation;
	return rot.get_rotation();
}

pair<Vector3f, float> Frog::adjust_yaw(float amount) {
	Vector3f up = orientation * Vector3f(0.0f, 0.0f, 1.0f);
	Quaternion rot = Quaternion::Axis_Angle(up, amount);
	orientation = rot * orientation;
	return rot.get_rotation();
}

void Frog::rotate(float amount) {
	if (move_state == JUMP) {
		Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
		orientation = Quaternion::Axis_Angle(forward, amount) * orientation;
	}
}

void Frog::reset_camera(Zeni::Camera* c) {
	c->orientation = orientation.normalized();
	reset_camera_pos(c);
}

void Frog::reset_camera_pos(Zeni::Camera* c) {
	Vector3f forward = orientation * Vector3f(1.0f, 0.0f, 0.0f);
	Vector3f up = orientation * Vector3f(0.0f, 0.0f, 1.0f);
	c->position = position - (forward.normalized() * 30.0f) + (up.normalized() * 20.0f);
}
