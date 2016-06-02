#include "SoftwareRasterizer.h"
#include "SoftwareDriver.h"
#include "SwSurface.h"
#include "Vectorf4.h"
#include "SoftShader.h"
#include "Vectorf3.hpp"
#include "SwRenderPrimitive.hpp"
#include "Transform.h"

NS_Using(XIRE)

SoftwareRasterizer::SoftwareRasterizer(U32 bufferWidth,U32 bufferHeight)
{ 
	CreateBuffer(bufferWidth, bufferHeight); 
}

SoftwareRasterizer::~SoftwareRasterizer()
{
	SafeDelete(backbuffer);
}

void SoftwareRasterizer::CreateBuffer(U32 bufferWidth, U32 bufferHeight)
{
	backbuffer = new SwSurface(S("Backbuffer"), bufferWidth, bufferHeight, 4);
}   
 
template<typename T>
static inline T Clamp(const T& p, const T& min, const T& max) { if (p < min) return min; if (p > max) return max; return p; }

static inline core::Vectorf4 Clamp(const core::Vectorf4& p, float min, float max)
{

#ifdef USE_SIMD
	core::Vectorf4 ret;
	__m128 max128 = _mm_set_ps1(max);
	__m128 min128 = _mm_set_ps1(min);
	ret.m128 = _mm_locut_ps(_mm_hicut_ps(p.m128, max128), min128);
#else
	core::Vectorf4 ret = p;
	ret.x = Clamp(ret.x, min, max);
	ret.y = Clamp(ret.y, min, max);
	ret.z = Clamp(ret.z, min, max);
	ret.w = Clamp(ret.w, min, max);
#endif
	return ret;
}

static inline U32 float4_2_uint32(const core::Vectorf4& f)
{
#ifdef USE_SIMD
	__m128 fMul = _mm_set_ps1(255.f);
	__m128 m128 = _mm_mul_ps(f.m128, fMul);
	__m128i dword128 = _mm_cvtps_epi32(m128);
	U32* dword4 = (U32*)(&dword128);

#ifdef SR_COLOR_RGBA
	U32 ret = (dword4[0] << 16)
		| (dword4[1] << 8)
		| (dword4[2] << 0)
		| (dword4[3] << 24);
#else
	U32 ret = (dword4[0] << 24)
		| (dword4[1] << 16)
		| (dword4[2] << 8)
		| (dword4[3]);
#endif
	return ret;

#else

#ifdef SR_COLOR_RGBA
	U32 ret = (((U8)(f.x * 0xFF)) << 16)
		| (((U8)(f.y * 0xFF)) << 8)
		| (((U8)(f.z * 0xFF)) << 0)
		| ((U8)(f.w * 0xFF) << 24);
#else
	U32 ret = (((U8)(f.x * 0xFF)) << 24)
		| (((U8)(f.y * 0xFF)) << 16)
		| (((U8)(f.z * 0xFF)) << 8)
		| ((U8)(f.w * 0xFF));
#endif
	return ret;
#endif
}

bool flag[XIRE_DEFAULT_WND_W * 2][XIRE_DEFAULT_WND_H * 2] = { 0 };

//Rasterization goes here
void SoftwareRasterizer::Flush(U32 *gpuBuffer, std::vector<SwRenderPrimitive *> buffer)
{  
	U32 width = backbuffer->getWidth();
	U32 height = backbuffer->getHeight();

	//Camera coordinates to screen pixels
	F32 aspectRatio = width*1.f/ height;
	F32 h = 2 * 1.f / tanf(90.f*0.5);
	F32 w = h * aspectRatio;

	std::vector<core::Vectorf2> pts;
	 
	memset(flag,0,sizeof(bool)*XIRE_DEFAULT_WND_W*XIRE_DEFAULT_WND_H*4);

	for (int i = 0; i < buffer.size(); ++i)
	{
		buffer[i]->pos /= buffer[i]->pos.z;
 
		U32 px = (buffer[i]->pos.x+1) * width / w;
		U32 py = (buffer[i]->pos.y+1) * height / h;

		if (px >= 0 && px < width &&py >= 0 && py < height)
		{
			flag[py][px] = true;
		}
	} 

	int cnt = 0; 
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{  
			core::Vectorf4 clr(255, 0, 0, 0);

			if (flag[i][j] == true)
			{
				clr.a = 255;
				clr.r = 255;
				clr.g = 255;
				clr.b = 255;
			} 

			core::Vectorf4 clampedClr = Clamp(clr, 0.f, 1.f);

			clampedClr.sqrt();

			*(gpuBuffer + cnt++) = float4_2_uint32(clampedClr); 
		}
	} 
} 

void SoftwareRasterizer::Rasterize()
{

}

void SoftwareRasterizer::DrawLine()
{

}

void SoftwareRasterizer::DrawRHZPrimitive(SwPrimitive *primitive)
{

}
