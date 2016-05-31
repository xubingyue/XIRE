#pragma once

#include "XIRE_Afx.h"
#include "Vectorf2.hpp"

NS_Begin(XIRE)
NS_Begin(core)

XIRE_ALIGN
struct XIREAPI Vectorf3
{
public:
	union
	{
		float m[3];
		struct { float x, y, z; };
		struct { float r, g, b; };
		struct { Vectorf2 xy; float z; };
		__m128 m128;
	};

	Vectorf3()
	{

	}

	Vectorf3(const float px, const float py, const float pz)
	{
		// #ifdef USE_SIMD
		// 		m128 = _mm_set_ps(0, pz, py, px);
		// #else
		x = px;
		y = py;
		z = pz;
		//#endif
	}

	/**
	*@brief Vectorf3的快捷建立方式 Vectorf3( Vectorf2(x,y),z );
	*@return
	*@param const Vectorf2 pxy
	*@param const float pz
	*/
	Vectorf3(const Vectorf2& pxy, const float pz)
	{
#ifdef USE_SIMD
		m128 = _mm_set_ps(0, pz, pxy.x, pxy.y);
#else
		x = pxy.x;
		y = pxy.y;
		z = pz;
#endif
	}

	Vectorf3(const float px)
	{
#ifdef USE_SIMD
		m128 = _mm_set_ps1(px);
#else
		x = px;
		y = px;
		z = px;
#endif
	}

	inline Vectorf3 & operator += (const Vectorf3 & p)
	{
#ifdef USE_SIMD
		m128 = _mm_add_ps(m128, p.m128);
#else
		x += p.x;
		y += p.y;
		z += p.z;
#endif
		return (*this);
	}
	inline Vectorf3 & operator -= (const Vectorf3 & p)
	{
#ifdef USE_SIMD
		m128 = _mm_sub_ps(m128, p.m128);
#else
		x -= p.x;
		y -= p.y;
		z -= p.z;
#endif
		return (*this);
	}
	inline Vectorf3 operator *= (const Vectorf3 & p)
	{
#ifdef USE_SIMD
		m128 = _mm_mul_ps(m128, p.m128);
#else
		x *= p.x;
		y *= p.y;
		z *= p.z;
#endif
		return (*this);
	}
	inline Vectorf3 & operator *= (const float p)
	{
#ifdef USE_SIMD
		__m128 div = _mm_set_ps1(p);
		m128 = _mm_mul_ps(m128, div);
#else
		x *= p;
		y *= p;
		z *= p;
#endif
		return (*this);
	}
	inline Vectorf3 & operator /= (const float p)
	{
#ifdef USE_SIMD
		__m128 div = _mm_set_ps1(p);
		m128 = _mm_div_ps(m128, div);
#else
		x /= p;
		y /= p;
		z /= p;
#endif
		return (*this);
	}

	inline Vectorf3 operator + (const Vectorf3 & p) const
	{
#ifdef USE_SIMD
		Vectorf3 tmp;
		tmp.m128 = _mm_add_ps(m128, p.m128);
#else
		Vectorf3 tmp(x + p.x, y + p.y, z + p.z);
#endif
		return tmp;
	}
	inline Vectorf3 operator - (const Vectorf3 & p) const
	{
#ifdef USE_SIMD
		Vectorf3 tmp;
		tmp.m128 = _mm_sub_ps(m128, p.m128);
#else
		Vectorf3 tmp(x - p.x, y - p.y, z - p.z);
#endif
		return tmp;
	}
	inline Vectorf3 operator - () const
	{
#ifdef USE_SIMD
		Vectorf3 tmp;
		tmp.m128 = _mm_setzero_ps();
		tmp.m128 = _mm_sub_ps(tmp.m128, m128);
#else
		Vectorf3 tmp(-x, -y, -z);
#endif
		return tmp;
	}

