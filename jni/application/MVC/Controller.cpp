#include "Controller.h"
#include "Game_model.h"
#include "../Utility.h"
#include <cmath>

using namespace std;
using namespace Zeni;

Controller::Controller() : rs(false), ls(false), b_hold(false), b_time(0.0f), b_release(false), jump(false) {
	camera = Game_model::get_model().get_camera();
	frog = Game_model::get_model().get_frog();
}

void Controller::apply_actions(float timestep) {
	bool match_cam = false;
	bool match_cam_pos = false;
	bool slerp = false;

	camera->orientation.normalize();
	
	//Camera movement
	if (abs(joy_rx) > 0.1f) {
		camera->adjust_yaw(joy_rx * -0.5f * timestep);
	}
	if (abs(joy_ry) > 0.1f) {
		camera->adjust_pitch(joy_ry * 0.5f * timestep);
	}
	//Frog movement
	if (abs(joy_lx) > 0.1f) {
		auto rot = frog->turn(joy_lx * timestep * -2.0f);
		match_cam_pos = true;
		camera->orientation = Quaternion::Axis_Angle(rot.first, rot.second/*frog_up, joy_lx * timestep * -2.0f*/) * camera->orientation;
	}
	if (abs(joy_ly) > 0.1f) {
		if (frog->locked()) {
			auto rot = frog->move(joy_ly * timestep * 5.0f);
			slerp = true;
			camera->orientation = Quaternion::Axis_Angle(rot.first, -rot.second) * camera->orientation;
		}
		else  {
			auto rot = frog->move(joy_ly * timestep * 2.0f);
			camera->orientation = Quaternion::Axis_Angle(rot.first, rot.second) * camera->orientation;
		}
		match_cam_pos = true;
	}
	if (b_hold) {
		if (b_time == 0.0f) {
			frog->jump(MAX_B_TIME);
		}
		else frog->thrust(timestep * 100.0f);

		b_time += timestep;
		match_cam_pos = true;
		slerp = true;
		//if (b_time > MAX_B_TIME)
		//	b_time = MAX_B_TIME;
	}
	if (b_release) {
		b_time = 0.0f;
		b_release = false;
	}
	if (ls) {
		frog->rotate(0.5f * timestep);
		camera->orientation = frog->get_orientation();
		match_cam = true;
	}
	if (rs) {
		frog->rotate(-0.5f * timestep);
		camera->orientation = frog->get_orientation();
		match_cam = true;
	}
	if (joy_rt > 0.05) {
		frog->thrust(joy_rt * timestep * 100.0f);
		if (!frog->locked())
			slerp = true;
		match_cam_pos = true;
	}
	if (match_cam) {
		frog->reset_camera(camera);
	}
	if (match_cam_pos) {
		frog->reset_camera_pos(camera);
	}
	if (slerp) {
		camera->orientation = quaternion_slerp(camera->orientation, frog->get_orientation(),  timestep);
	}
}

void Controller::leftx(float confidence) {
	joy_lx = confidence;
}

void Controller::lefty(float confidence) {
	joy_ly = confidence;
}

void Controller::rightx(float confidence) {
	joy_rx = confidence;
}

void Controller::righty(float confidence) {
	joy_ry = confidence;
}

void Controller::b_state(float confidence) {
	if (confidence > 0) b_hold = true;
	else if (b_hold) {
		b_hold = false;
		b_release = true;
	}
}

//Left shoulder
void Controller::ls_state(float confidence) {
	ls = (confidence > 0);
}

//Right shoulder
void Controller::rs_state(float confidence) {
	rs = (confidence > 0);
}

void Controller::rt(float confidence) {
	joy_rt = confidence;
}
