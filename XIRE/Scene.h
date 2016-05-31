#pragma once

#include "Camera.h"

NS_Begin(XIRE)

class XIREAPI Scene
{
public:

	Scene();

	virtual ~Scene();

	Camera* CreateCamera();


};

NS_End(XIRE)