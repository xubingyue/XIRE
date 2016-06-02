//SwDriver implementation
//(c)2016 Sekkit,LLC.

#include "SoftwareDriver.h"
#include "SwRenderPrimitive.hpp"
#include "Transform.h"
#include "Camera.h"
#include <math.h>

NS_Using(XIRE)

SoftwareDriver::SoftwareDriver(Window *_window) 
{
	Name = S("SoftwareDriver");
	window = _window;

	windowed = !window->IsFullscreen();

	rasterizer = new SoftwareRasterizer(window->Width,window->Height);
}

SoftwareDriver::~SoftwareDriver()
{
	SafeRelease(d3ddev);
	SafeRelease(d3d); 
	SafeDelete(rasterizer); 
}

void SoftwareDriver::BeginFrame()
{
	/*
	if (d3ddev != nullptr)
	{ 
		d3ddev->Clear(NULL, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0);
		d3ddev->BeginScene();
	}
	*/
}

void SoftwareDriver::EndFrame() 
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
	for (it = vertexRenderQueue.begin();it != vertexRenderQueue.end(); ++it)
	{
		SwVertexBuffer* buffer = *it;
		std::vector<SwRenderPrimitive *> *outBuffer = nullptr;

		//Rendering PIPE goes here
		//这里有一个巨大的坑，包含hpp文件后不能有相关前置声明！否则编译不过。。。卡了半小时 
		Translate(buffer, core::Vectorf3(0.f, 0.f, 1.f), 1.f, (void**)&outBuffer);
		 
		PerspectiveProj(outBuffer, (double)window->Width / window->Height, 90.f, 1.f, 1000.f, (void**)&outBuffer);

		//ScreenProj(outBuffer, (void**)&outBuffer);

		rasterizer->Flush((U32*)backBuffer, *outBuffer);

		for (U32 i = 0; i < outBuffer->size(); ++i)
		{
			SafeDelete((*outBuffer)[i]);
		}
		
		(*outBuffer).clear();

		SafeDelete(outBuffer);  
	}

	backSurface->UnlockRect();
	 
	Clear();
} 

void SoftwareDriver::Translate(
	void *vIn,
	const core::Vectorf3& pos,
	F32 scale,
	void **vOut)
{
	SwVertexBuffer *vertex = (SwVertexBuffer*)vIn;

	//U8 *renderVBuffer = (U8*)MemoryPool::Get()._mm_malloc_16byte(sizeof(SwRenderPrimitive)*vertex->count, 16);

	std::vector<SwRenderPrimitive *> *renderList = new std::vector<SwRenderPrimitive*>();
	Camera *cam = this->window->getCamera();

	for (int i = 0; i < vertex->count; ++i)
	{ 
		//transform Model Space into World Space
		SwVertexP3N3T2 *data = (SwVertexP3N3T2 *)(vertex->data + i*vertex->size);

		core::Vectorf3 normal = data->normal;
		core::Vectorf4 pos = data->pos;
		core::Vectorf2 tex = data->texcoord;
		  
		core::Matrixf44 Tmatrix = Transform::getMatrixTranslationConst(pos.x, pos.y, pos.z); //Model to World Space Translation matrix
 		core::Matrixf44 Cmatrix = cam->getCameraMatrix();                                    //World to Camera Space Translation&Rotation matrix
		core::Matrixf44 Smatrix = Transform::getMatrixScaleConst(scale, scale, scale);       //Model to World Space Rotation matrix
		 
		core::Vectorf4 worldpos = pos * Tmatrix * Smatrix * Cmatrix;

		SwRenderPrimitive *vertex = new SwRenderPrimitive();
		vertex->pos = worldpos;
		renderList->push_back(vertex);

		//memcpy(renderVBuffer + i * sizeof(SwRenderPrimitive), &vertex, sizeof(SwRenderPrimitive));
	}

	//memcpy(renderVBuffer, renderList.data(), sizeof(SwRenderPrimitive)*renderList.size());
	
	*vOut = renderList;
}

void SoftwareDriver::PerspectiveProj(
	void *vIn, 
	F32 aspectRadio,
	F32 fov,
	F32 znear,
	F32 zfar, 
	void **vOut)
{
	core::Matrixf44 matrix = Transform::PerspectiveMatrixLH(aspectRadio, fov, znear, zfar);

	std::vector<SwRenderPrimitive*> vec = *(std::vector<SwRenderPrimitive*>*)vIn;
	 
	for (U32 i=0;i<vec.size();++i)
	{   
		SwRenderPrimitive* data = vec[i];
		 
		data->pos = data->pos * matrix;
		data->pos /= data->pos.w;  
	}

	*vOut = vIn;
}

void SoftwareDriver::ScreenProj(void *vIn, void **vOut)
{  
	F32 data[4][4] = {1,0,0,0,0,-1,0,0,0,0,1,0,1,1,0,1};
	core::Matrixf44 matrix(data);

	std::vector<SwRenderPrimitive*> vec = *(std::vector<SwRenderPrimitive*>*)vIn;

	for (U32 i = 0; i < vec.size(); ++i)
	{
		SwRenderPrimitive* data = vec[i];

		data->pos = data->pos * matrix;
		data->pos /= data->pos.w;
	}

	*vOut = vIn;
}

bool SoftwareDriver::StartupRender()
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

	DWORD vertexProcessing = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		/*if (caps.DevCaps & D3DDEVCAPS_PUREDEVICE)
		{
			vertexProcessing |= D3DCREATE_PUREDEVICE;
		}*/
	}
	else
	{
		vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

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

bool SoftwareDriver::BuildParameters()
{
	D3DDISPLAYMODE displayMode;
	d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode); 

	ZeroMemory(&pp, sizeof(pp));
	pp.BackBufferWidth = (windowed) ? 0 : displayMode.Width;
	pp.BackBufferHeight = (windowed) ? 0 : displayMode.Height;

	pp.BackBufferFormat = displayMode.Format; 
	pp.BackBufferCount = 1;
	pp.MultiSampleType = D3DMULTISAMPLE_NONE;//D3DMULTISAMPLE_4_SAMPLES;
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

bool SoftwareDriver::ShutdownRender() 
{

	return true;
}

void SoftwareDriver::DrawPrimitive(SwPrimitive *primitive)
{ 
	vertexRenderQueue.push_back(primitive->vb); 
} 

void SoftwareDriver::Reset()
{
	if (d3ddev != nullptr)
	{
		if (BuildParameters())
		{
			d3ddev->Reset(&pp);
		}
	}
}

void SoftwareDriver::Present()
{
	if (d3ddev != NULL)
	{
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}
}

void SoftwareDriver::Clear()
{
	vertexRenderQueue.clear();
}

