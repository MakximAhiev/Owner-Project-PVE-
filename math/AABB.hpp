#pragma once
#ifndef AABB_hpp
#define AABB_hpp
#include "Vec3.hpp"
struct AABB
{
	Vec3_tpl<float> min, max;
	Vec3_tpl<float> GetCenter() { return (min + max) * 0.5f; }
	bool IsReset() { return min.x > max.x; }
	void Reset() { min = Vec3_tpl<float>(1e15f); max = Vec3_tpl<float>(-1e15f); }
};
#endif // !AABB_hpp
