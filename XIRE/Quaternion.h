#pragma once

#include "XIRE_Afx.h"
#include "Vectorf3.hpp"
#include <math.h>
#include <assert.h> 

static inline float isqrtf(float x) { return 1.f / sqrtf(x); }
static inline void sincosf(float angle, float* pSin, float* pCos) { *pSin = float(sin(angle));	*pCos = float(cos(angle)); }

NS_Begin(XIRE)
NS_Begin(core)

//struct Quaternionernion
//{
//public:
//
//	Quaternionernion();
//
//	virtual ~Quaternionernion();
//
//	Quaternionernion operator*(const Quaternionernion& b)
//	{
//		return 
//	}
//
//public:
//
//	F32 a;
//	F32 b;
//	F32 c;
//	F32 w;
//};

struct Quaternion;

float operator | (const Quaternion& q, const Quaternion& p);

XIRE_ALIGN struct Quaternion
{
	union
	{
		XIRE_ALIGN struct { Vectorf3 v; float w; };
		XIRE_ALIGN struct { float x, y, z, w; };
	};

	Quaternion() {}

	Quaternion(float W, float X, float Y, float Z, bool bNorm = false)
		: w(W), v(X, Y, Z)
	{
		if (bNorm) Normalize();
		assert(IsValid());
	}

	Quaternion(float angle, const Vectorf3 &axis) : w(angle), v(axis) {};

	// 四元数 单乘
	void operator *= (float op) { w *= op; v *= op; }

	// 四元数相当对比
	//bool operator==(const Quaternion &q) const { return IsEqual(q,0.0000001f); }
	//bool operator!=(const Quaternion &q) const { return !(*this == q); }

	// 四元数求逆
	Quaternion operator ! () const;

	// 检查是否为单位四元数
	bool IsIdentity() const { return w == 1 && v.x == 0 && v.y == 0 && v.z == 0; }
	void SetIdentity(void);
	static Quaternion CreateIdentity(void);

	void SetRotationX(float r);
	static Quaternion CreateRotationX(float r);
	void SetRotationY(float r);
	static Quaternion CreateRotationY(float r);
	void SetRotationZ(float r);
	static Quaternion CreateRotationZ(float r);

	Vectorf3 GetColumn0() const { return Vectorf3(2 * (v.x*v.x + w*w) - 1, 2 * (v.y*v.x + v.z*w), 2 * (v.z*v.x - v.y*w)); }
	Vectorf3 GetColumn1() const { return Vectorf3(2 * (v.x*v.y - v.z*w), 2 * (v.y*v.y + w*w) - 1, 2 * (v.z*v.y + v.x*w)); }
	Vectorf3 GetColumn2() const { return Vectorf3(2 * (v.x*v.z + v.y*w), 2 * (v.y*v.z - v.x*w), 2 * (v.z*v.z + w*w) - 1); }
	Vectorf3 GetRow0() const { return Vectorf3(2 * (v.x*v.x + w*w) - 1, 2 * (v.x*v.y - v.z*w), 2 * (v.x*v.z + v.y*w)); }
	Vectorf3 GetRow1() const { return Vectorf3(2 * (v.y*v.x + v.z*w), 2 * (v.y*v.y + w*w) - 1, 2 * (v.y*v.z - v.x*w)); }
	Vectorf3 GetRow2() const { return Vectorf3(2 * (v.z*v.x - v.y*w), 2 * (v.z*v.y + v.x*w), 2 * (v.z*v.z + w*w) - 1); }

	void Invert(void);
	Quaternion GetInverted() const;

	void	Normalize(void);
	Quaternion GetNormalized() const;

	float GetLength() const;

	// 	 bool IsEqual( const Quaternion& q, float e= SR_EQUAL_PRECISION) const {
	// 		Quaternion p=-q;
	// 		bool t0= (abs(v.x-q.v.x)<=e) && (abs(v.y-q.v.y)<=e) && (abs(v.z-q.v.z)<=e) && (abs(w-q.w)<=e);	
	// 		bool t1= (abs(v.x-p.v.x)<=e) && (abs(v.y-p.v.y)<=e) && (abs(v.z-p.v.z)<=e) && (abs(w-p.w)<=e);	
	// 		t0 |= t1;
	// 		return t0;
	// 	}

	bool IsUnit(float e = EQUAL_EPSILON) const
	{
		return abs(1 - ((*this) | (*this))) < e;
	}

	bool IsValid(float e = EQUAL_EPSILON) const
	{
		if (!IsUnit(e))	return false;
		return true;
	}
};

inline float operator | (const Quaternion& q, const Quaternion& p)
{
	return (q.v.x*p.v.x + q.v.y*p.v.y + q.v.z*p.v.z + q.w*p.w);
}

inline Quaternion  operator * (const Quaternion &q, const Quaternion &p) {
	return Quaternion
	(
		q.w*p.w - (q.v.x*p.v.x + q.v.y*p.v.y + q.v.z*p.v.z),
		q.v.y*p.v.z - q.v.z*p.v.y + q.w*p.v.x + q.v.x*p.w,
		q.v.z*p.v.x - q.v.x*p.v.z + q.w*p.v.y + q.v.y*p.w,
		q.v.x*p.v.y - q.v.y*p.v.x + q.w*p.v.z + q.v.z*p.w
	);
}

