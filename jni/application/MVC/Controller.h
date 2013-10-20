#pragma once

#include <zenilib.h>
#include "../Game_objects/Frog.h"

class Controller {
private:
	Frog* frog;
	Zeni::Camera* camera;
	
public:
	//Turn frog
	void leftx(float confidence);
	//Move frog
	void lefty(float confidence);
	//Rotate view
	void rightx(float confidence);
	//Move view up/down
	void righty(float confidence);
	//Jump frog
	void b();
};
