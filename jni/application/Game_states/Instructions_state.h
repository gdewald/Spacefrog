#pragma once
#include <zenilib.h>
//#include "Play_State.h"

class Instructions_state : public Zeni::Widget_Gamestate {
	Instructions_state(const Instructions_state &);
	Instructions_state operator=(const Instructions_state &);
	class Goals_button : public Zeni::Text_Button {
	private:

	public:
		Goals_button() : Zeni::Text_Button(Zeni::Point2f(1920.0/4.0-200.0, 20.0f), Zeni::Point2f(1920.0/4.0+200.0, 100.0f), "system_36_800x600", "Goals") { }

		void on_hover() {
			set_image("goals");
		}
	} g;

	class Controls_button : public Zeni::Text_Button {
	private:

	public:
		Controls_button() : Zeni::Text_Button(Zeni::Point2f(1920.0 / 2.0 + 1920/4 - 200.0, 20.0f), Zeni::Point2f(1920.0 / 2.0 + 1920/4 + 200.0, 100.0f), "system_36_800x600", "Controls") { }

		void on_hover() {
			set_image("controls");
		}
	} c;

	class Menu_button : public Zeni::Text_Button {
	private:

	public:
		Menu_button() : Zeni::Text_Button(Zeni::Point2f(350.0f, 480.0f), Zeni::Point2f(450.0f, 520.0f), "system_36_800x600", "Exit") { }
		void on_accept() {
			//for (int i = level_num; i < num_levels; i++) {
			Zeni::get_Game().pop_state();
			//}
		}
	} m;

	//Controls_button c;
	//Terrains_button t;
	//Powerups_button p;
	//Goals_button g;

public:
	Instructions_state()
		: Zeni::Widget_Gamestate(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(1920.0f, 1080.0f))), c(), g(), m() {
			m_widgets.lend_Widget(c);
			m_widgets.lend_Widget(g);
			render_image("skybox", Zeni::Point2f(), Zeni::Point2f(Zeni::get_Window().get_size()));

	}
	static void set_image(Zeni::String image_name_) { image_name = image_name_; }
private:
	static Zeni::String image_name;

	void on_key(const SDL_KeyboardEvent &event);
	
	void render();
};