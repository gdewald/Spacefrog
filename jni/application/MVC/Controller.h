#pragma once

#include <zenilib.h>
#include "../Game_objects/Frog.h"

class Controller {
private:
	Frog* frog;
	Zeni::Camera* camera;

	//Controller data
	bool jump;
	bool rs, ls;
	float joy_rx;
	float joy_ry;
	float joy_lx;
	float joy_ly;
	
public:
	Controller();

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
	void b_down();
	//Left shoulder
	void ls_down();
	void ls_up();
	//Right shoulder
	void rs_down();
	void rs_up();
};
