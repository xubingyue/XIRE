#include "D3D9Driver.h"

//DirectX 9 Driver implementation
//(c)2016 Sekkit,LLC.

#include "D3D9Driver.h"
#include "SwRenderPrimitive.hpp"
#include "Transform.h"
#include "Camera.h"
#include <math.h>
#include "Window.h"

NS_Using(XIRE)

D3D9Driver::D3D9Driver(Window *_window)
{
	Name = S("D3D9Driver");
	window = _window;

	windowed = !window->IsFullscreen(); 
}

D3D9Driver::~D3D9Driver()
{
	SafeRelease(d3ddev);
	SafeRelease(d3d); 
}

void D3D9Driver::BeginFrame()
{
	if (d3ddev != nullptr)
	{
		d3ddev->Clear(NULL, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0);
		d3ddev->BeginScene();
	}
}

void D3D9Driver::EndFrame()
{
	D3DLOCKED_RECT rect;
	memset(&rect, 0, sizeof(rect));

	HRESULT r = backSurface->LockRect(&rect, NULL, D3DLOCK_DISCARD);

	if (FAILED(r))
	{
		//Error log
		return;
	}

	void *backBuffer = rect.pBits;
	U32 pitch = rect.Pitch;

	std::list<SwVertexBuffer*>::iterator it;
	for (it = vertexRenderQueue.begin(); it != vertexRenderQueue.end(); ++it)
	{
		SwVertexBuffer* buffer = *it;
		std::vector<SwRenderPrimitive *> *outBuffer = nullptr;

		for (U32 i = 0; i < outBuffer->size(); ++i)
		{
			SafeDelete((*outBuffer)[i]);
		}

		(*outBuffer).clear();

		SafeDelete(outBuffer);
	}

	backSurface->UnlockRect();

	if (d3ddev != nullptr)
	{
		d3ddev->EndScene();
	}

	Clear();
}

 
bool D3D9Driver::StartupRender()
{
	if (window == nullptr)
	{
		//Error print
		return false;
	}

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == nullptr)
	{
		//Error print
		return false;
	}

	if (!BuildParameters())
	{
		return false;
	}

	D3DCAPS9 caps;
	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	DWORD vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	/*if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING; 
	}
	else
	{
		vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}*/

	HRESULT r = d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window->GetWindowHandle(),
		vertexProcessing,
		&pp,
		&d3ddev);

	if (FAILED(r))
	{
		d3ddev->Release();
		d3d->Release();
		//
		return false;
	}

	r = d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backSurface);
	if (FAILED(r))
	{
		return false;
	}

	return true;
}

bool D3D9Driver::BuildParameters()
{
	D3DDISPLAYMODE displayMode;
	d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

	ZeroMemory(&pp, sizeof(pp));
	pp.BackBufferWidth = (windowed) ? 0 : displayMode.Width;
	pp.BackBufferHeight = (windowed) ? 0 : displayMode.Height;

	pp.BackBufferFormat = displayMode.Format;
	pp.BackBufferCount = 1;
	pp.MultiSampleType = D3DMULTISAMPLE_NONE; 
	pp.MultiSampleQuality = 0;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.hDeviceWindow = window->GetWindowHandle();
	pp.Windowed = windowed;
	pp.EnableAutoDepthStencil = FALSE;
	pp.FullScreen_RefreshRateInHz = (windowed) ? 0 : displayMode.RefreshRate;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	pp.Flags |= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	return true;
}

bool D3D9Driver::ShutdownRender()
{

	return true;
}

void D3D9Driver::DrawPrimitive(SwPrimitive *primitive)
{
	vertexRenderQueue.push_back(primitive->vb);
}

void D3D9Driver::Reset()
{
	if (d3ddev != nullptr)
	{
		if (BuildParameters())
		{
			d3ddev->Reset(&pp);
		}
	}
}

void D3D9Driver::Present()
{
	if (d3ddev != NULL)
	{
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}
}

void D3D9Driver::Clear()
{
	vertexRenderQueue.clear();
}

