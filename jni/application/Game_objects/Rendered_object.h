#pragma once

#include <zenilib.h>
#include <map>

class Rendered_object {
private:
	Zeni::Model* m;
	Zeni::Point3f center;
	Zeni::Vector3f size;
	Zeni::Quaternion rotation;

public:
	Rendered_object(Zeni::String model_name);
	//Model* get_Model();
	virtual void render();
};
