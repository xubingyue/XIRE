#pragma once

#include "XIRE_Afx.h"   
#include "Vectorf3.hpp"

NS_Begin(XIRE)

class SwVertexBuffer;  
 
NS_Begin(core)
class Matrixf44;  
NS_End(core)

class XIREAPI Transform
{
public:

	Transform();

	virtual ~Transform(); 

public:

	static core::Matrixf44& getMatrixRotationXConst(F32 theta);

	static core::Matrixf44& getMatrixRotationYConst(F32 theta);

	static core::Matrixf44& getMatrixRotationZConst(F32 theta);

	static core::Matrixf44& getMatrixTranslationConst(S32 dx, S32 dy, S32 dz);

	static core::Matrixf44& getMatrixScaleConst(F32 sx, F32 sy, F32 sz); 
	
	static core::Matrixf44 MatrixPerspectiveLH(F32 aspectRadio,F32 fov,F32 znear,F32 zfar);
}; 
 
NS_End(XIRE)