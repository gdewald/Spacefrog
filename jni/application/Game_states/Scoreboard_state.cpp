#include "Scoreboard_state.h"
#include "../Points.h"
#include "Play_state.h"

using namespace Zeni;

void save_score() {
	Points::get_Points().save_score();
}

void Retry_button::on_accept() {
	save_score();
	get_Game().pop_state();
	get_Game().push_state(new Play_state());
	//Level_Select_State::push_current_level();
}

void Scoreboard_state::on_key(const SDL_KeyboardEvent &event) {
	if (event.state == SDL_PRESSED && event.keysym.sym == SDLK_ESCAPE) {
		save_score();
		get_Game().pop_state();
	}
	else Widget_Gamestate::on_key(event);
}

void Scoreboard_state::render() {
	render_image("skybox", Point2f(), Point2f(get_Window().get_size()));

	Widget_Gamestate::render();
	auto& p = Points::get_Points();
	p.render_scores();
}
