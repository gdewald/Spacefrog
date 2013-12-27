#pragma once

#include <zenilib.h>
#include "../MVC/Controller.h"
#include "../MVC/Player_view.h"

class Play_state : public Zeni::Gamestate_II {
	Controller* controller;
	Player_view* view;
	Zeni::Chronometer<Zeni::Time> m_chrono;
	float m_time_passed;

	Play_state(const Play_state &);
	Play_state operator=(const Play_state &);
public:
	Play_state();

	//All button events(keyboard/joystick) and joystick-axis events here
	void on_event(const Zeni::Zeni_Input_ID& id, const float& confidence, const int& action);
	//Only for events involving axis-type controls with keyboard
	void on_event(const SDL_Event& event);
	void on_push();
	void on_pop();
	void on_cover();
	void on_uncover();
	void perform_logic();
	void step(float m_timestep);
	void render();
};
