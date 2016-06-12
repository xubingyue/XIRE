#include "Graphics.h" 
#include "SoftwareDriver.h" 
#include "Window.h"
#include "Primitive.hpp"
#include "D3D9Driver.h"

NS_Using(XIRE)

Graphics::Graphics(Window *_window, E_RENDER_DRIVER driverFlag)
{
	window = _window; 

	currentDriver = LoadDriver(driverFlag);

	if (currentDriver == NULL)
	{
		printf("%s not found, loading default driver instead...\n", GetRenderDriverAlias(driverFlag));

		int drvIndex = 0;
		while (drvIndex <= E_SoftwareDriver && (currentDriver = LoadDriver(E_RENDER_DRIVER(drvIndex))) == NULL)
		{
			++drvIndex;
		}
	} 
	
	if (currentDriver == NULL)
	{
		printf("No graphics driver available. now exit\n", GetRenderDriverAlias(driverFlag));
		return;
	}

	this->Startup();
}

Graphics::~Graphics()
{
	SafeDelete(currentDriver); 
}

RenderBase* Graphics::LoadDriver(E_RENDER_DRIVER driverFlag)
{ 
 	if (driverFlag == E_D3D12Driver)
	{
		
	}
	else if (driverFlag == E_D3D11Driver)
	{

	}
	else if (driverFlag == E_D3D10Driver)
	{

	}
	else if (driverFlag == E_D3D9Driver)
	{
		return new D3D9Driver(window); 
	}
	else if (driverFlag == E_VulkanDriver)
	{
	}
	else if (driverFlag == E_OpenGLDriver)
	{

	}
	else if (driverFlag == E_SoftwareDriver)
	{
		return new SoftwareDriver(window);
	} 

	return NULL;
}

RenderBase *Graphics::GetDriver()
{
	return currentDriver;
} 

bool Graphics::Startup()
{
	return currentDriver->StartupRender(); 
}

bool Graphics::Shutdown()
{
	currentDriver->ShutdownRender();
	return true;
}

void Graphics::Swap()
{ 
	currentDriver->Present();
}

bool Graphics::BeginFrame()
{
	if (currentDriver != nullptr)
	{
		return currentDriver->BeginFrame();
	}

	return false;
}

bool Graphics::EndFrame()
{
	if (currentDriver != nullptr)
	{
		return currentDriver->EndFrame();
	}

	return false;
}

void Graphics::ResetDefaultDriver()
{
	currentDriver = LoadDriver();
}

void Graphics::Draw(Drawable* drawable)
{
	drawable->Draw(this);
}

void Graphics::DrawPrimitive(SwPrimitive *primitive) 
{
	currentDriver->DrawPrimitive(primitive);
}