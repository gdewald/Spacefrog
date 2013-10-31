#pragma once

#include <zenilib.h>
#include <map>

class Points {
	int pts;
	int high_score_pts;

	int hits;

	static Points* instance;
	Points() {
		reset();
	}

public:
	static Points& get_Points() {
		if (!instance) instance = new Points();
		return *instance;
	}

	void save_score();

	void hit() { hits++; pts += 50 + 5 * hits; }

	void reset();

	void render(Zeni::Point2f ul, Zeni::Point2f lr) {
		Zeni::Colors& cr = Zeni::get_Colors();
		Zeni::String col = "white";

		Zeni::get_Fonts()["system_36_800x600"].render_text(Zeni::String("Food:  " + Zeni::itoa(hits)), Zeni::Vector3f(lr.x - 300.0f, ul.y, 0), Zeni::Vector3f(1, 0, 0), Zeni::Vector3f(0, 1, 0), cr[col]);
		Zeni::get_Fonts()["system_36_800x600"].render_text("Score: " + Zeni::itoa(pts), Zeni::Vector3f(lr.x - 300.0f, ul.y + 20.0f, 0), Zeni::Vector3f(1, 0, 0), Zeni::Vector3f(0, 1, 0), Zeni::get_Colors()["white"]);
	}

	void render_scores();
};
