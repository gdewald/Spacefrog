#include "Planet.h"

using namespace Zeni;
using namespace std;

void Planet::render() {
	//Game_model m("models/snowball.3ds");
	//m.set_translate(center);
	//m.set_scale(scale);
	
	//m.render();
	Rendered_object::render(center, scale, Quaternion());
}

Vector3f Planet::get_force(Point3f position) {
	Vector3f f(position - center);
	if (f.magnitude() > 3 * radius)
		return Vector3f();

	f.normalize();
	f *= g;
	return f;
}
