#pragma once

//this is not a generic Matrix implementation BUT for 3d transformation only!

#include "XIRE_Afx.h" 

NS_Begin(XIRE)
NS_Begin(core)

class Vectorf4;

class XIREAPI Matrixf44
{
public:

	Matrixf44();

	Matrixf44(F32 m[4][4]);

	Matrixf44 getTranpose();

	Matrixf44& operator*(const Matrixf44& matrix);

	inline F32 get(U32 x, U32 y) const;

	inline Vectorf4 getRow(U32 row) const;

	void set(U32 r, U32 c, F32 v);

	//value copy temporarily
	void set(F32 _d[4][4]);
	 
	Matrixf44& RotateX(F32 theta);

	Matrixf44& RotateY(F32 theta);

	Matrixf44& RotateZ(F32 theta);

	Matrixf44& Translate(F32 dx, F32 dy, F32 dz);

	Matrixf44& Scale(F32 scaleX, F32 scaleY, F32 scaleZ); 

	void MakeIdentity();

	void MakeInverse();

	Matrixf44 getInverse();

	//Debug method
	void Print()
	{
		printf("%.4lf,%.4lf,%.4lf,%.4lf\n", _matrix[0][0], _matrix[0][1], _matrix[0][2], _matrix[0][3]);
		printf("%.4lf,%.4lf,%.4lf,%.4lf\n", _matrix[1][0], _matrix[1][1], _matrix[1][2], _matrix[1][3]);
		printf("%.4lf,%.4lf,%.4lf,%.4lf\n", _matrix[2][0], _matrix[2][1], _matrix[2][2], _matrix[2][3]);
		printf("%.4lf,%.4lf,%.4lf,%.4lf\n", _matrix[3][0], _matrix[3][1], _matrix[3][2], _matrix[3][3]);
	}

public:

	union {
		F32 _matrix[4][4];
	};

protected:
	
	F32 transpose[4][4];

	bool transposeReady;
};

NS_End(core)
NS_End(XIRE)