inline void operator *= (Quaternion &q, const Quaternion &p) {
	float s0 = q.w; q.w = q.w*p.w - (Vectorf3::dot(q.v, p.v)); q.v = p.v*s0 + q.v*p.w + (q.v%p.v);
}

inline  Quaternion operator / (const Quaternion &q, const Quaternion &p) {
	return (!p*q);
}
inline  void operator /= (Quaternion &q, const Quaternion &p) {
	q = (!p*q);
}

inline  Quaternion operator + (const Quaternion &q, const Quaternion &p) {
	return Quaternion(q.w + p.w, q.v + p.v);
}

inline  void operator += (Quaternion &q, const Quaternion &p) {
	q.w += p.w; q.v += p.v;
}

//   Quaternion operator % (const Quaternion &q, const Quaternion &tp) { 
// 	Quaternion p=tp;
// 	if( (p|q) < 0 ) { p=-p;	} 
// 	return Quaternion( q.w+p.w, q.v+p.v ); 
// }
// 
//   void operator %= (Quaternion &q, const Quaternion &tp) { 
// 	Quaternion p=tp;
// 	if( (p|q) < 0 ) { p=-p;	} 
// 	q = Quaternion( q.w+p.w, q.v+p.v ); 
// }

inline  Quaternion operator - (const Quaternion &q, const Quaternion &p) {
	return Quaternion(q.w - p.w, q.v - p.v);
}

inline void operator -= (Quaternion &q, const Quaternion &p) {
	q.w -= p.w; q.v -= p.v;
}

inline Quaternion	operator * (float t, const Quaternion &q) {
	return Quaternion(t*q.w, q.v * t);
};

inline Quaternion	operator * (const Quaternion &q, float t) {
	return Quaternion(q.w*t, q.v*t);
};

inline Quaternion	operator / (const Quaternion &q, float t) {
	return Quaternion(q.w / t, q.v / t);
};

inline Vectorf3 operator * (const Quaternion &q, const Vectorf3 &v) {
	Vectorf3 out, r2;
	r2.x = (q.v.y*v.z - q.v.z*v.y) + q.w*v.x;
	r2.y = (q.v.z*v.x - q.v.x*v.z) + q.w*v.y;
	r2.z = (q.v.x*v.y - q.v.y*v.x) + q.w*v.z;
	out.x = (r2.z*q.v.y - r2.y*q.v.z); out.x += out.x + v.x;
	out.y = (r2.x*q.v.z - r2.z*q.v.x); out.y += out.y + v.y;
	out.z = (r2.y*q.v.x - r2.x*q.v.y); out.z += out.z + v.z;
	return out;
}

inline Vectorf3 operator * (const Vectorf3 &v, const Quaternion &q) {
	Vectorf3 out, r2;
	r2.x = (q.v.z*v.y - q.v.y*v.z) + q.w*v.x;
	r2.y = (q.v.x*v.z - q.v.z*v.x) + q.w*v.y;
	r2.z = (q.v.y*v.x - q.v.x*v.y) + q.w*v.z;
	out.x = (r2.y*q.v.z - r2.z*q.v.y); out.x += out.x + v.x;
	out.y = (r2.z*q.v.x - r2.x*q.v.z); out.y += out.y + v.y;
	out.z = (r2.x*q.v.y - r2.y*q.v.x); out.z += out.z + v.z;
	return out;
}

inline  Quaternion Quaternion::operator ! () const { return Quaternion(w, -v); }
inline  void Quaternion::Invert(void) { *this = !*this; }
inline  Quaternion Quaternion::GetInverted() const { return !(*this); }

inline  Quaternion Quaternion::CreateIdentity(void) { return Quaternion(1, 0, 0, 0); }
inline  void	Quaternion::SetIdentity(void) { w = 1; v.x = 0; v.y = 0; v.z = 0; }

inline  Quaternion Quaternion::CreateRotationX(float r)
{
	Quaternion q;	q.SetRotationX(r); 	return q;
}

inline  void Quaternion::SetRotationX(float r)
{
	float s, c;
	sincosf(float(r*(float)0.5), &s, &c); w = c; v.x = s; v.y = 0; v.z = 0;
}

inline  Quaternion Quaternion::CreateRotationY(float r)
{
	Quaternion q;	q.SetRotationY(r); 	return q;
}

inline  void Quaternion::SetRotationY(float r)
{
	float s, c; sincosf(float(r*(float)0.5), &s, &c); w = c; v.x = 0; v.y = s; v.z = 0;
}

inline  Quaternion Quaternion::CreateRotationZ(float r)
{
	Quaternion q;	q.SetRotationZ(r); 	return q;
}
inline  void Quaternion::SetRotationZ(float r)
{
	float s, c; sincosf(float(r*(float)0.5), &s, &c); w = c; v.x = 0; v.y = 0; v.z = s;
}

inline void Quaternion::Normalize(void)
{
	float d = isqrtf(w*w + v.x*v.x + v.y*v.y + v.z*v.z);
	w *= d;
	v.x *= d;
	v.y *= d;
	v.z *= d;
}

inline Quaternion Quaternion::GetNormalized() const
{
	Quaternion t = *this;
	t.Normalize();
	return t;
}

inline float Quaternion::GetLength() const
{
	return sqrtf(w*w + v.x*v.x + v.y*v.y + v.z*v.z);
}


NS_End(core)
NS_End(XIRE)