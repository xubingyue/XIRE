#include "D3D9Driver.h"

//DirectX 9 Driver implementation
//(c)2016 Sekkit,LLC.

#include "D3D9Driver.h"
#include "SwRenderPrimitive.hpp"
#include "Transform.h"
#include "D3D9Camera.h"
#include "SwCamera.h"
#include <math.h>
#include "Window.h"

NS_Using(XIRE)

D3D9Driver::D3D9Driver(Window *_window)
{
	Name = S("D3D9Driver");
	window_ = _window;
}

D3D9Driver::~D3D9Driver()
{
	ShutdownRender();
}

bool D3D9Driver::BeginFrame()
{ 
	if (d3ddev_ != nullptr)
	{
		d3ddev_->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);

		auto viewMat = window_->getCamera()->ViewMatrix;


		d3ddev_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		d3ddev_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		d3ddev_->SetRenderState(D3DRS_LIGHTING, FALSE);
		d3ddev_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		/*D3DXMATRIX proj, view;

		D3DXMatrixPerspectiveFovLH(&proj, 90.0f, (FLOAT)window_->Width / window_->Height, 0.1f, 1000.0f);
		d3ddev_->SetTransform(D3DTS_PROJECTION, &proj);

		D3DXVECTOR3 cameraPos(0.0f, 0.0f, -1.0f);
		D3DXVECTOR3 lookAtPos(0.0f, 0.0f, 1.0f);
		D3DXVECTOR3 upDir(0.0f, 1.0f, 0.0f);

		D3DXMatrixLookAtLH(&view, &cameraPos, &lookAtPos, &upDir);
		*/


		//d3ddev_->SetTransform(D3DTS_VIEW, &viewMat);
		 
		HRESULT hr = SUCCEEDED(d3ddev_->BeginScene());

		//d3ddev_->SetTransform(D3DTS_VIEW, &viewMat);

		//d3ddev_->SetTransform(D3DTS_VIEW, &viewMat);

		D3DXMATRIX proj;
		D3DXMatrixPerspectiveFovLH(
			&proj,                        // result
			D3DX_PI * 0.5f,               // 90 - degrees
			(FLOAT)window_->Width / window_->Height, // aspect ratio
			1.0f,                         // near plane
			1000.0f);                     // far plane

		d3ddev_->SetTransform(D3DTS_PROJECTION, &proj);

		//
		// Set wireframe mode render state.
		//

		D3DXMATRIX matProj;
		D3DXMATRIX matView;

		// Create and set the projection matrix
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 2.0f, (FLOAT)window_->Width / window_->Height, 1.0f, 10000.0f);
		d3ddev_->SetTransform(D3DTS_PROJECTION, &matProj);

		// Create and set the view matrix
		D3DXMatrixLookAtLH(&matView,  
			&D3DXVECTOR3(0.0f, 0.0f, -1.0f),  
			&D3DXVECTOR3(0.0f, 0.0f, 0.0f),  
			&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		d3ddev_->SetTransform(D3DTS_VIEW, &matView);

		d3ddev_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		return SUCCEEDED(hr);
	}

	return false;
}

IDirect3DVertexBuffer9 *tempBuffer;

