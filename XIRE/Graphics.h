#pragma once
  
#include "Drawable.h"

#include <map>

NS_Begin(XIRE)

class Window;
class RenderBase;
class SwPrimitive;

static Text gDriverPriority[]  = { S("D3D9Driver") ,S("D3D10Driver") ,S("D3D11Driver"),S("D3D12Driver"),S("OpenGLDriver"),S("VulkanDriver"),S("SoftwareDriver") };

enum E_RENDER_DRIVER
{ 
	E_D3D9Driver = 0,
	E_D3D10Driver,
	E_D3D11Driver,
	E_D3D12Driver,
	E_OpenGLDriver,
	E_VulkanDriver,
	E_SoftwareDriver
};

static String GetRenderDriverAlias(E_RENDER_DRIVER eFlag)
{ 
	return gDriverPriority[(S32)eFlag];
}

class XIREAPI Graphics
{
public:

	explicit Graphics(Window* _window, E_RENDER_DRIVER driverFlag);

	virtual ~Graphics();
	 
	RenderBase *LoadDriver(E_RENDER_DRIVER driverFlag = E_D3D9Driver);

	RenderBase *GetDriver();

	bool Startup();

	bool Shutdown();

	bool BeginFrame();

	bool EndFrame();

	void Swap();

	void Draw(Drawable* drawable);

	void DrawPrimitive(SwPrimitive *primitive);

	void ResetDefaultDriver();

	void Print();

protected:

	RenderBase *currentDriver; 

	std::map<String, RenderBase*> drivers;

	Window* window;
};

NS_End(XIRE)