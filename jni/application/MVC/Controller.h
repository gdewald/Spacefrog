#pragma once

#include <zenilib.h>
#include "../Game_objects/Frog.h"

const float MAX_B_TIME = 3.0f;

class Controller {
private:
	Frog* frog;
	Zeni::Camera* camera;

	//Controller data
	bool jump;
	bool rs, ls;
	bool b_hold;
	//The amount of time b was held
	float b_time;
	bool b_release;
	float joy_rx;
	float joy_ry;
	float joy_lx;
	float joy_ly;
	float joy_rt;

	
public:
	Controller();

	float get_b_percent() { return b_time / MAX_B_TIME; }

	void apply_actions(float timestep);

	//Turn frog
	void leftx(float confidence);
	//Move frog
	void lefty(float confidence);
	//Rotate view
	void rightx(float confidence);
	//Move view up/down
	void righty(float confidence);
	//Jump frog
	void b_state(float confidence);
	//Left shoulder
	void ls_state(float confidence);
	//Right shoulder
	void rs_state(float confidence);
	//Right trigger
	void rt(float confidence);
};
