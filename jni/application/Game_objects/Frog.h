#pragma once

#include <zenilib.h>
#include "Rendered_object.h"

class Frog : public Rendered_object{
private:
	Zeni::Point3f position;
	Zeni::Vector3f direction;
	
public:
	void render();
};
