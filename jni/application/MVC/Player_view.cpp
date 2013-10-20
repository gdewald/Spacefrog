#include "Player_view.h"
#include "Game_model.h"

using namespace std;
using namespace Zeni;

void Player_view::render() {
	auto renderables = Game_model::get_model().get_rendered();
	for_each(renderables.begin(), renderables.end(), [](Rendered_object* r){ r->render(); });
}
