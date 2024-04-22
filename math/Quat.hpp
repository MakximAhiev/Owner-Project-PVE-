#pragma once
#ifndef Quat_hpp
#define Quat_hpp
#include "Vec3.hpp"
template <typename F>
struct Quat_tpl {

	Vec3_tpl< F > v;
	F w;

	Quat_tpl() { }
};
typedef Quat_tpl<float> Quat;
#endif // !Quat_hpp
