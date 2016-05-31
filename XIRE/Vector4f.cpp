#include "Vectorf4.h"
#include "Matrixf44.h"


NS_Using(XIRE::core)

Vectorf4::Vectorf4()
{
}

Vectorf4::Vectorf4(const float * const p)
	{
#ifdef USE_SIMD
		m128 = _mm_loadr_ps(p);
#else
		x = p[0];
		y = p[1];
		z = p[2];
		w = p[3];
#endif
	}

Vectorf4::Vectorf4(const float px, const float py, const float pz, const float pw)
	{
		// #ifdef USE_SIMD
		// 		m128 = _mm_set_ps(pw, pz, py, px);
		// #else
		x = px;
		y = py;
		z = pz;
		w = pw;
		//#endif
	}

Vectorf4::Vectorf4(const float px)
	{
#ifdef USE_SIMD
		m128 = _mm_set_ps1(px);
#else
		x = px; y = px; z = px; w = px;
#endif
	}

Vectorf4::Vectorf4(const Vectorf3& v, const float pw)
	{
#ifdef USE_SIMD
		m128 = v.m128;
		w = pw;
#else
		x = v.x; y = v.y; z = v.z; w = pw;
#endif
	}


Vectorf4 & Vectorf4::operator += (const Vectorf4 & p)
	{
#ifdef USE_SIMD
		m128 = _mm_add_ps(m128, p.m128);
#else
		x += p.x;
		y += p.y;
		z += p.z;
		w += p.w;
#endif
		return (*this);
	}
Vectorf4 & Vectorf4::operator -= (const Vectorf4 & p)
	{
#ifdef USE_SIMD
		m128 = _mm_sub_ps(m128, p.m128);
#else
		x -= p.x;
		y -= p.y;
		z -= p.z;
		w -= p.w;
#endif
		return (*this);
	}

Vectorf4 & Vectorf4::operator %= (const Vectorf4 & p)
	{
		Vectorf4 tmp(w * p.x + x * p.w - z * p.y + y * p.z
			, w * p.y + y * p.w - x * p.z + z * p.x
			, w * p.z + z * p.w - y * p.x + x * p.y
			, w * p.w - x * p.x - y * p.y - z * p.z);
		x = tmp.x;
		y = tmp.y;
		z = tmp.z;
		w = tmp.w;
		return (*this);
	}

Vectorf4 & Vectorf4::operator *= (const Vectorf4 & p)
	{
#ifdef USE_SIMD
		m128 = _mm_mul_ps(m128, p.m128);
#else
		x *= p.x;
		y *= p.y;
		z *= p.z;
		w *= p.w;
#endif
		return (*this);
	}

