#pragma once

#include <zenilib.h>
#include <list>
#include "..\Game_objects\Planet.h"
#include "..\Game_objects\Rendered_object.h"
#include "..\Game_objects\Frog.h"

class Game_model {
private:
	std::list<Planet*> planets;
	Frog* frog;
	Zeni::Camera* camera;

	//Timer and limit for checkpoints
	int time_limit;
	float timer;

	static Game_model* instance;
	Game_model();
public:
	//Initialize new model
	static void init_model() {
		if (instance) delete instance;
		instance = new Game_model();
	}

	//Singleton
	static Game_model& get_model() {
		if (!instance) instance = new Game_model();
		return *instance;
	}
	
	//Getters
	Zeni::Camera* get_camera() { return camera; }
	float get_timer() { return timer; }
	int get_time_limit() { return time_limit; }

	//Returns everything that is rendered
	std::list<Rendered_object*> get_rendered() {
		std::list<Rendered_object*> renderables;
		renderables.push_back(frog);
		for(auto it = planets.begin(); it != planets.end(); it++) {
			renderables.push_back(*it);
		}
		return renderables;
	}

	std::list<Planet*> get_closest_planets(Zeni::Point3f pos);
	Frog* get_frog() { return frog; }

	//Updates the game model
	void update(float timestep);
};
