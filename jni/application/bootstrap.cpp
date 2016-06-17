/* This file is part of the Zenipex Library (zenilib).
 * Copyleft (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * This source file is simply under the public domain.
 */

#include <zenilib.h>
#include "Game_states/Play_state.h"
#include "Game_states/Instructions_state.h"

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;

class Title_state_custom : public Title_State<Play_state, Instructions_state> {
public:
	Title_state_custom(String title_) : Title_State(title_) {
		Colors& cr = get_Colors();
		//m_widgets.unlend_Widget(play_button);
		//m_widgets.lend_Widget(play_button);
	}

	void render() {
		render_image("skybox", Point2f(), Point2f(get_Window().get_size()));
		Title_State::render();
	}
};

class Bootstrap {
  class Gamestate_One_Initializer : public Gamestate_Zero_Initializer {
    virtual Gamestate_Base * operator()() {
      Window::set_title("zenilib Application");

      get_Controllers();
      get_Video();
      get_Textures();
      get_Fonts();
      get_Sounds();

      return new Title_state_custom("SPACE\nFROG");
    }
  } m_goi;

public:
  Bootstrap() {
    g_gzi = &m_goi;
  }
} g_bootstrap;

int main(int argc, char **argv) {
  return zenilib_main(argc, argv);
}
