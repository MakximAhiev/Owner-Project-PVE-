#pragma once
#include "Vec3.hpp"
#ifndef Color_hpp
#define Color_hpp
template <class T> struct Color_tpl;
typedef Color_tpl<unsigned char> ColorB;
typedef Color_tpl<float> ColorF;

template <class T> struct Color_tpl
{
	T	r, g, b, a;
	inline Color_tpl() {};
	Color_tpl(T _x, T _y, T _z, T _w) {};
	Color_tpl(T _x, T _y, T _z) {};
	Color_tpl(const unsigned int abgr) {};
	Color_tpl(const float c) {};
	Color_tpl(const ColorF& c) {};
	Color_tpl(const Vec3& c, float fAlpha) {};
};
template<> inline Color_tpl<float>::Color_tpl(float _x, float _y, float _z, float _w)
{
	r = _x; g = _y; b = _z; a = _w;
}
template<> inline Color_tpl<float>::Color_tpl(float _x, float _y, float _z)
{
	r = _x; g = _y; b = _z; a = 1.f;
}
template<> inline Color_tpl<unsigned char>::Color_tpl(unsigned char _x, unsigned char _y, unsigned char _z, unsigned char _w)
{
	r = _x; g = _y; b = _z; a = _w;
}
template<> inline Color_tpl<unsigned char>::Color_tpl(unsigned char _x, unsigned char _y, unsigned char _z)
{
	r = _x; g = _y; b = _z; a = 255;
}
template<> inline Color_tpl<float>::Color_tpl(const unsigned int abgr)
{
	r = (abgr & 0xff) / 255.0f;
	g = ((abgr >> 8) & 0xff) / 255.0f;
	b = ((abgr >> 16) & 0xff) / 255.0f;
	a = ((abgr >> 24) & 0xff) / 255.0f;
}
template<> inline Color_tpl<unsigned char>::Color_tpl(const unsigned int c) { *(unsigned int*)(&r) = c; }
template<> inline Color_tpl<float>::Color_tpl(const float c)
{
	r = c;	g = c;	b = c;	a = c;
}
template<> inline Color_tpl<unsigned char>::Color_tpl(const float c)
{
	r = (unsigned char)(c * 255);	g = (unsigned char)(c * 255);	b = (unsigned char)(c * 255);	a = (unsigned char)(c * 255);
}
template<> inline Color_tpl<float>::Color_tpl(const ColorF& c)
{
	r = c.r;	g = c.g;	b = c.b;	a = c.a;
}
template<> inline Color_tpl<unsigned char>::Color_tpl(const ColorF& c) {
	r = (unsigned char)(c.r * 255);	g = (unsigned char)(c.g * 255);	b = (unsigned char)(c.b * 255);	a = (unsigned char)(c.a * 255);
}
template<> inline Color_tpl<float>::Color_tpl(const Vec3& c, float fAlpha)
{
	r = c.x;	g = c.y;	b = c.z;	a = fAlpha;
}
template<> inline Color_tpl<unsigned char>::Color_tpl(const Vec3& c, float fAlpha)
{
	r = (unsigned char)(c.x * 255);	g = (unsigned char)(c.y * 255);	b = (unsigned char)(c.z * 255);	a = (unsigned char)(fAlpha * 255);
}
#endif // !Color_hpp
