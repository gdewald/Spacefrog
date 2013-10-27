#pragma once

#include <zenilib.h>
#include <map>

class Rendered_object {
private:
	Zeni::Model* model;

public:
	Rendered_object(Zeni::String model_name);
	//Model* get_model();
	virtual void render() = 0;
	virtual void render(Zeni::Point3f center, Zeni::Vector3f scale, Zeni::Quaternion rotation);

	virtual void advance_keyframe(float timestep, float rate = 1.0f);
};
