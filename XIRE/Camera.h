#pragma once

#include "XIRE_Afx.h"
#include "EventListener.h"
#include "Vectorf3.hpp"
#include "Matrixf44.h"
#include "Quaternion.h"

NS_Begin(XIRE) 

class XIREAPI Camera: public EventListener
{
public:
	enum CameraMode
	{
		CM_FixedPoint = 0,
		CM_Roam 
	};

public:

	Camera(void *parent,const core::Vectorf3 &pos,
		/*const core::Vectorf3 &lookat = core::Vectorf3(0.f, 0.f, 1.f),*/
		const core::Quaternion &rot,
		const core::Vectorf3 &updir = core::Vectorf3(0.f,1.f,0.f),
		F32 znear = 1.f,
		F32 zfar = 2.f,
		F32 fov = 90.f);

	virtual ~Camera();

	void MarkDirty();

	void Rotate(F32 yaw, F32 pitch, F32 roll); 

	void LookAt(const core::Vectorf3& point);

	void ResetLookAt();

	core::Vectorf3 getPosition();

	void setFov(F32 angle);

	void setPosition(const core::Vectorf3& point);

	void Move(const core::Vectorf3& point);
	
	core::Matrixf44 &getCameraMatrix();

	//void setRotation(const Quaternion& rotation);

	void Update();

protected:

	core::Vectorf3 position;

	//core::Vectorf3 lookAtDir;

	core::Vectorf3 up;

	F32 fov;

	F32 zNear;

	F32 zFar;

	CameraMode cameraMode;

	bool isDirty;
 
	core::Quaternion quat;

	core::Matrixf44 cameraMatrix;

	core::Matrixf44 projectMatrix;
};

NS_End(XIRE)