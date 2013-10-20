#include "Frog.h"
#include "../MVC/Game_model.h"

using namespace std;
using namespace Zeni;

void Frog::update(float timestep) {
	auto p = Game_model::get_model().get_closest_planets(Point3f());
	Vector3f force = Vector3f();
	Point3f pos = position;
	for_each(p.begin(), p.end(), [&force, &pos](Planet* p){ force += p->get_force(pos); });

	velocity += force * timestep;

	position += velocity * timestep;
}

void Frog::render() {
	
}
