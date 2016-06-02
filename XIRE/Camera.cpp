#include "Camera.h"
#include "Window.h"
#include "Transform.h"

NS_Using(XIRE)
NS_Using(core)

Camera::Camera(void *parentWindow, const core::Vectorf3 &pos,
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

	//LookAt(lookat);

	MarkDirty();

	Update();
}

Camera::~Camera()
{

}

void Camera::setFov(F32 angle)
{
	fov = angle;
	MarkDirty();
}

void Camera::setPosition(const core::Vectorf3& point)
{
	position = point;

	MarkDirty();
}

void Camera::LookAt(const core::Vectorf3& point)
{
	//lookAtDir = point; 
	MarkDirty();
}

void Camera::ResetLookAt()
{
	LookAt(core::Vectorf3(0.f, 0.f, 1.f));
}

//XIRE is based on LH(left hand) coordinate system!

core::Matrixf44 &Camera::getCameraMatrix()
{
	if (isDirty)
	{
		Update();
	}

	return cameraMatrix; 
}

void Camera::Move(const core::Vectorf3& point)
{
	position += (point * quat);

	MarkDirty();
}

void Camera::Rotate(F32 yaw, F32 pitch, F32 roll)
{
	Quaternion rollQ = Quaternion::CreateRotationY(roll);
	Quaternion yawQ = Quaternion::CreateRotationX(yaw);
	Quaternion pitchQ = Quaternion::CreateRotationZ(pitch);

	quat = quat * rollQ;
	quat = yawQ * quat; 
	 
	MarkDirty();
}

void Camera::MarkDirty()
{
	isDirty = true;
}

core::Vectorf3 Camera::getPosition()
{
	return position;
}

void Camera::Update()
{
	if (Parent == NULL)
		return;

	Window* parentWindow = (Window*)Parent;

	F32 aspect = parentWindow->Width/parentWindow->Height; 

	quat.Normalize(); 
	
	cameraMatrix = Transform::CameraMatrixLH(position, position + quat.GetRow2(), up);
 
	projectMatrix = Transform::PerspectiveMatrixLH(aspect, fov, zNear, zFar);

	core::Vectorf3 lookAt = quat.GetRow2();

	lookAt.normalize(); 

	isDirty = false;
}