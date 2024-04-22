#pragma once
#ifndef Matrix34_hpp
#define Matrix34_hpp
#include "QuatT.hpp"
#include "Vec3.hpp"
template <typename F> struct Matrix34_tpl
{
	 Matrix34_tpl(typeZero) : m00(0), m01(0), m02(0), m03(0), m10(0), m11(0), m12(0), m13(0), m20(0), m21(0), m22(0), m23(0) {}
	F m00, m01, m02, m03;
	F m10, m11, m12, m13;
	F m20, m21, m22, m23;

	Matrix34_tpl() : m00(0), m01(0), m02(0), m03(0), m10(0), m11(0), m12(0), m13(0), m20(0), m21(0), m22(0), m23(0) {}

	Matrix34_tpl(F xm00, F xm01, F xm02, F xm03, F xm10, F xm11, F xm12, F xm13, F xm20, F xm21, F xm22, F xm23)
	{
		m00 = xm00;
		m01 = xm01;
		m02 = xm02;
		m03 = xm03;
		m10 = xm10;
		m11 = xm11;
		m12 = xm12;
		m13 = xm13;
		m20 = xm20;
		m21 = xm21;
		m22 = xm22;
		m23 = xm23;
	}


	template<class F1> explicit Matrix34_tpl(const QuatT_tpl<F1>& q)
	{
		////JUNK_CODE_THREE//VMProtectBeginMutation("explicit Matrix34_tpl");
		Vec3_tpl<F1> v2 = q.q.v + q.q.v;
		F1 xx = 1 - v2.x * q.q.v.x;		F1 yy = v2.y * q.q.v.y;		F1 xw = v2.x * q.q.w;
		F1 xy = v2.y * q.q.v.x;			F1 yz = v2.z * q.q.v.y;		F1 yw = v2.y * q.q.w;
		F1 xz = v2.z * q.q.v.x;			F1 zz = v2.z * q.q.v.z;		F1 zw = v2.z * q.q.w;
		m00 = F(1 - yy - zz);					m01 = F(xy - zw);					m02 = F(xz + yw);			m03 = F(q.t.x);
		m10 = F(xy + zw);						m11 = F(xx - zz);					m12 = F(yz - xw);			m13 = F(q.t.y);
		m20 = F(xz - yw);						m21 = F(yz + xw);					m22 = F(xx - yy);			m23 = F(q.t.z);
		// 
	}

	Vec3_tpl<F> GetTranslation() const
	{

		return Vec3_tpl<F>(m03, m13, m23);

	}
	Vec3_tpl<F> GetColumn0() const { return Vec3_tpl<F>{ m00, m10, m20 }; }
	Vec3_tpl<F> GetColumn1() const { return Vec3_tpl<F>{ m01, m11, m21 }; }
	Vec3_tpl<F> GetColumn2() const { return Vec3_tpl<F>{ m02, m12, m22 }; }
	Vec3_tpl<F> GetColumn3() const { return Vec3_tpl<F>{ m03, m13, m23 }; }

};
template<class F> Vec3_tpl<F> operator*(const Matrix34_tpl<F>& m, const Vec3_tpl<F>& p)
{
	Vec3_tpl<F> tp;
	tp.x = m.m00 * p.x + m.m01 * p.y + m.m02 * p.z + m.m03;
	tp.y = m.m10 * p.x + m.m11 * p.y + m.m12 * p.z + m.m13;
	tp.z = m.m20 * p.x + m.m21 * p.y + m.m22 * p.z + m.m23;
	return tp;
}
template<class F> Matrix34_tpl<F> operator * (const Matrix34_tpl<F>& l, const Matrix34_tpl<F>& r)
{
	////JUNK_CODE_THREE//VMProtectBeginMutation("Matrix34_tpl<F> operator *");
	Matrix34_tpl<F> m;
	m.m00 = l.m00 * r.m00 + l.m01 * r.m10 + l.m02 * r.m20;
	m.m10 = l.m10 * r.m00 + l.m11 * r.m10 + l.m12 * r.m20;
	m.m20 = l.m20 * r.m00 + l.m21 * r.m10 + l.m22 * r.m20;
	m.m01 = l.m00 * r.m01 + l.m01 * r.m11 + l.m02 * r.m21;
	m.m11 = l.m10 * r.m01 + l.m11 * r.m11 + l.m12 * r.m21;
	m.m21 = l.m20 * r.m01 + l.m21 * r.m11 + l.m22 * r.m21;
	m.m02 = l.m00 * r.m02 + l.m01 * r.m12 + l.m02 * r.m22;
	m.m12 = l.m10 * r.m02 + l.m11 * r.m12 + l.m12 * r.m22;
	m.m22 = l.m20 * r.m02 + l.m21 * r.m12 + l.m22 * r.m22;
	m.m03 = l.m00 * r.m03 + l.m01 * r.m13 + l.m02 * r.m23 + l.m03;
	m.m13 = l.m10 * r.m03 + l.m11 * r.m13 + l.m12 * r.m23 + l.m13;
	m.m23 = l.m20 * r.m03 + l.m21 * r.m13 + l.m22 * r.m23 + l.m23;
	// 
	return m;
}

typedef Matrix34_tpl<float> Matrix34;
#endif // !Matrix34_hpp
