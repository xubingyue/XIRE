#pragma once

#include "Root.h"

NS_Begin(XIRE)

class XIREAPI GpuObject : public Root
{
public:

	GpuObject();

	virtual ~GpuObject();

protected:

	void *buffer;
};

NS_End(XIRE)