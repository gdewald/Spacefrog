#include "Player_view.h"
#include "Game_model.h"

using namespace std;
using namespace Zeni;

Player_view::Player_view() : to_rend() {
	//Get the camera from the model
	camera = Game_model::get_model().get_camera();
}

void Player_view::render() {
	//auto renderables = Game_model::get_model().get_rendered();
	//for_each(renderables.begin(), renderables.end(), [](Rendered_object* r){ r->render(); });


	//Game_model::get_model().get_frog_position();
	get_Video().set_3d(*camera);
	get_Video().set_zwrite(true);
	Game_model::get_model().get_frog()->render();
}
