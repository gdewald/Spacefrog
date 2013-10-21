#include "Play_state.h"
#include "../MVC/Game_model.h"

using namespace Zeni;
using namespace std;

Play_state::Play_state() {
	controller = new Controller();
	view = new Player_view();
	Game_model::init_model();

	//Map the joystick buttons
	//Pause
	set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE), 1);
	//set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_START), 1);
	//Left joystick
	set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTX /* x-axis */), 2);
	set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTY /* y-axis */), 3);
	//Right joystick
	set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTX), 4);
	set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTY), 5);
	//B button
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_B), 6);

}

void Play_state::on_event(const Zeni::Zeni_Input_ID& id, const float& confidence, const int& action) {
	switch (action) {
	case 1: //Pause
		if (confidence == 1.0f) {
			Game &game = get_Game();
			game.push_state(new Popup_Menu_State);
		}
		break;
	case 2: //Frog turn
		controller->leftx(confidence);
		break;
	case 3: //Frog move
		controller->lefty(confidence);
		break;
	case 4: //View turn x
		controller->rightx(confidence);
		break;
	case 5: //View turn y
		controller->righty(confidence);
		break;
	case 6: //Frog jump
		controller->b();
		break;
	}

}

void Play_state::on_push() {
	//Grab the mouse and controller
	get_Window().set_mouse_state(Window::MOUSE_GRABBED_AND_HIDDEN);
	get_Game().controller_mouse.enabled = false;

	//Start the chronometer
	m_chrono.start();
}

void Play_state::on_pop() {
	//Ungrab the mouse and controller
	get_Window().set_mouse_state(Window::MOUSE_NORMAL);
	get_Game().controller_mouse.enabled = true;

	//Stop the chronometer
	m_chrono.stop();
}

void Play_state::on_cover() {
	//Pause the chronometer
	m_chrono.stop();
}

void Play_state::on_uncover() {
	//Resume the chronometer
	m_chrono.start();
}

void Play_state::perform_logic() {
	SDL_Delay(5);

	const float time_passed = m_chrono.seconds();
	float time_step = time_passed - m_time_passed;
	m_time_passed = time_passed;

	const float max_timestep = 1.0f / 20.0f;
	const int max_timesteps = 10;
	if (time_step / max_timestep > max_timesteps)
		time_step = max_timesteps * max_timestep;

	while (time_step > max_timestep) {
		step(max_timestep);
		time_step -= max_timestep;
	}
	step(max_timestep);
}

void Play_state::step(float m_timestep) {
	Game_model::get_model().update(m_timestep);
	controller->apply_actions(m_timestep);
	//view->update();
}

void Play_state::render() {
	Colors& cr = get_Colors();
	view->render();

	//Vertex3f_Color v1(Point3f(10.0f, 10.0f, -20.0f), cr["yellow"]);
	//Vertex3f_Color v2(Point3f(100.0f, 10.0f, -20.0f), cr["yellow"]);
	//Vertex3f_Color v3(Point3f(100.0f, 100.0f, -20.0f), cr["blue"]);
	//Vertex3f_Color v4(Point3f(10.0f, 100.0f, -20.0f), cr["blue"]);
	//Quadrilateral<Vertex3f_Color> q(v1, v2, v3, v4);

	//get_Video().render(q);
}
