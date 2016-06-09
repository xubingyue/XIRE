#pragma once

#include "RenderBase.h"
#include <d3d9.h>
#include <list>

#pragma comment(lib,"d3d9.lib")

NS_Begin(XIRE)

class SwVertexBuffer;

class Window;

class D3D9Driver : public RenderBase
{
public:

	D3D9Driver(Window *_window);

	~D3D9Driver();

	void BeginFrame() override;

	void EndFrame() override;

	bool StartupRender();

	bool ShutdownRender();

	bool BuildParameters();

	void Reset() override;

	void DrawPrimitive(SwPrimitive* primitive) override;

	void Present() override;

	void Clear() override;

protected:

	IDirect3D9 *d3d;

	IDirect3DDevice9 *d3ddev;

	D3DPRESENT_PARAMETERS pp;

	bool windowed;

	Window *window;
	 
	IDirect3DSurface9 *backSurface;

	std::list<SwVertexBuffer*> vertexRenderQueue;
};

NS_End(XIRE)

