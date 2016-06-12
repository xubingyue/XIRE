#pragma once

#include "XIRE_Afx.h"
#include "Callable.h"
#include "Vectorf3.hpp"
#include "Matrixf44.h"
#include "Quaternion.h"
#include "ICamera.hpp"

NS_Begin(XIRE) 

class XIREAPI SwCamera: public ICamera
{
public:

	SwCamera(void *parent,const core::Vectorf3 &pos,
		/*const core::Vectorf3 &lookat = core::Vectorf3(0.f, 0.f, 1.f),*/
		const core::Quaternion &rot,
		const core::Vectorf3 &updir = core::Vectorf3(0.f,1.f,0.f),
		F32 znear = 1.f,
		F32 zfar = 2.f,
		F32 fov = 90.f);

	virtual ~SwCamera();

	void MarkDirty();

	void Rotate(F32 yaw, F32 pitch, F32 roll) override; 

	void LookAt(const core::Vectorf3& point) override;

	void Reset() override;

	core::Vectorf3 getPosition();

	void setFov(F32 angle);

	void setPosition(const core::Vectorf3& point);

	void Move(const core::Vectorf3& point) override;
	
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

	E_CAMERA_MODE cameraMode;

	bool isDirty;
 
	core::Quaternion quat;

	core::Matrixf44 cameraMatrix;

	core::Matrixf44 projectMatrix;
};

NS_End(XIRE)