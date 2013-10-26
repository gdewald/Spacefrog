#include "Controller.h"
#include "Game_model.h"
#include <cmath>

using namespace std;
using namespace Zeni;

Controller::Controller() : rs(false), ls(false), b_hold(false), b_release(false), jump(false) {
	camera = Game_model::get_model().get_camera();
	frog = Game_model::get_model().get_frog();
}

void Controller::apply_actions(float timestep) {
	bool match_cam = false;
	//Camera movement
	if (abs(joy_rx) > 0.1f) {
		camera->adjust_yaw(joy_rx * -0.5f * timestep);
	}
	if (abs(joy_ry) > 0.1f) {
		camera->adjust_pitch(joy_ry * 0.5f * timestep);
	}
	//Frog movement
	if (abs(joy_lx) > 0.1f) {
		//camera->adjust_yaw(joy_lx * timestep * -0.05);
		//float theta = timestep*joy_lx;
		//frog->turn(timestep*joy_lx);
		//camera->turn_left_xy(timestep*joy_lx);
		frog->turn(joy_lx * timestep * -5.0f);
		match_cam = true;
	}
	if (abs(joy_ly) > 0.1f) {
		//camera->position += camera->get_forward().normalized() * timestep * -10 * joy_ly;
		//frog->move(timestep * joy_ly);
		//camera->position = frog->get_position() - camera->orientation.get_rotation().first.normalized() * 100.0f;
		frog->move(joy_ly * timestep * 5.0f);
		match_cam = true;
	}
	const float MAX_TIME = 3.0f;
	if (b_hold) {
		b_time += timestep;
		if (b_time > MAX_TIME)
			b_time = MAX_TIME;
	}
	if (b_release) {
		b_time = 0.0f;
		b_release = false;
		frog->jump(b_time/MAX_TIME);
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
		match_cam = true;
	}
	if (match_cam) {
		frog->reset_camera(camera);
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
