#pragma once

#include <d3d9.h> 

#include "RenderBase.h" 
#include "Window.h" 
#include "Primitive.hpp" 
#include "SoftwareRasterizer.h"
#include <list>

#pragma comment(lib,"d3d9.lib")

NS_Begin(XIRE)

class VertexBuffer;

class SoftwareDriver : public RenderBase
{
public:
	
	explicit SoftwareDriver(Window* window);

	virtual ~SoftwareDriver();  

	bool BeginFrame() override;

	bool EndFrame() override;

	bool StartupRender();

	bool ShutdownRender();

	bool BuildParameters();

	void Reset() override;

	void DrawPrimitive(SwPrimitive* primitive) override;

	void Present() override;

	void Clear() override;

	void Translate(void *vIn,const core::Vectorf3& pos, F32 scale, void **vOut); 

	void PerspectiveProj(void *vIn,	F32 aspectRadio, F32 fov, F32 znear, F32 zfar, void **vOut);

	void ScreenProj(void *vIn, void **vOut);

protected:

	IDirect3D9 *d3d;

	IDirect3DDevice9 *d3ddev; 

	D3DPRESENT_PARAMETERS pp;

	bool windowed;

	Window *window;

	SoftwareRasterizer *rasterizer;

	IDirect3DSurface9 *backSurface;

	std::list<SwVertexBuffer*> vertexRenderQueue;

private: 

};

NS_End(XIRE)