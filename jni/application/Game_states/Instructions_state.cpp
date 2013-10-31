#include "Instructions_state.h"

using namespace Zeni;

Zeni::String Instructions_state::image_name = "goals";

void Instructions_state::on_key(const SDL_KeyboardEvent &event) {
	if (event.state == SDL_PRESSED && event.keysym.sym == SDLK_ESCAPE)
		get_Game().pop_state();
	else Widget_Gamestate::on_key(event);
}

void Instructions_state::render() {
	Widget_Gamestate::render();

	Zeni::Font &fr = get_Fonts()["title"];
	Zeni::Video& vr = get_Video();
	int w = get_Window().get_height();

	//fr.render_text("Controls",
	//	Point2f(400.0f, 300.0f - 0.5f * fr.get_text_height()),
	//	get_Colors()["title_text"],
	//	ZENI_CENTER);

	render_image(image_name, Point2f(0.0f, 120.0f), Point2f(1920.0f, 1080.0f));

}
