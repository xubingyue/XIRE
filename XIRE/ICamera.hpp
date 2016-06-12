#pragma once

#include "Root.h"

NS_Begin(XIRE)

NS_Begin(core)
class Vectorf3;
NS_End(core)

enum E_CAMERA_MODE
{
	CM_FixedPoint = 0,
	CM_Roam
};

class ICamera : public Root 
{
public:

	virtual void Rotate( F32 yaw, F32 pitch, F32 roll ) = 0;

	virtual void LookAt( const core::Vectorf3& point ) = 0;

	virtual void Reset() = 0;
	 
	virtual void setFov( F32 angle ) = 0;
	 
	virtual void Move( const core::Vectorf3& point ) = 0; 

public:

	
};

NS_End(XIRE)