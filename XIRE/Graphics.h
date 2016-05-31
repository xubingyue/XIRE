#pragma once
  
#include "Drawable.h"

#include <map>

NS_Begin(XIRE)

class Window;
class RenderBase;
class SwPrimitive;

static Text gDriverPriority[]  = { S("D3D12Driver"),S("VulkanDriver"),S("D3D11Driver"),S("D3D10Driver") ,S("D3D9Driver") ,S("OpenGLDriver"),S("SoftwareDriver") };

class XIREAPI Graphics
{
public:

	explicit Graphics(Window* _window);

	virtual ~Graphics();
	 
	RenderBase *LoadDriver(String driverName);

	RenderBase *GetDriver();

	bool Startup();

	bool Shutdown();

	void BeginFrame();

	void EndFrame();

	void Swap();

	void Draw(Drawable* drawable);

	void DrawPrimitive(SwPrimitive *primitive);

	void ResetDefaultDriver();

protected:

	RenderBase *currentDriver; 

	std::map<String, RenderBase*> drivers;

	Window* window;
};

NS_End(XIRE)