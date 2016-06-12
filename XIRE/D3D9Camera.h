#pragma once

#include "ICamera.hpp"

#include <d3d9.h> 
#include <d3dx9.h>
#include <d3dx9math.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

NS_Begin(XIRE)
 
class D3D9Camera : public Root
{
public:

	D3D9Camera(void* parent);

protected: 

	//Stores the position and three vectors
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_LookAt;
	D3DXVECTOR3 m_Right;
	D3DXVECTOR3 m_Up;

	//Stores whether the camera has changed since last update.
	//By change, we mean whether the camera has moved
	//or rotated. If so, we¡¯ll recompute the matrix.
	bool m_bChanged;

	//Stores the rotation to apply to a given axis
	float m_RotateAroundUp;

	float m_RotateAroundRight;

	float m_RotateAroundLookAt;

public:

	//Final view transformation matrix
	D3DXMATRIX ViewMatrix;

public:

	void Update();

	void SetPosition(D3DXVECTOR3 *Pos);

	void MoveForward(float Dist);

	void MoveRight(float Dist);

	void MoveUp(float Dist);

	void MoveInDirection(float Dist, D3DXVECTOR3 *Dir);

	void RotateDown(float Angle);

	void RotateRight(float Angle);

	void Roll(float Angle); 
};

NS_End(XIRE)