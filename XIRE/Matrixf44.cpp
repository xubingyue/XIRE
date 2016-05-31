#include "Matrixf44.h"
#include "Vectorf4.h"
#include "Transform.h"

NS_Using(XIRE)
NS_Using(XIRE::core)

Matrixf44::Matrixf44()
{
	transposeReady = false;

	MakeIdentity();
}

Matrixf44::Matrixf44(F32 m[4][4])
	:Matrixf44()
{
	this->set(m);
}

Matrixf44 Matrixf44::getTranpose()
{
	if (transposeReady == false)
	{
		for (int j = 0; j < 4; ++j)
			for (int i = 0; i < 4; ++i)
				transpose[i][j] = _matrix[j][i];

		transposeReady = true;
	}

	Matrixf44 matrixInverse(transpose);

	return matrixInverse;
}

Matrixf44 Matrixf44::getInverse()
{
	return getTranpose();
}

void Matrixf44::MakeInverse()
{
	*this = getInverse();
}

void Matrixf44::MakeIdentity()
{ 
	F32 m[4][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}};

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			this->_matrix[i][j] = m[i][j]; 
}

Matrixf44& Matrixf44::operator*(const Matrixf44& matrix)
{
	F32 temp[4][4];

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			temp[i][j] = _matrix[i][0] * matrix._matrix[0][j] + _matrix[i][1] * matrix._matrix[1][j] + _matrix[i][2] * matrix._matrix[2][j] + _matrix[i][4] * matrix._matrix[4][j];

	Matrixf44* matrixNew = new Matrixf44();
	matrixNew->set(temp);

	return *matrixNew;
}

F32 Matrixf44::get(U32 x, U32 y) const
{
	return this->_matrix[x][y];
}

Vectorf4 Matrixf44::getRow(U32 row) const
{
	Vectorf4 vec(_matrix[row][0], _matrix[row][1], _matrix[row][2], _matrix[row][3]);

	return vec;
}

void Matrixf44::set(U32 r, U32 c, F32 v)
{
	if (r >= 0 && r < 4 && c >= 0 && c < 4)
	{
		_matrix[r][c] = v;

		if (transposeReady)
			transposeReady = false;
	}
}

//value copy temporarily
void Matrixf44::set(F32 _d[4][4])
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			_matrix[i][j] = _d[i][j];

	transposeReady = false;
}

Matrixf44& Matrixf44::RotateX(F32 theta)
{
	Matrixf44 matrix = Transform::getMatrixRotationXConst(theta);
	return (*this)*matrix;
}

Matrixf44& Matrixf44::RotateY(F32 theta)
{
	Matrixf44 matrix = Transform::getMatrixRotationYConst(theta);
	return (*this)*matrix;
}

Matrixf44& Matrixf44::RotateZ(F32 theta)
{
	Matrixf44 matrix = Transform::getMatrixRotationZConst(theta);
	return (*this)*matrix;
}

Matrixf44& Matrixf44::Translate(F32 dx, F32 dy, F32 dz)
{
	Matrixf44 matrix = Transform::getMatrixTranslationConst(dx, dy, dz);
	return (*this)*matrix;
}

Matrixf44& Matrixf44::Scale(F32 scaleX, F32 scaleY, F32 scaleZ)
{
	Matrixf44 matrix = Transform::getMatrixScaleConst(scaleX, scaleY, scaleZ);
	return (*this)*matrix;
}
 