#pragma once

#include <zenilib.h>
#include "../Game_objects/Rendered_object.h"

class Player_view {
private:
	//List of rendered objects
	std::list<Rendered_object*> to_rend;
	Zeni::Camera* camera;

public:
	Player_view();

	//Renders the rendered_objects that need to be rendered
	void render();
};
