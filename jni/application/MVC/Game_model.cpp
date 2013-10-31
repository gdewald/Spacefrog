#include "Game_model.h"
#include "Controller.h"
#include "../Points.h"
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace Zeni;

Game_model* Game_model::instance = nullptr;

Game_model::Game_model() : controller(nullptr) {
	//Point3f init_pos = Point3f(100.0f, 100.0f, 100.0f);
	//Quaternion init_quaternion = Quaternion(0.0f, 0.0f, 1.0f);
	////Create a camera instance
	//Vector3f forward = init_quaternion * Vector3f(1.0f, 0.0f, 0.0f);
	//camera = new Camera(init_pos - (forward.normalized() * 30), init_quaternion);

	//Checkpoint time
	time_limit = 25;
	timer = 30.0f;

	planets.push_back(new Planet(Point3f(300.0f, 150.0f, 150.0f), 25.0f, 80, "Planet_orange"));
	planets.push_back(new Planet(Point3f(-300.0f, -150.0f, -150.0f), 20.0f, 60));
	planets.push_back(new Planet(Point3f(300.0f, 300.0f, 800.0f), 20.0f));

	//Create a food instance
	food = new Food(*planets.begin());
	//Create a frog instance
	frog = new Frog(planets[1]);
	//Set up camera instance
	camera = new Camera(frog->get_position(), frog->get_orientation(), 10.0f, 2000.0f);
}

Controller* Game_model::get_controller() {
	if (!controller) controller = new Controller();
	return controller;
}

vector<Planet*> Game_model::get_closest_planets(Point3f pos) {
	return planets;
}

void make_random_axis_angle(Vector3f& axis, float& angle) {
	srand(time(NULL));
	float theta = 6.28f * ((rand() % 100) / 100.0f);
	float omega = 6.28f * ((rand() % 100) / 100.0f);
	axis.set_spherical(theta, omega);
	angle = 6.28f * ((rand() % 100) / 100.0f);
}

void Game_model::update(float timestep) {
	//frog->reset_camera(camera);
	//frog->reset_camera_pos(camera);
	//frog->rotate(5.0 * timestep);
	//frog->render();
	frog->update(timestep);
	food->update(timestep);

	//Reduce timer
	timer -= timestep / 3;

	if (frog->get_col_sphere().intersects(food->get_col_sphere())) {
		//Update points
		Points::get_Points().hit();
		// Add the time limit if food picked up
		timer += time_limit;
		if (time_limit > 5)
			time_limit -= 5;

		Vector3f axis;
		float angle;
		make_random_axis_angle(axis, angle);
		int i = rand() % planets.size();
		food->set_planet(planets[i], axis, angle);

		//Food sound
	}

	//Stop game if out of time
	if (timer <= 0.0f) {
		get_Game().pop_state();
	}
}
