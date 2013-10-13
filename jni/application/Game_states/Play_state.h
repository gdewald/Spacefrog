#pragma once

#include <zenilib.h>

class Play_state : public Zeni::Gamestate_II {
	Play_state(const Play_state &);
	Play_state operator=(const Play_state &);

public:
	Play_state() {
		set_pausable(true);
	}

private:
	void on_push() {
		Zeni::get_Window().set_mouse_state(Zeni::Window::MOUSE_HIDDEN);
	}

	void on_pop() {
		Zeni::get_Controllers().reset_vibration_all();
	}

	void on_cover() {
		Zeni::get_Controllers().reset_vibration_all();
	}

	void on_controller_button(const SDL_ControllerButtonEvent &event) {
		if (event.button == SDL_CONTROLLER_BUTTON_BACK && event.state == SDL_PRESSED)
			Zeni::get_Game().push_Popup_Menu_State();
	}
};
