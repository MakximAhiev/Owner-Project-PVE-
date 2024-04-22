#ifndef Plane_tpl_hpp
#define Plane_tpl_hpp
#include "../math/Vec3.hpp"
template <typename T>
struct Plane_tpl {
	Vec3_tpl<T> n;
	T d;
};
#endif // !Plane_tpl_hpp