	inline Vectorf3 CrossProduct(const Vectorf3 &p)
	{
#ifdef USE_SIMD
		Vectorf3 tmp;
		tmp.m128 = _mm_cross3_ps(m128, p.m128);
#else
		Vectorf3 tmp(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
#endif
		return tmp;
	}

	inline Vectorf3 operator %= (const Vectorf3 & p)
	{
#ifdef USE_SIMD
		m128 = _mm_cross3_ps(m128, p.m128);
#else
		Vectorf3 tmp(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
		x = tmp.x;
		y = tmp.y;
		z = tmp.z;
#endif
		return (*this);
	}

	inline Vectorf3 operator % (const Vectorf3 & p) const
	{
#ifdef USE_SIMD
		Vectorf3 tmp;
		tmp.m128 = _mm_cross3_ps(m128, p.m128);
#else
		Vectorf3 tmp(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
#endif
		return tmp;
	}

	inline Vectorf3 operator * (const Vectorf3 & p) const
	{
#ifdef USE_SIMD
		Vectorf3 tmp;
		tmp.m128 = _mm_mul_ps(m128, p.m128);
#else
		Vectorf3 tmp(x * p.x, y * p.y, z * p.z);
#endif
		return tmp;
	}

	inline Vectorf3 operator * (const float p) const
	{
#ifdef USE_SIMD
		Vectorf3 tmp;
		tmp.m128 = _mm_set_ps1(p);
		tmp.m128 = _mm_mul_ps(m128, tmp.m128);
#else
		Vectorf3 tmp(x * p, y * p, z * p);
#endif
		return tmp;
	}
	inline Vectorf3 operator / (const float p) const
	{
#ifdef USE_SIMD
		Vectorf3 tmp;
		tmp.m128 = _mm_set_ps1(p);
		tmp.m128 = _mm_div_ps(m128, tmp.m128);
#else
		Vectorf3 tmp(x / p, y / p, z / p);
#endif
		return tmp;
	}

	bool operator == (const Vectorf3 & p) const
	{
		if (x + EQUAL_EPSILON < p.x || x - EQUAL_EPSILON > p.x)
		{
			return false;
		}
		if (y + EQUAL_EPSILON < p.y || y - EQUAL_EPSILON > p.y)
		{
			return false;
		}
		if (z + EQUAL_EPSILON < p.z || z - EQUAL_EPSILON > p.z)
		{
			return false;
		}
		return true;
	}
	bool operator != (const Vectorf3 & p) const
	{
		if (x + EQUAL_EPSILON < p.x || x - EQUAL_EPSILON > p.x)
		{
			return true;
		}
		if (y + EQUAL_EPSILON < p.y || y - EQUAL_EPSILON > p.y)
		{
			return true;
		}
		if (z + EQUAL_EPSILON < p.z || z - EQUAL_EPSILON > p.z)
		{
			return true;
		}
		return true;
	}
	inline float lengthsq() const
	{
#ifdef USE_SIMD
		Vectorf3 tmp;
		tmp.m128 = _mm_mul_ps(m128, m128);
		return tmp.x + tmp.y + tmp.z;
#else
		return x * x + y * y + z * z;
#endif
	}

	inline float length() const
	{
		return sqrt(lengthsq());
	}

	inline Vectorf3 & normalize()
	{
		(*this) /= length();
		return (*this);
	}

	inline Vectorf3& reflect(Vectorf3& i, Vectorf3& n)
	{
		*this = i - n * (i.dot(n)*2.f);
		return *this;
	}

	inline float dot(const Vectorf3& rhs)
	{
#ifdef USE_SIMD
		return *(float*)(&_mm_dot_ps(m128, rhs.m128));
#else
		return x * rhs.x + y * rhs.y + z * rhs.z;
#endif
	}

	static inline float dot(const Vectorf3& lhs, const Vectorf3& rhs)
	{
#ifdef USE_SIMD
		return *(float*)(&_mm_dot_ps(lhs.m128, rhs.m128));
#else
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
#endif
	}
};

NS_End(core)
NS_End(XIRE)