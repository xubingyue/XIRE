#pragma once

#include "Matrixf44.h"

#include "Vertex.hpp"
#include "VertexBuffer.hpp"
#include "Vectorf3.hpp"

NS_Begin(XIRE)

XIRE_ALIGN
class XIREAPI SoftShader
{
public:

	SoftShader();

	virtual ~SoftShader();
 
	static void ProcessPixel();

protected: 
	
}; 

NS_End(XIRE)