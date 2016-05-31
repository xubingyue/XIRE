#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

NS_Begin(XIRE)

struct XIREAPI SwPrimitive
{
	SwVertexBuffer *vb;
	SwIndexBuffer *ib;
};

NS_End(XIRE)