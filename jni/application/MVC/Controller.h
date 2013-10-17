#pragma once

#include <zenilib.h>

class Controller {
private:
	
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
