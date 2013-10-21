#include "Controller.h"
#include "Game_model.h"
#include <cmath>

using namespace std;
using namespace Zeni;

Controller::Controller() : rs(false), ls(false), jump(false) {
	camera = Game_model::get_model().get_camera();
	frog = Game_model::get_model().get_frog();
}

void Controller::apply_actions(float timestep) {
	//Camera movement
	if (abs(joy_rx) > 0.2f)
		camera->adjust_yaw(joy_rx * -0.05f * timestep);
	if (abs(joy_ry) > 0.2f)
		camera->adjust_pitch(joy_ry * 0.05f * timestep);
	//Frog movement
	if (abs(joy_lx) > 0.2f) {
		//camera->adjust_yaw(joy_lx * timestep * -0.05);
		//float theta = timestep*joy_lx;
		//frog->turn(timestep*joy_lx);
		//camera->turn_left_xy(timestep*joy_lx);
		//camera->orientation = frog->get_orientation();
		frog->adjust_yaw(joy_lx * timestep * 5.0f);
	}
	if (abs(joy_ly) > 0.2f) {
		//camera->position += camera->get_forward().normalized() * timestep * -10 * joy_ly;
		//frog->move(timestep * joy_ly);
		//camera->position = frog->get_position() - camera->orientation.get_rotation().first.normalized() * 100.0f;
		frog->adjust_pitch(joy_ly * timestep * 5.0f);
	}
	if (ls) {
		frog->rotate(0.5f * timestep);
	}
	if (rs) {
		frog->rotate(-0.5f * timestep);
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

void Controller::b_down() {
	//jump = true;
}

//Left shoulder
void Controller::ls_down() {
	ls = true;
}

void Controller::ls_up() {
	ls = false;
}

//Right shoulder
void Controller::rs_down() {
	rs = true;
}

void Controller::rs_up() {
	rs = false;
}
