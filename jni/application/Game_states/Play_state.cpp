#include "Play_state.h"
#include "../MVC/Game_model.h"

using namespace Zeni;
using namespace std;

Play_state::Play_state() {
	Game_model::init_model();
	controller = new Controller();
	view = new Player_view();

	//Map the joystick buttons
	//Pause
	set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE), 1);
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_START), 1);
	//Left joystick
	set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTX /* x-axis */), 2);
	set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTY /* y-axis */), 3);
	//Right joystick
	set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTX), 4);
	set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTY), 5);
	//B button
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_B), 6);
	//Left bumper
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_LEFTSHOULDER), 7);
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONUP, SDL_CONTROLLER_BUTTON_LEFTSHOULDER), 8);
	//Right bumper
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER), 9);
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONUP, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER), 10);
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
		controller->b_down();
		break;
	case 7:
		controller->ls_down();
		break;
	case 8:
		controller->ls_up();
		break;
	case 9:
		controller->rs_down();
		break;
	case 10:
		controller->rs_up();
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
	Camera* cam = Game_model::get_model().get_camera();
	Point3f temp = cam->position;
	cam->position = Point3f();

	get_Video().set_3d(*cam);
	get_Video().set_zwrite(false);

	Vertex3f_Color v1(Point3f(-50.0f, -50.0f, -50.0f), cr["white"]);
	Vertex3f_Color v2(Point3f(-50.0f, -50.0f, 50.0f), cr["black"]);
	Vertex3f_Color v3(Point3f(-50.0f, 50.0f, -50.0f), cr["white"]);
	Vertex3f_Color v4(Point3f(-50.0f, 50.0f, 50.0f), cr["black"]);
	Vertex3f_Color v5(Point3f(50.0f, -50.0f, -50.0f), cr["white"]);
	Vertex3f_Color v6(Point3f(50.0f, -50.0f, 50.0f), cr["black"]);
	Vertex3f_Color v7(Point3f(50.0f, 50.0f, -50.0f), cr["white"]);
	Vertex3f_Color v8(Point3f(50.0f, 50.0f, 50.0f), cr["black"]);

	Quadrilateral<Vertex3f_Color> q1(v1, v3, v4, v2);
	Quadrilateral<Vertex3f_Color> q2(v8, v7, v5, v6);
	Quadrilateral<Vertex3f_Color> q3(v2, v6, v5, v1);
	Quadrilateral<Vertex3f_Color> q4(v3, v7, v8, v4);
	Quadrilateral<Vertex3f_Color> q5(v1, v5, v7, v3);
	Quadrilateral<Vertex3f_Color> q6(v2, v6, v8, v4);

	get_Video().render(q1);
	get_Video().render(q2);
	get_Video().render(q3);
	get_Video().render(q4);
	get_Video().render(q5);
	get_Video().render(q6);

	cam->position = temp;
	view->render();
}
