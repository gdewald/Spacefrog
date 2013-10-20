#include "Game_model.h"

using namespace std;
using namespace Zeni;

Game_model* Game_model::instance = nullptr;

Game_model::Game_model() {
	frog = new Frog(Point3f());
	planets.push_back(new Planet(Point3f()));
}

list<Planet*> Game_model::get_closest_planets(Point3f pos) {
	return planets;
}

void Game_model::update(float timestep) {
	
}
