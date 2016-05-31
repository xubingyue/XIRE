#include "Camera.h"
#include "Window.h"
#include "Transform.h"

NS_Using(XIRE)

Camera::Camera(void *parent, const core::Vectorf3 &pos,
	const core::Vectorf3 &lookat,
	const core::Vectorf3 &updir,
	F32 znear,
	F32 zfar,
	F32 fov)
{
	setPosition(pos);
	setFov(fov);
	
	up = updir;

	zNear = znear;
	zFar = zfar;

	LookAt(lookat);

	isDirty = true;
}

Camera::~Camera()
{

}

void Camera::setFov(F32 angle)
{
	fov = angle;
}

void Camera::setPosition(const core::Vectorf3& point)
{
	position = point;
}

void Camera::LookAt(const core::Vectorf3& point)
{
	lookAtDir = point; 
}

void Camera::ResetLookAt()
{
	LookAt(core::Vectorf3(0.f, 0.f, 1.f));
}

//XIRE is based on LH(left hand) coordinate system!

core::Matrixf44 &Camera::getCameraMatrix()
{
	/*
	欧拉相机 Matrix translation&rotation to form a Camera View matrix(这个方法不太好)

	core::Matrixf44 m0 = Transform::getMatrixTranslationConst(-position.x, -position.y, -position.z);
	core::Matrixf44 m1 = Transform::getMatrixRotationXConst(-PI * 90.f/180);
	core::Matrixf44 m2 = Transform::getMatrixRotationYConst(0.f);
	core::Matrixf44 m3 = Transform::getMatrixRotationZConst(0.f);

	return m0*m1*m2*m3;
	*/

	//from to     up
	//pos  lookat up

	//UVN相机
	//http://blog.csdn.net/chenfeiyang2009/article/details/7212091
	//左手坐标系用左手法则判定方向，坑啊，书上没说

	core::Vectorf3 N = (lookAtDir - position).normalize();
	core::Vectorf3 U = (up.CrossProduct(N)).normalize();
	core::Vectorf3 V = (N.CrossProduct(U)).normalize();

	core::Vectorf3 offset(position.dot(U),position.dot(V),position.dot(N));

	core::Matrixf44 matrix;
	matrix.MakeIdentity();

	matrix._matrix[0][0] = U.x;			matrix._matrix[0][1] = V.x;			matrix._matrix[0][2] = N.x;
	matrix._matrix[1][0] = U.y;			matrix._matrix[1][1] = V.y;			matrix._matrix[1][2] = N.y;
	matrix._matrix[2][0] = U.z;			matrix._matrix[2][1] = V.z;			matrix._matrix[2][2] = N.z;
	matrix._matrix[3][0] = -offset.x;	matrix._matrix[3][1] = -offset.y;	matrix._matrix[3][2] = -offset.z;
	//matrix.Print();
	matrix.MakeInverse();
	//matrix.Print();
	return matrix;
}

void Camera::Move(const core::Vectorf3& point)
{

}

void Camera::Rotate(F32 yaw, F32 pitch, F32 roll)
{

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
	Window* parentWindow = (Window*)parent;

	F32 aspect = parentWindow->Width/parentWindow->Height; 
}