bool D3D9Driver::EndFrame()
{
	/*D3DLOCKED_RECT rect;
	memset(&rect, 0, sizeof(rect));*/

	//HRESULT r = backSurface_->LockRect(&rect, NULL, D3DLOCK_DISCARD);

	//if (FAILED(r))
	//{
	//	//Error log
	//	return false;
	//}

	/*void *backBuffer = rect.pBits;
	U32 pitch = rect.Pitch;*/

	//std::list<VertexBuffer*>::iterator it;
	//for (it = vertexRenderQueue.begin(); it != vertexRenderQueue.end(); ++it)
	//{
	//	VertexBuffer* buffer = *it;
	//	std::vector<SwRenderPrimitive *> *outBuffer = nullptr;
	 
	std::list<SwVertexBuffer*>::iterator it;
	for (it = vertexRenderQueue_.begin(); it != vertexRenderQueue_.end(); ++it)
	{ 
		SwVertexBuffer *buf = *it; 
 
		if (tempBuffer == NULL)
		{
			d3ddev_->CreateVertexBuffer(buf->count*buf->size, 0, XIRE_VERTEX_FVF2, D3DPOOL_DEFAULT, &tempBuffer, 0);
		}

		//std::vector<XireVertex2> vec;

		//for (int i = 0; i < buf->count; ++i)
		//{
		//	SwVertexP3N3T2 *data = (SwVertexP3N3T2 *)(buf->data + i*buf->size);

		//	//tranform Model Space into World Space
		//	core::Vectorf3 normal = data->normal;
		//	core::Vectorf4 pos = data->pos;
		//	core::Vectorf2 tex = data->texcoord;
 
		//	core::Matrixf44 Tmatrix = Transform::getMatrixTranslationConst(pos.x, pos.y, pos.z); //Model to World Space Translation matrix
		//	//core::Matrixf44 Cmatrix = cam->getCameraMatrix();                                    //World to Camera Space Translation&Rotation matrix
		//	//core::Matrixf44 Smatrix = Transform::getMatrixScaleConst(scale, scale, scale);       //Model to World Space Rotation matrix

		//	core::Vectorf4 worldpos = pos * Tmatrix;// *Smatrix * Cmatrix;

		//	/*SwRenderPrimitive *vertex = new SwRenderPrimitive();
		//	vertex->pos = worldpos;
		//	renderList->push_back(vertex); 
		//	*/
		//	//printf("%d %.4f %.4f %.4f %.4f\n", sizeof(SwVertexP3N3T2), pos.x, pos.y, pos.z, pos.w);
		//	//translate every vertex into world space  
		//	worldpos.normalize();

		//	//XireVertex2 v;
		//	//v.x = worldpos.x; v.y = worldpos.y; v.z = worldpos.z; v.rhw = worldpos.w;

		//	//v.color = D3DXCOLOR(255, 255, 255, 255);
 
		//	//vec.push_back(v);
		//} 

		XireVertex2 *p;
		tempBuffer->Lock(NULL, NULL, (void**)&p, NULL);
		//auto ppp = vec.data();
		//memcpy(p, vec.data(), sizeof(XireVertex2)*vec.size());

		for (int i = 0; i < buf->count; ++i)
		{
			SwVertexP3N3T2 *data = (SwVertexP3N3T2 *)(buf->data + i*buf->size);

			//tranform Model Space into World Space
			core::Vectorf3 normal = data->normal;
			core::Vectorf4 pos = data->pos;
			core::Vectorf2 tex = data->texcoord;
 
			core::Vectorf4 worldpos = pos;

			p[i] = XireVertex2(pos.x , pos.y , pos.z );
		}

		tempBuffer->Unlock();
		 

		/*d3ddev_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		d3ddev_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		d3ddev_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);*/
		
		d3ddev_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		d3ddev_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		// Set default rendering states.
		d3ddev_->SetRenderState(D3DRS_LIGHTING, FALSE);
		d3ddev_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		d3ddev_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		d3ddev_->SetStreamSource(0, tempBuffer, 0, sizeof(XireVertex2));
		d3ddev_->SetFVF(XIRE_VERTEX_FVF2);
		d3ddev_->DrawPrimitive(D3DPT_POINTLIST, 0, buf->count);

		IDirect3DVertexBuffer9 *tr;

		d3ddev_->CreateVertexBuffer(
			3 * sizeof(XireVertex), // size in bytes
			D3DUSAGE_WRITEONLY, // flags
			XIRE_VERTEX_FVF,        // vertex format
			D3DPOOL_MANAGED,    // managed memory pool
			&tr,          // return create vertex buffer
			0);                 // not used - set to 0
		 

		XireVertex* vertices;
		tr->Lock(0, 0, (void**)&vertices, 0);

		vertices[0] = XireVertex(0.0f, 0.0f, 2.0f,0.f);
		vertices[1] = XireVertex(0.0f, 1.0f, 2.0f,0.f);
		vertices[2] = XireVertex(1.0f, 0.0f, 2.0f,0.f);

		tr->Unlock();

		d3ddev_->SetStreamSource(0, tr, 0, sizeof(XireVertex));
		d3ddev_->SetFVF(XIRE_VERTEX_FVF);
		d3ddev_->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	}

	//backSurface_->UnlockRect();
 
	bool success = SUCCEEDED(d3ddev_->EndScene()); 

	Clear();

	return success;
}

 
bool D3D9Driver::StartupRender()
{
	if (window_ == nullptr)
	{
		//Error print
		return false;
	}

	d3d_ = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d_ == nullptr)
	{
		//Error print
		return false;
	}

	if (!BuildParameters())
	{
		return false;
	}

	D3DCAPS9 caps;
	d3d_->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	DWORD vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	/*if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING; 
	}
	else
	{
		vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}*/

	HRESULT r = d3d_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_->GetWindowHandle(),
		vertexProcessing,
		&pp_,
		&d3ddev_);

	if (FAILED(r))
	{
		ShutdownRender();
		return false;
	}

	r = d3ddev_->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backSurface_);
	if (FAILED(r))
	{
		ShutdownRender();
		return false;
	}

	return true;
}

bool D3D9Driver::BuildParameters()
{
	D3DDISPLAYMODE displayMode;
	d3d_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

	ZeroMemory(&pp_, sizeof(pp_));
	pp_.BackBufferWidth = window_->IsFullscreen() ? displayMode.Width : 0;
	pp_.BackBufferHeight = window_->IsFullscreen() ?  displayMode.Height : 0;

	pp_.BackBufferFormat = displayMode.Format;
	pp_.BackBufferCount = 1;
	pp_.MultiSampleType = D3DMULTISAMPLE_NONE;
	pp_.MultiSampleQuality = 0;
	pp_.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp_.hDeviceWindow = window_->GetWindowHandle();
	pp_.Windowed = !window_->IsFullscreen();
	pp_.EnableAutoDepthStencil = false;
	pp_.FullScreen_RefreshRateInHz = window_->IsFullscreen() ? displayMode.RefreshRate : 0;
	pp_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	pp_.Flags |= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	return true;
}

bool D3D9Driver::ShutdownRender()
{
	SafeRelease(d3d_);
	SafeRelease(d3ddev_);

	return true;
}

void D3D9Driver::DrawPrimitive(SwPrimitive *primitive)
{
	vertexRenderQueue_.push_back(primitive->vb);
}

void D3D9Driver::Reset()
{
	if (d3ddev_ != nullptr)
	{
		HRESULT hr = d3ddev_->TestCooperativeLevel();

		if (FAILED(hr))
		{
			if (BuildParameters())
			{
				d3ddev_->Reset(&pp_);
			}
		}
	}
}

void D3D9Driver::Present()
{
	if (d3ddev_ != NULL)
	{
		d3ddev_->Present(NULL, NULL, NULL, NULL);
	}
}

void D3D9Driver::Clear()
{
	vertexRenderQueue_.clear();
}

