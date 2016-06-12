#include "SwCamera.h"
#include "Window.h"
#include "Transform.h"

NS_Using(XIRE)
NS_Using(core)

SwCamera::SwCamera(void *parentWindow, const core::Vectorf3 &pos,
	/*const core::Vectorf3 &lookat,*/
	const core::Quaternion &rot,
	const core::Vectorf3 &updir,
	F32 znear,
	F32 zfar,
	F32 fov)  
{	 
	Parent = parentWindow;

	setPosition(pos);
	setFov(fov);
	
	up = updir;

	quat = rot;

	zNear = znear;
	zFar = zfar;
 
	MarkDirty();

	Update();
}

SwCamera::~SwCamera()
{

}

void SwCamera::setFov(F32 angle)
{
	fov = angle;
	MarkDirty();
}

void SwCamera::setPosition(const core::Vectorf3& point)
{
	position = point;

	MarkDirty();
}

void SwCamera::LookAt(const core::Vectorf3& point)
{
	//lookAtDir = point; 
	MarkDirty();
}

void SwCamera::Reset()
{
	LookAt(core::Vectorf3(0.f, 0.f, 1.f));
}

//XIRE is based on LH(left hand) coordinate system!

core::Matrixf44 &SwCamera::getCameraMatrix()
{
	if (isDirty)
	{
		Update();
	}

	return cameraMatrix;
}

void SwCamera::Move(const core::Vectorf3& point)
{
	position += (point * quat);

	MarkDirty();
}

void SwCamera::Rotate(F32 yaw, F32 pitch, F32 roll)
{
	Quaternion qRoll  = Quaternion::CreateRotationY(roll);
	Quaternion qYaw   = Quaternion::CreateRotationX(yaw);
	Quaternion qPitch = Quaternion::CreateRotationZ(pitch);
	 
	quat = qRoll * quat * qRoll.GetInverted();
	//quat = qYaw * quat;
	 
	MarkDirty();
}

void SwCamera::MarkDirty()
{
	isDirty = true;
}

core::Vectorf3 SwCamera::getPosition()
{
	return position;
}

void SwCamera::Update()
{
	if (Parent == nullptr)
		return;

	Window* parentWindow = (Window*)Parent;

	F32 aspect = parentWindow->Width * 0.f/parentWindow->Height; 

	//quat.Normalize();
	
	cameraMatrix = Transform::CameraMatrixLH(position, position + quat.GetRow2(), up);

	projectMatrix = Transform::PerspectiveMatrixLH(aspect, fov, zNear, zFar);
 
	isDirty = false;
}