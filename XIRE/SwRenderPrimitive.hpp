#pragma once

#include "Vectorf4.h" 

NS_Begin(XIRE)

XIRE_ALIGN
struct XIREAPI SwRenderPrimitive
{
	core::Vectorf4 pos;

	// vertex shader
	//core::Vectorf3 normal;
	//core::Vectorf2 texcoord;
};

NS_End(XIRE)