#include "Play_state.h"
#include "../MVC/Game_model.h"
#include "Scoreboard_state.h"
#include "../Points.h"

using namespace Zeni;
using namespace std;

Play_state::Play_state() {
	Game_model::init_model();
	controller = Game_model::get_model().get_controller();//Game_model::get_model().get_controller();
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
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_X), 6);
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONUP, SDL_CONTROLLER_BUTTON_X), 7);
	//Left bumper
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_LEFTSHOULDER), 8);
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONUP, SDL_CONTROLLER_BUTTON_LEFTSHOULDER), 9);
	//Right bumper
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER), 10);
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONUP, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER), 11);
	//Right trigger
	set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERRIGHT), 12);
	//End game
	set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_BACK), 13);

	//Map keyboard keys
}

class Popup_pause_state_custom : public Popup_Pause_State {
public:
	class Continue_button : public Text_Button {
	public:
		Continue_button(Point2f ul, Point2f lr)
			: Text_Button(ul, lr,
			"system_36_800x600", "Continue")
		{
		}

		void on_accept() { get_Game().pop_state(); }
	};

	class Quit_button : public Text_Button {
	public:
		Quit_button(Point2f ul, Point2f lr)
			: Text_Button(ul, lr,
			"system_36_800x600", "Quit")
		{
		}

		void on_accept() { get_Game().pop_state(); get_Game().pop_state(); }
	};

	class Restart_button : public Text_Button {
	public:
		Restart_button(Point2f ul, Point2f lr)
			: Text_Button(ul, lr,
			"system_36_800x600", "Restart")
		{
		}

		void on_accept() { get_Game().pop_state(); get_Game().pop_state(); get_Game().pop_state(); get_Game().push_state(new Play_state()); }
	};

	Continue_button* c;
	Restart_button* r;
	Quit_button* q;

	Popup_pause_state_custom() : Popup_Pause_State() {
		float ww = get_Window().get_width();
		float wh = get_Window().get_height();
		float left = ww/2 - ww / 8;
		float right = ww/2 + ww / 8;
		float upper = wh / 2 - wh / 16;
		float lower = wh / 2 + wh / 16;

		c = new Continue_button(Point2f(left, upper), Point2f(right, lower));
		m_widgets.lend_Widget(*c);

		upper += wh / 6;
		lower += wh / 6;

		r = new Restart_button(Point2f(left, upper), Point2f(right, lower));
		m_widgets.lend_Widget(*r);

		upper += wh / 6;
		lower += wh / 6;

		q = new Quit_button(Point2f(left, upper), Point2f(right, lower));
		m_widgets.lend_Widget(*q);
	}

	void render() {
		m_widgets.render();
		Popup_Pause_State::render();
	}
};

void Play_state::on_event(const SDL_Event& event) {
	if (event.type == SDL_MOUSEMOTION) {

	}
	else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		float conf = 1.0f;
		switch (event.key.keysym.sym) {
		case SDLK_w:
			conf = -1.0f;
		case SDLK_s:
			if (event.type == SDL_KEYUP) conf = 0.0f;
			controller->lefty(conf);
			return;
		case SDLK_a:
			conf = -1.0f;
		case SDLK_d:
			if (event.type == SDL_KEYUP) conf = 0.0f;
			controller->leftx(conf);
			return;
		case SDLK_SPACE:
			controller->b_state(event.type == SDL_KEYDOWN);
			return;
		default:
			break;
		}
	}
	Gamestate_II::on_event(event);
}

void Play_state::on_event(const Zeni::Zeni_Input_ID& id, const float& confidence, const int& action) {
	switch (action) {
	case 1: //Pause
		if (confidence == 1.0f) {
			Game &game = get_Game();
			game.push_state(new Popup_pause_state_custom());
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
	case 7:
		controller->b_state(confidence);
		break;
	case 8:
	case 9:
		controller->ls_state(confidence);
		break;
	case 10:
	case 11:
		controller->rs_state(confidence);
		break;
	case 12:
		controller->rt(confidence);
	case 13:
		get_Game().pop_state();
	}

}

void Play_state::on_push() {
	//Grab the mouse and controller
	get_Window().set_mouse_state(Window::MOUSE_GRABBED_AND_HIDDEN);
	get_Game().controller_mouse.enabled = false;

	Points::get_Points().reset();

	//Start the chronometer
	m_chrono.start();
}

void Play_state::on_pop() {
	//Ungrab the mouse and controller
	get_Window().set_mouse_state(Window::MOUSE_NORMAL);
	get_Game().controller_mouse.enabled = true;

	get_Game().push_state(new Scoreboard_state());
	Game_model::dump_model();

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

	if (!m_chrono.is_running())
		return;

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
	controller->apply_actions(m_timestep);
	Game_model::get_model().update(m_timestep);
}

void Play_state::render() {
	Colors& cr = get_Colors();
	Camera* cam = Game_model::get_model().get_camera();
	Point3f temp = cam->position;
	cam->position = Point3f();

	get_Video().set_3d(*cam);
	get_Video().set_zwrite(false);

	Material m("skybox");

	Vertex3f_Texture v1(Point3f(-50.0f, -50.0f, -50.0f), Point2f(0.0f, 0.0f));
	Vertex3f_Texture v2(Point3f(-50.0f, -50.0f, 50.0f), Point2f(1.0f, 0.0f));
	Vertex3f_Texture v3(Point3f(-50.0f, 50.0f, -50.0f), Point2f(0.0f, 1.0f));
	Vertex3f_Texture v4(Point3f(-50.0f, 50.0f, 50.0f), Point2f(1.0f, 1.0f));
	Vertex3f_Texture v5(Point3f(50.0f, -50.0f, -50.0f), Point2f(1.0f, 1.0f));
	Vertex3f_Texture v6(Point3f(50.0f, -50.0f, 50.0f), Point2f(0.0f, 1.0f));
	Vertex3f_Texture v7(Point3f(50.0f, 50.0f, -50.0f), Point2f(1.0f, 0.0f));
	Vertex3f_Texture v8(Point3f(50.0f, 50.0f, 50.0f), Point2f(0.0f, 0.0f));

	Quadrilateral<Vertex3f_Texture> q1(v1, v3, v4, v2);
	Quadrilateral<Vertex3f_Texture> q2(v8, v7, v5, v6);
	Quadrilateral<Vertex3f_Texture> q3(v2, v6, v5, v1);
	Quadrilateral<Vertex3f_Texture> q4(v3, v7, v8, v4);
	Quadrilateral<Vertex3f_Texture> q5(v1, v5, v7, v3);
	Quadrilateral<Vertex3f_Texture> q6(v2, v6, v8, v4);
	q1.fax_Material(&m);
	q2.fax_Material(&m);
	q3.fax_Material(&m);
	q4.fax_Material(&m);
	q5.fax_Material(&m);
	q6.fax_Material(&m);

	get_Video().render(q1);
	get_Video().render(q2);
	get_Video().render(q3);
	get_Video().render(q4);
	get_Video().render(q5);
	get_Video().render(q6);

	cam->position = temp;
	view->render();
}
