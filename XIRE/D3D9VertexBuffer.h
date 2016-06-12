#pragma once

#include "GpuObject.h"

NS_Begin(XIRE)

#define XIRE_VERTEX_FVF		(D3DFVF_XYZRHW)
//#define XIRE_VERTEX_FVF2	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define XIRE_VERTEX_FVF2	(D3DFVF_XYZ)
//|D3DFVF_DIFFUSE)

struct XIREAPI XireVertex {
	float x, y, z , w;  

	XireVertex(float _x, float _y, float _z, float _w)
	{
		x = _x; y = _y; z = _z; w = _w;
	}
};

struct XIREAPI XireVertex2 {
	float x, y, z;// , rhw;

	XireVertex2(float _x, float _y, float _z)//,float _w)
	{
		x = _x; y = _y; z = _z; //rhw = _w;
	}

	//DWORD color;
	//float u, v; 
};

class D3D9VertexBuffer
{
public:

	D3D9VertexBuffer();

	virtual ~D3D9VertexBuffer();


};

NS_End(XIRE)

