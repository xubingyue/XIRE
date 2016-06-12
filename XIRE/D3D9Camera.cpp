#include "D3D9Camera.h"

NS_Using(XIRE)

D3D9Camera::D3D9Camera(void* parent)
{
	Parent = parent;

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //Set position to 0,0,0
	m_LookAt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);	//Set look at to 0,0,1
	m_Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);	//Set right to 1,0,0
	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//Set up to 0,1,0

	m_RotateAroundUp = m_RotateAroundRight = m_RotateAroundLookAt = 0;

	D3DXMatrixIdentity(&ViewMatrix);
}

void D3D9Camera::SetPosition(D3DXVECTOR3 *Pos)
{
	m_Position = *Pos;
	m_bChanged = true;
}

void D3D9Camera::MoveForward(float Dist)
{
	m_Position += Dist*m_LookAt;
	m_bChanged = true;
}
void D3D9Camera::MoveRight(float Dist)
{
	m_Position += Dist*m_Right;
	m_bChanged = true;
}
void D3D9Camera::MoveUp(float Dist)
{
	m_Position += Dist*m_Up;
	m_bChanged = true;
}
void D3D9Camera::MoveInDirection(float Dist, D3DXVECTOR3 *Dir)
{
	m_Position += Dist*(*Dir);
	m_bChanged = true;
}

void D3D9Camera::RotateDown(float Angle)
{
	m_RotateAroundRight += Angle;
	m_bChanged = true;
}

void D3D9Camera::RotateRight(float Angle)
{
	m_RotateAroundUp += Angle;
	m_bChanged = true;
}
void D3D9Camera::Roll(float Angle)
{
	m_RotateAroundLookAt += Angle;
	m_bChanged = true;
}

void D3D9Camera::Update()
{
	if (m_bChanged)
	{
		//Matrices to store the transformations about our axes
		D3DXMATRIX MatTotal;
		D3DXMATRIX MatRotateAroundRight;
		D3DXMATRIX MatRotateAroundUp;
		D3DXMATRIX MatRotateAroundLookAt;
	 
		//Get the matrix for each rotation
		D3DXMatrixRotationAxis(&MatRotateAroundRight,
			&m_Right, m_RotateAroundRight);
		D3DXMatrixRotationAxis(&MatRotateAroundUp,
			&m_Up, m_RotateAroundUp);
		D3DXMatrixRotationAxis(&MatRotateAroundLookAt,
			&m_LookAt, m_RotateAroundLookAt);
		//Combine the transformations into one matrix
		D3DXMatrixMultiply(&MatTotal, &MatRotateAroundUp,
			&MatRotateAroundRight);
		D3DXMatrixMultiply(&MatTotal, &MatRotateAroundLookAt,
			&MatTotal);
		//Transforms two vectors by our matrix and computes the third by
		//cross product
		D3DXVec3TransformCoord(&m_Right, &m_Right, &MatTotal);
		D3DXVec3TransformCoord(&m_Up, &m_Up, &MatTotal);
		D3DXVec3Cross(&m_LookAt, &m_Right, &m_Up);
		//Check to ensure vectors are perpendicular
		if (fabs(D3DXVec3Dot(&m_Up, &m_Right)) > 0.01)
		{
			//If they��re not
			D3DXVec3Cross(&m_Up, &m_LookAt, &m_Right);
		}
		//Normalize our vectors
		D3DXVec3Normalize(&m_Right, &m_Right);
		D3DXVec3Normalize(&m_Up, &m_Up);
		D3DXVec3Normalize(&m_LookAt, &m_LookAt);
		//Compute the bottom row of the view matrix
		float fView41, fView42, fView43;
		fView41 = -D3DXVec3Dot(&m_Right, &m_Position);
		fView42 = -D3DXVec3Dot(&m_Up, &m_Position);
		 
		fView43 = -D3DXVec3Dot(&m_LookAt, &m_Position);
		//Fill in the view matrix
		ViewMatrix = D3DXMATRIX(m_Right.x, m_Up.x, m_LookAt.x, 0.0f,
			m_Right.y, m_Up.y, m_LookAt.y, 0.0f,
			m_Right.z, m_Up.z, m_LookAt.z, 0.0f,
			fView41, fView42, fView43, 1.0f);
	}
 
	//Set view transform
	//m_pDevice->SetTransform(D3DTS_VIEW, &m_MatView);
	//Reset update members
	m_RotateAroundRight = m_RotateAroundUp = m_RotateAroundLookAt = 0.0f;
	m_bChanged = false;
}

