#pragma once

#include "Vectorf3.hpp" 

NS_Begin(XIRE)
NS_Begin(core)

class XIREAPI Matrixf33
{
public:

	Matrixf33()
	{
		transposeReady = false;
	}

	Matrixf33(F32 m[3][3])
		:Matrixf33()
	{
		this->set(m);
	}

	Matrixf33& getTranpose()
	{
		if (transposeReady == false)
		{
			for (int j = 0; j < 3; ++j)
				for (int i = 0; i < 3; ++i)
					transpose[i][j] = d[j][i];

			transposeReady = true;
		}

		Matrixf33 *matrixInverse = new Matrixf33();
		matrixInverse->set(transpose);

		return *matrixInverse;
	}

	Matrixf33& operator*(const Matrixf33& matrix)
	{
		F32 temp[3][3];

		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				temp[i][j] = d[i][0] * matrix.d[0][j] + d[i][1] * matrix.d[1][j] + d[i][2] * matrix.d[2][j] + d[i][3] * matrix.d[3][j];

		Matrixf33* matrixNew = new Matrixf33();
		matrixNew->set(temp);

		return *matrixNew;
	}

	void set(U32 r, U32 c, F32 v)
	{
		if (r >= 0 && r < 3 && c >= 0 && c < 3)
		{
			d[r][c] = v;

			if (transposeReady)
				transposeReady = false;
		}
	}

	//value copy temporarily
	void set(F32 _d[3][3])
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				d[i][j] = _d[i][j];

		transposeReady = false;
	}

protected:
  
	F32 d[3][3];
	F32 transpose[3][3];

	bool transposeReady;
};

NS_End(core)
NS_End(XIRE)