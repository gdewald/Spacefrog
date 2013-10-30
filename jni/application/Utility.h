#pragma once

#include <zenilib.h>

float dot_product(Zeni::Quaternion a, Zeni::Quaternion b);
Zeni::Quaternion inverse(Zeni::Quaternion a);
Zeni::Quaternion quaternion_slerp(Zeni::Quaternion src, Zeni::Quaternion dest, float t);
Zeni::Quaternion quaternion_lerp(Zeni::Quaternion src, Zeni::Quaternion dest, float t);
