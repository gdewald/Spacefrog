#include "Play_state.h"
#include "../MVC/Game_model.h"

using namespace Zeni;
using namespace std;

Play_state::Play_state() {
	//controller = new Controller();
	//view = new Player_view();

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

}

void Play_state::step(float m_timestep) {
	//Game_model::get_Model().update(m_timestep);
}

void Play_state::render() {
	
}
