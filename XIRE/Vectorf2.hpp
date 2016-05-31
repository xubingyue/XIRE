#pragma once

#include "XIRE_Afx.h"
#include "MatrixSIMD.hpp"

NS_Begin(XIRE)
NS_Begin(core)

XIRE_ALIGN
struct XIREAPI Vectorf2
{
public:
	union
	{
		F32 m[2];
		struct { float x; float y; };
	};

	Vectorf2()
	{
	}

	Vectorf2(const float * const p)
	{
		x = p[0];
		y = p[1];
	}

	Vectorf2(const float px, const float py)
	{
		x = px;
		y = py;
	}

	inline Vectorf2 & operator += (const Vectorf2 & p)
	{
		x += p.x;
		y += p.y;
		return (*this);
	}
	inline Vectorf2 & operator -= (const Vectorf2 & p)
	{
		x -= p.x;
		y -= p.y;
		return (*this);
	}
	inline Vectorf2 & operator *= (const Vectorf2& p)
	{
		x *= p.x;
		y *= p.y;
		return (*this);
	}
	inline Vectorf2 & operator *= (const float p)
	{
		x *= p;
		y *= p;
		return (*this);
	}
	inline Vectorf2 & operator /= (const float p)
	{
		x /= p;
		y /= p;
		return (*this);
	}

	inline Vectorf2 operator + (const Vectorf2 & p) const
	{
		Vectorf2 tmp(x + p.x, y + p.y);
		return tmp;
	}

	inline Vectorf2 operator - (const Vectorf2 & p) const
	{
		Vectorf2 tmp(x - p.x, y - p.y);
		return tmp;
	}

	inline float operator % (const Vectorf2 & p) const
	{
		return x * p.y - y * p.x;
	}

	inline Vectorf2 operator * (const Vectorf2 & p) const
	{
		Vectorf2 tmp(x * p.x, y * p.y);
		return tmp;
	}

	inline Vectorf2 operator * (const float p) const
	{
		Vectorf2 tmp(x * p, y * p);
		return tmp;
	}

	inline Vectorf2 operator / (const float p) const
	{
		Vectorf2 tmp(x / p, y / p);
		return tmp;
	}

	bool operator == (const Vectorf2 & p) const
	{
		if (x + EQUAL_EPSILON < p.x || x - EQUAL_EPSILON > p.x)
		{
			return false;
		}
		if (y + EQUAL_EPSILON < p.y || y - EQUAL_EPSILON > p.y)
		{
			return false;
		}
		return true;
	}
	bool operator != (const Vectorf2 & p) const
	{
		if (x + EQUAL_EPSILON < p.x || x - EQUAL_EPSILON > p.x)
		{
			return true;
		}
		if (y + EQUAL_EPSILON < p.y || y - EQUAL_EPSILON > p.y)
		{
			return true;
		}
		return false;
	}

	inline float length() const
	{
		return sqrt(x * x + y * y);
	}
	inline float lengthsq() const
	{
		return x * x + y * y;
	}
	inline Vectorf2 & normalize()
	{
		(*this) /= length();
		return (*this);
	}

	inline void zero()
	{
		memset(this, 0, sizeof(Vectorf2));
	}

	inline void set(float nx, float ny)
	{
		x = nx;
		y = ny;
	}

	inline Vectorf2& reflect(Vectorf2& i, Vectorf2& n)
	{
		*this = i - n * (i.dot(n)*2.f);
		return *this;
	}

	inline float dot(Vectorf2& rhs)
	{
		return x * rhs.x + y * rhs.y;
	}

	static inline float dot(Vectorf2& lhs, Vectorf2& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
};

NS_End(core)
NS_End(XIRE)