Vectorf4 & Vectorf4::operator *= (const float p)
	{
#ifdef USE_SIMD
		__m128 mul = _mm_set_ps1(p);
		m128 = _mm_mul_ps(m128, mul);
#else
		x *= p;
		y *= p;
		z *= p;
		w *= p;
#endif

		return (*this);
	}
 Vectorf4 & Vectorf4::operator /= (const float p)
	{
#ifdef USE_SIMD
		__m128 div = _mm_set_ps1(p);
		m128 = _mm_div_ps(m128, div);
#else
		x /= p;
		y /= p;
		z /= p;
		w /= p;
#endif		

		return (*this);
	}

 Vectorf4 Vectorf4::operator + (const Vectorf4 & p) const
	{
#ifdef USE_SIMD
		Vectorf4 tmp;
		tmp.m128 = _mm_add_ps(m128, p.m128);
#else
		Vectorf4 tmp(x + p.x, y + p.y, z + p.z, w + p.w);
#endif
		return tmp;
	}

 Vectorf4 Vectorf4::operator - (const Vectorf4 & p) const
	{
#ifdef USE_SIMD
		Vectorf4 tmp;
		tmp.m128 = _mm_sub_ps(m128, p.m128);
#else
		Vectorf4 tmp(x - p.x, y - p.y, z - p.z, w - p.w);
#endif		
		return tmp;
	}

	Vectorf4 Vectorf4::operator % (const Vectorf4 & p) const
	{
		Vectorf4 tmp(w * p.x + x * p.w - z * p.y + y * p.z
			, w * p.y + y * p.w - x * p.z + z * p.x
			, w * p.z + z * p.w - y * p.x + x * p.y
			, w * p.w - x * p.x - y * p.y - z * p.z);
		return tmp;
	}

	inline Vectorf4 Vectorf4::operator * (const Vectorf4 & p) const
	{

#ifdef USE_SIMD
		Vectorf4 tmp;
		tmp.m128 = _mm_mul_ps(m128, p.m128);
#else
		Vectorf4 tmp(x * p.x, y * p.y, z * p.z, w * p.w);
#endif
		return tmp;
	}

	Vectorf4 Vectorf4::operator * (const Matrixf44& matrix) const
	{
		//Vectorf4 resVec; 
	 
		F32 r0 = this->m[0] * matrix._matrix[0][0] + this->m[1] * matrix._matrix[1][0] + this->m[2] * matrix._matrix[2][0] + this->m[3] * matrix._matrix[3][0];
		F32 r1 = this->m[0] * matrix._matrix[0][1] + this->m[1] * matrix._matrix[1][1] + this->m[2] * matrix._matrix[2][1] + this->m[3] * matrix._matrix[3][1];
		F32 r2 = this->m[0] * matrix._matrix[0][2] + this->m[1] * matrix._matrix[1][2] + this->m[2] * matrix._matrix[2][2] + this->m[3] * matrix._matrix[3][2];
		F32 r3 = this->m[0] * matrix._matrix[0][3] + this->m[1] * matrix._matrix[1][3] + this->m[2] * matrix._matrix[2][3] + this->m[3] * matrix._matrix[3][3];

		/*resVec.m[0] = this->m[0] * matrix._matrix[0][0] + this->m[1] * matrix._matrix[1][0] + this->m[2] * matrix._matrix[2][0] + this->m[3] * matrix._matrix[3][0];
		resVec.m[1] = this->m[0] * matrix._matrix[0][1] + this->m[1] * matrix._matrix[1][1] + this->m[2] * matrix._matrix[2][1] + this->m[3] * matrix._matrix[3][1];
		resVec.m[2] = this->m[0] * matrix._matrix[0][2] + this->m[1] * matrix._matrix[1][2] + this->m[2] * matrix._matrix[2][2] + this->m[3] * matrix._matrix[3][2];
		resVec.m[3] = this->m[0] * matrix._matrix[0][3] + this->m[1] * matrix._matrix[1][3] + this->m[2] * matrix._matrix[2][3] + this->m[3] * matrix._matrix[3][3];*/

		return Vectorf4(r0,r1,r2,r3);
	}

	inline Vectorf4 Vectorf4::operator * (const float p) const
	{
#ifdef USE_SIMD
		Vectorf4 tmp;
		tmp.m128 = _mm_set_ps1(p);
		tmp.m128 = _mm_mul_ps(m128, tmp.m128);
#else
		Vectorf4 tmp(x * p, y * p, z * p, w * p);
#endif

		return tmp;
	}

	inline Vectorf4 Vectorf4::operator / (const float p) const
	{
#ifdef USE_SIMD
		Vectorf4 tmp;
		tmp.m128 = _mm_set_ps1(p);
		tmp.m128 = _mm_div_ps(m128, tmp.m128);
#else
		Vectorf4 tmp(x / p, y / p, z / p, w / p);
#endif		
		return tmp;
	}

	bool Vectorf4::operator == (const Vectorf4 & p) const
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
		if (w + EQUAL_EPSILON < p.w || w - EQUAL_EPSILON > p.w)
		{
			return false;
		}
		return true;
	}

	bool Vectorf4::operator != (const Vectorf4 & p) const
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
		if (w + EQUAL_EPSILON < p.w || w - EQUAL_EPSILON > p.w)
		{
			return true;
		}
		return true;
	}

	inline float Vectorf4::length() const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	inline float Vectorf4::lengthsq() const
	{
		return x * x + y * y + z * z + w * w;
	}

	inline Vectorf4 & Vectorf4::normalize()
	{
		(*this) /= length();
		return (*this);
	}

	inline void Vectorf4::sqrt()
	{
#ifdef USE_SIMD
		m128 = _mm_sqrt_ps(m128);
#else
		x = sqrtf(x);
		y = sqrtf(y);
		z = sqrtf(z);
		w = sqrtf(w);
#endif
	}

	inline float Vectorf4::dot(Vectorf4& rhs)
	{
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}

	inline float Vectorf4::dot(Vectorf4& lhs, Vectorf4& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	} 