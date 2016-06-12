#pragma once

#include "RenderBase.h"
#include <d3d9.h>
#include <list>
#include "D3D9VertexBuffer.h"
#include "VertexBuffer.hpp"

#pragma comment(lib,"d3d9.lib") 

NS_Begin(XIRE) 

class Window;

class XIREAPI D3D9Driver : public RenderBase
{
public:

	D3D9Driver(Window *_window);

	~D3D9Driver();

	bool BeginFrame() override;

	bool EndFrame() override;

	bool StartupRender();

	bool ShutdownRender();

	bool BuildParameters();

	void Reset() override;

	void DrawPrimitive(SwPrimitive* primitive) override;

	void Present() override;

	void Clear() override;

protected:

	IDirect3D9 *d3d_;

	IDirect3DDevice9 *d3ddev_;

	D3DPRESENT_PARAMETERS pp_;
 
	Window *window_;
	 
	IDirect3DSurface9 *backSurface_;

	std::list<SwVertexBuffer*> vertexRenderQueue_;
};

NS_End(XIRE)

