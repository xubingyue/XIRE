#pragma once

#include "Camera.h"

NS_Begin(XIRE)

class Viewport
{
public:
	
	Viewport();

	virtual ~Viewport();
	
	Camera *camera;
};

NS_End(XIRE)