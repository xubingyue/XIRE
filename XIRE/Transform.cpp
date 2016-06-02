#include "Transform.h" 

#include "Matrixf44.h"
#include "VertexBuffer.hpp"
#include "SwRenderPrimitive.hpp" 
#include "MemoryPool.h"
#include "Vertex.hpp"
#include "Vectorf4.h"
#include <string.h>
#include <stdio.h>

NS_Using(XIRE) 

Transform::Transform()
{

}

Transform::~Transform()
{

}

core::Matrixf44& Transform::getMatrixRotationXConst(F32 theta)
{
	F32 temp[4][4] = {
		1.f, 0.f,          0.f,         0.f,
		0.f, cosf(theta),  sinf(theta), 0.f,
		0.f, -sinf(theta), cosf(theta), 0.f,
		0.f, 0.f,          0.f,         1.f
	};

	core::Matrixf44 matrix(temp);
	return matrix;
}

core::Matrixf44& Transform::getMatrixRotationYConst(F32 theta)
{
	F32 temp[4][4] = {
		cosf(theta), 0.f, -sinf(theta), 0.f,
		0.f,         1.f, 0.f,          0.f,
		sinf(theta), 0.f, cosf(theta),  0.f,
		0.f,         0.f, 0.f,          1.f
	};

	core::Matrixf44 matrix(temp);
	return matrix;
}

core::Matrixf44& Transform::getMatrixRotationZConst(F32 theta)
{
	F32 temp[4][4] = {
		cosf(theta),  sinf(theta), 0.f, 0.f,
		-sinf(theta), cosf(theta), 0.f, 0.f,
		0.f,          0.f,         1.f, 0.f,
		0.f,          0.f,         0.f, 1.f
	};

	core::Matrixf44 matrix(temp);
	return matrix;
}

core::Matrixf44& Transform::getMatrixTranslationConst(S32 dx, S32 dy, S32 dz)
{
	F32 temp[4][4] = {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		dx,  dy,  dz,  1.f
	};

	core::Matrixf44 matrix(temp);
	return matrix;
}

core::Matrixf44& Transform::getMatrixScaleConst(F32 sx, F32 sy, F32 sz)
{
	F32 temp[4][4] = {
		sx,  0.f, 0.f, 0.f,
		0.f, sy,  0.f, 0.f,
		0.f, 0.f, sz,  0.f,
		0.f, 0.f, 0.f, 1.f
	};

	core::Matrixf44 matrix(temp);
	return matrix;
}


core::Matrixf44 Transform::PerspectiveMatrixLH(
	F32 aspectRadio,
	F32 fov,
	F32 znear,
	F32 zfar)
{
	//FOV按yz平面来计算
	F32 h = 2 * znear / tanf(fov*0.5);
	F32 w = h*aspectRadio;

	F32 top, bottom, left, right;

	right = w / 2;
	left = -right;
	top = h / 2;
	bottom = -top;


	F32 a = -(zfar + znear) / (zfar - znear);
	F32 b = -2.f*zfar*znear / (zfar - znear);

	core::Matrixf44 matrix;
	matrix._matrix[0][0] = 2 * znear / (right - left);	matrix._matrix[0][1] = 0.f;						matrix._matrix[0][2] = (right + left) / (right - left);		matrix._matrix[0][3] = 0.f;
	matrix._matrix[1][0] = 0.f;							matrix._matrix[1][1] = 2 * znear / (top - bottom);	matrix._matrix[1][2] = (top + bottom) / (top - bottom); matrix._matrix[1][3] = 0.f;
	matrix._matrix[2][0] = 0.f;							matrix._matrix[2][1] = 0.f;						matrix._matrix[2][2] = a;								matrix._matrix[2][3] = b;
	matrix._matrix[3][0] = 0.f;							matrix._matrix[3][1] = 0.f;						matrix._matrix[3][2] = -1.f;							matrix._matrix[3][3] = 0.f;

	return matrix;
}

core::Matrixf44 Transform::CameraMatrixLH(core::Vectorf3 &from, core::Vectorf3 &to, core::Vectorf3 &up)
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

	core::Vectorf3 N = (to - from).normalize();
	core::Vectorf3 U = (up.CrossProduct(N)).normalize();
	core::Vectorf3 V = (N.CrossProduct(U)).normalize();

	core::Vectorf3 offset(from.dot(U), from.dot(V), from.dot(N));

	core::Matrixf44 matrix;
	matrix.MakeIdentity();

	matrix._matrix[0][0] = U.x;			matrix._matrix[0][1] = V.x;			matrix._matrix[0][2] = N.x;
	matrix._matrix[1][0] = U.y;			matrix._matrix[1][1] = V.y;			matrix._matrix[1][2] = N.y;
	matrix._matrix[2][0] = U.z;			matrix._matrix[2][1] = V.z;			matrix._matrix[2][2] = N.z;
	matrix._matrix[3][0] = -offset.x;	matrix._matrix[3][1] = -offset.y;	matrix._matrix[3][2] = -offset.z;
	//matrix.Print();
	matrix.MakeInverse();

	return matrix;
}

