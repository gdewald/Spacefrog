#include "Game_model.h"

using namespace std;
using namespace Zeni;

Game_model* Game_model::instance = nullptr;

Game_model::Game_model() {
	Point3f init_pos = Point3f();
	Quaternion init_quaternion = Quaternion();
	//Create a frog instance
	frog = new Frog(init_pos, init_quaternion);
	//Create a camera instance
	camera = new Camera(init_pos, init_quaternion);
	planets.push_back(new Planet(Point3f()));

}

list<Planet*> Game_model::get_closest_planets(Point3f pos) {
	return planets;
}

void Game_model::update(float timestep) {
	
}
