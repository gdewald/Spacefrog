#pragma once

#include <zenilib.h>
#include <list>
#include "..\Game_objects\Planet.h"
#include "..\Game_objects\Frog.h"
#include "..\Game_objects\Rendered_object.h"

class Game_model {
private:
	std::list<Planet*> planets;
	//Frog* frog;

	static Game_model* instance;
	Game_model() {

	}
public:
	static Game_model& get_Model() {
		if (!instance) instance = new Game_model();
		return *instance;
	}

	std::list<Rendered_object*> get_rendered() {
		std::list<Rendered_object*> renderables;
		for(auto it = planets.begin(); it != planets.end(); it++) {
			renderables.push_back(*it);
		}
		return renderables;
	}
};
