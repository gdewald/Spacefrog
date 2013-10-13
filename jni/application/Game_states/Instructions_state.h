#pragma once

#include <zenilib.h>
#include <utility>

class Instructions_state : public Zeni::Widget_Gamestate {
	Instructions_state(const Instructions_state &);
	Instructions_state operator=(const Instructions_state &);

public:
	Instructions_state()
		: Zeni::Widget_Gamestate(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(800.0f, 600.0f)))
	{
	}

private:
	void on_key(const SDL_KeyboardEvent &event) {
		if (event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
			Zeni::get_Game().pop_state();
	}

	void render() {
		Widget_Gamestate::render();

		Zeni::Font &fr = Zeni::get_Fonts()["title"];

		fr.render_text(
#if defined(_WINDOWS)
			"ALT+F4"
#elif defined(_MACOSX)
			"Apple+Q"
#else
			"Ctrl+Q"
#endif
			" to Quit",
			Zeni::Point2f(400.0f, 300.0f - 0.5f * fr.get_text_height()),
			Zeni::get_Colors()["title_text"],
			Zeni::ZENI_CENTER);
	}
};
