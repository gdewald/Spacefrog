#include "Player_view.h"
#include "Game_model.h"

using namespace std;
using namespace Zeni;

Player_view::Player_view() : to_rend() {
	//Get the camera from the model
	camera = Game_model::get_model().get_camera();
}

void Player_view::render_hud() {
	Colors& cr = get_Colors();
	float ww = get_Window().get_width();
	float wh = get_Window().get_height();

	//Time limit data
	int time_limit = Game_model::get_model().get_time_limit();
	int time = Game_model::get_model().get_timer();
	Point2f timer_pos = Point2f(ww / 8, wh / 8);

	//Set up and render HUD
	get_Video().set_2d();
	get_Video().set_zwrite(true);
	get_Fonts()["system_36_800x600"].render_text(itoa(time) + "/" + itoa(time_limit), timer_pos, cr["yellow"]);
}

void Player_view::render() {

	//Game_model::get_model().get_frog_position();
	get_Video().set_3d(*camera);
	get_Video().set_zwrite(true);
	//Game_model::get_model().get_frog()->render();
	auto renderables = Game_model::get_model().get_rendered();
	for_each(renderables.begin(), renderables.end(), [](Rendered_object* r){ r->render(); });

	//Render 2d timer
	render_hud();
}
