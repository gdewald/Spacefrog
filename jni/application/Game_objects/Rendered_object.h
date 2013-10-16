#pragma once

#include <zenilib.h>

class Rendered_object {
public:
	virtual void render(Zeni::Point3f ul, Zeni::Point3f lr) = 0;
};
