#pragma once

#include "Vectorf4.h" 

NS_Begin(XIRE)

XIRE_ALIGN
struct XIREAPI SwVertexP3N3T2
{
	core::Vectorf4 pos;
 
	core::Vectorf3 normal;
	core::Vectorf2 texcoord;
};

NS_End(XIRE)