#include "Rendered_object.h"

using namespace std;
using namespace Zeni;

//Initializes the model_map
std::map<Zeni::String, Zeni::Model*> get_model_map();
//Keeps instances of each model
std::map<Zeni::String, Zeni::Model*> model_map = get_model_map();

map<String, Model*> get_model_map() {
	map<String, Model*> m;
	m["Frog"] = new Model("models/snowball.3ds");
	m["Planet"] = new Model("models/snowball.3ds");
	return m;
}

Rendered_object::Rendered_object(Zeni::String model_name) : m(model_map[model_name]) {

}
