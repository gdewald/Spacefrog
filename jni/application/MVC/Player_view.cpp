#include "Player_view.h"
#include "Game_model.h"
#include "Controller.h"

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

	//Fuel data
	float bar_w = Game_model::get_model().get_frog()->get_fuel_percent() * ww/2;
	float bar_h = wh / 16;
	Vertex2f_Color v1(Point2f(ww / 2 - bar_w / 2, wh - wh / 16), cr["red"]);
	Vertex2f_Color v2(Point2f(ww / 2 + bar_w / 2, wh - wh / 16), cr["green"]);
	Vertex2f_Color v3(Point2f(ww / 2 + bar_w / 2, wh - wh / 16 + 30.0f), cr["green"]);
	Vertex2f_Color v4(Point2f(ww / 2 - bar_w / 2, wh -  wh / 16 + 30.0f), cr["red"]);
	Quadrilateral<Vertex2f_Color> fuel_bar(v1, v2, v3, v4);

	//Jump data
	bar_w = Game_model::get_model().get_controller()->get_b_percent() * ww/2;
	Vertex2f_Color v1_j(Point2f(ww / 2 - bar_w / 2, wh / 16), cr["blue"]);
	Vertex2f_Color v2_j(Point2f(ww / 2 + bar_w / 2, wh / 16), cr["white"]);
	Vertex2f_Color v3_j(Point2f(ww / 2 + bar_w / 2, wh / 16 + 30.0f), cr["white"]);
	Vertex2f_Color v4_j(Point2f(ww / 2 - bar_w / 2, wh / 16 + 30.0f), cr["blue"]);
	Quadrilateral<Vertex2f_Color> jump_bar(v1_j, v2_j, v3_j, v4_j);

	//Set up and render HUD
	get_Video().set_2d();
	get_Video().set_zwrite(true);
	//Render timer
	get_Fonts()["system_36_800x600"].render_text(itoa(time) + "/" + itoa(time_limit), timer_pos, cr["yellow"]);
	get_Video().render(fuel_bar);
	get_Video().render(jump_bar);
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
