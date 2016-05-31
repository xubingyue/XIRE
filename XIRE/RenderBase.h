#pragma once

#include "Root.h"
#include <map> 

NS_Begin(XIRE)

class SwPrimitive;

class RenderBase : public Root
{
public: 

	virtual void BeginFrame() = 0;

	virtual void EndFrame() = 0;

	virtual bool StartupRender() = 0;

	virtual bool ShutdownRender() = 0;

	virtual void Reset() = 0;

	virtual void Present() = 0;

	virtual void Clear() = 0;

	virtual void DrawPrimitive(SwPrimitive *primitive) = 0;

};

NS_End(XIRE)