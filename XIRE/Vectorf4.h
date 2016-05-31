#pragma once

#include "XIRE_Afx.h"
#include "Vectorf2.hpp"
#include "Vectorf3.hpp" 

NS_Begin(XIRE)
NS_Begin(core)

class Matrixf44;

XIRE_ALIGN
struct XIREAPI Vectorf4
{
public:
	union
	{
		XIRE_ALIGN F32 m[4];

		XIRE_ALIGN struct { float x, y, z, w; };
#ifdef SR_COLOR_RGBA
		SR_ALIGN struct { float r, g, b, a; };
#else
		XIRE_ALIGN struct { float a, r, g, b; };
#endif
		XIRE_ALIGN struct {
			Vectorf3 xyz;
		};
		XIRE_ALIGN struct {
			Vectorf3 rgb;
		};
		XIRE_ALIGN struct {
			Vectorf2 xy; Vectorf2 zw;
		};

#ifdef USE_SIMD
		__m128 m128;
#endif
	};

	Vectorf4();

	Vectorf4(const float * const p);

	Vectorf4(const float px, const float py, const float pz, const float pw);

	Vectorf4(const float px);

	Vectorf4(const Vectorf3& v, const float pw);

	inline Vectorf4 & operator += (const Vectorf4 & p);

	inline Vectorf4 & operator -= (const Vectorf4 & p);

	inline Vectorf4 & operator %= (const Vectorf4 & p);

	inline Vectorf4 & operator *= (const Vectorf4 & p);

	inline Vectorf4 & operator *= (const float p);

	inline Vectorf4 & operator /= (const float p);

	inline Vectorf4 operator + (const Vectorf4 & p) const;

	inline Vectorf4 operator - (const Vectorf4 & p) const;

	inline Vectorf4 operator % (const Vectorf4 & p) const;

	inline Vectorf4 operator * (const Vectorf4 & p) const;

	inline Vectorf4 operator * (const float p) const; 
 
	inline Vectorf4 operator / (const float p) const;

	inline Vectorf4 operator * (const Matrixf44& p) const;

	bool operator == (const Vectorf4 & p) const;

	bool operator != (const Vectorf4 & p) const;

	inline float length() const;

	inline float lengthsq() const;

	inline Vectorf4 & normalize();

	inline void sqrt();

	inline float dot(Vectorf4& rhs);

	static inline float dot(Vectorf4& lhs, Vectorf4& rhs);
}; 

NS_End(core)
NS_End(XIRE)