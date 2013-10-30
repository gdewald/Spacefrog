#include "Planet.h"
#include <cmath>

using namespace Zeni;
using namespace std;

void Planet::update(float timestep) {
	if (!orbit) return;
}

void Planet::render() {
	Rendered_object::render(center, scale, Quaternion());

	Colors& cr = get_Colors();
	Vertex3f_Color v1(center - Point3f(radius, 0, 0), cr["yellow"]);
	Vertex3f_Color v2(center + Point3f(radius, 0, 0), cr["green"]);
	Line_Segment<Vertex3f_Color> l(v1, v2);
	get_Video().render(l);
}

Vector3f Planet::get_force(Point3f position) {
	Vector3f f(center - position);
	if (f.magnitude() > 5 * radius)
		return Vector3f();

	f.normalize();
	float rad2 = f.magnitude2();
	f = f.normalized()*(g/rad2);
	return f;
}
