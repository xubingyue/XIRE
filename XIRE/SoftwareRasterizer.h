#pragma once

#include "XIRE_Afx.h"
#include "Primitive.hpp"
#include "Vertex.hpp"
#include "Vectorf4.h"
#include <vector>
#include <list>

NS_Begin(XIRE)

class SoftwareDriver;
class SwSurface;
class SwRenderPrimitive;

class XIREAPI SoftwareRasterizer
{
public:

	SoftwareRasterizer(U32 bufferWidth, U32 bufferHeight);

	void CreateBuffer(U32 bufferWidth, U32 bufferHeight);

	virtual ~SoftwareRasterizer();
  
	//void DrawPrimitive(SwPrimitive *primitive);

	void Flush(U32 *gpuBuffer, std::vector<SwRenderPrimitive *> primitives);

	void Rasterize();

	void DrawLine();

	void DrawRHZPrimitive(SwPrimitive *primitive); 

protected: 
	

	//SoftwareDriver *driver;

	SwSurface *backbuffer;
};

NS_End(XIRE)