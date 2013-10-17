#pragma once

#include <zenilib.h>
#include <map>

class Rendered_object {
private:
	Zeni::Model* m;
	

public:
	Rendered_object(Zeni::String model_name);
	virtual void render(Zeni::Point3f ul, Zeni::Point3f lr) = 0;
};
