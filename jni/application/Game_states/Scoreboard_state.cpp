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

void Scoreboard_state::render() {
	Widget_Gamestate::render();
	auto& p = Points::get_Points();
	p.render_scores();
}
