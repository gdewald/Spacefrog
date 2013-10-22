#include "Rendered_object.h"

using namespace std;
using namespace Zeni;

//Initializes the model_map
std::map<Zeni::String, Zeni::Model*> get_model_map();
////Keeps instances of each model
std::map<Zeni::String, Zeni::Model*> model_map;// = get_model_map();

map<String, Model*> get_model_map() {
	map<String, Model*> m;
	
	m["Frog"] = new Model("models/frog.3ds");
	m["Planet"] = new Model("models/planet.3ds");

	return m;
}

Rendered_object::Rendered_object(Zeni::String model_name) {
	if (model_map.empty())
		model_map = get_model_map();
	model = model_map[model_name];
}

//void Rendered_object::render() {
//
//}

void Rendered_object::render(Point3f center, Vector3f scale, Quaternion rotation) {
	model->set_translate(center);
	model->set_scale(scale);
	model->set_rotate(rotation);

	model->render();
}
