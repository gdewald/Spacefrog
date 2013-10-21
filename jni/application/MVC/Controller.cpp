#include "Controller.h"
#include "Game_model.h"
#include <cmath>

using namespace std;
using namespace Zeni;

Controller::Controller() {
	camera = Game_model::get_model().get_camera();
	frog = Game_model::get_model().get_frog();
}

void Controller::apply_actions(float timestep) {
	//Camera movement
	if (abs(joy_rx) > 0.2f)
		camera->adjust_yaw(joy_rx * -0.05);
	if (abs(joy_ry) > 0.2f)
		camera->adjust_pitch(joy_ry * 0.05);
	//Frog movement
	if (abs(joy_lx) > 0.2f) {
		//camera->adjust_yaw(joy_lx * timestep * -0.05);
		frog->turn(timestep*joy_lx);
		camera->orientation = frog->get_orientation();
	}
	if (abs(joy_ly) > 0.2f) {
		//camera->position += camera->get_forward().normalized() * timestep * -10 * joy_ly;
		frog->move(timestep * joy_ly);
		camera->position = frog->get_position();
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

void Controller::b() {
	jump = true;
}
