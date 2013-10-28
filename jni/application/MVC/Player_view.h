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

	//2D Hud rendering
	void render_hud();
	//Renders everything the player sees
	void render();
};
