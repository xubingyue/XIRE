#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
 
//#include "D3D9VertexBuffer.h"

NS_Begin(XIRE)

struct XIREAPI SwPrimitive
{
	SwVertexBuffer *vb;
	SwIndexBuffer *ib;
};

//struct XIREAPI Primitive
//{
//	VertexBuffer *vb;
//
//};

NS_End(XIRE)