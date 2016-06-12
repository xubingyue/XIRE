#pragma once

#include "SwCamera.h"

NS_Begin(XIRE)

class XIREAPI Scene
{
public:

	Scene();

	virtual ~Scene();

	SwCamera* CreateCamera(); 

};

NS_End(XIRE)