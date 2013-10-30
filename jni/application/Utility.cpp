#include "Utility.h"

using namespace std;
using namespace Zeni;

float dot_product(Zeni::Quaternion a, Zeni::Quaternion b) {
	float result = 0.0f;
	for (int i = 0; i < 4; i++) {
		result += a[i] * b[i];
	}
	return result;
}

Quaternion inverse(Zeni::Quaternion a) {
	//float result = 0.0f;
	//for (int i = 0; i < 4; i++) {
	//	result += a[i] * a[i];
	//	if (i) a[i] = -a[i];
	//}
	//return a / result;
	return a.normalized().conjugate();
}

//Slurp calc, t between 0 and 1
Quaternion quaternion_slerp(Quaternion src, Quaternion dest, float t) {
	if (t <= 0.0f) return src;
	else if (t >= 1.0f) return dest;


	if (abs((inverse(src) * dest).get_rotation().second) < 0.05f) return quaternion_lerp(src, dest, t);

	//omega = theta/2
	float cos_omega = dot_product(src, dest);

	if (cos_omega < 0.0f) {
		cos_omega = -cos_omega;
		dest = -dest;
	}
	return quaternion_lerp(src, dest, t);

	float omega = acosf(cos_omega);
	//if (omega < 0.01 && omega > -0.01) return src;

	return (sinf((1.0f - t) * omega) * src + sinf(t * omega) * dest) / sin(omega);
}

Quaternion quaternion_lerp(Quaternion src, Quaternion dest, float t) {
	if (t <= 0.0f) return src;
	else if (t >= 1.0f) return dest;

	return (src*(1 - t) + dest*t).normalized();
}
