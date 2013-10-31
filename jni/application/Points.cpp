#include "Points.h"
#include <fstream>

using namespace Zeni;
using namespace std;

Points* Points::instance = nullptr;

void Points::reset() {
	pts = 0;
	hits = 0;

	fstream scores_in(String("score.sav").c_str(), fstream::in);
	if (scores_in.good()) {
		scores_in >> high_score_pts;
	}
	else high_score_pts = 0;
	scores_in.close();
}

void Points::save_score() {
	if (pts >= high_score_pts) {
		fstream scores_out(String("score.sav").c_str(), fstream::out);
		scores_out << pts << endl;
		scores_out.close();
	}
}

void Points::render_scores() {
	Colors& cr = get_Colors();

	if (pts > high_score_pts) {
		get_Fonts()["system_36_800x600"].render_text("New High Score!", Vector3f(160.0f, 175.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["green"]);
	}
	get_Fonts()["system_36_800x600"].render_text("Score: " + itoa(pts), Vector3f(160.0f, 235.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
	if (high_score_pts > 0) {
		get_Fonts()["system_36_800x600"].render_text("High Score: " + itoa(high_score_pts), Vector3f(160.0f, 295.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
	}
}
