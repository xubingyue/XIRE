#include "Graphics.h" 
#include "SoftwareDriver.h" 
#include "Window.h"
#include "Primitive.hpp"

NS_Using(XIRE)

Graphics::Graphics(Window *_window)
{
	window = _window; 

	int drvIndex = 0;
	while ((currentDriver = LoadDriver(gDriverPriority[drvIndex]))==NULL)
	{
		++drvIndex;
	}

	this->Startup();
}

Graphics::~Graphics()
{
	SafeDelete(currentDriver);
}

RenderBase* Graphics::LoadDriver(String driverName)
{ 
	//T("D3D12Driver"),T("VulkanDriver"),T("D3D11Driver"),T("D3D10Driver") ,T("D3D9Driver") ,T("OpenGLDriver"),T("SoftwareDriver")
	if (driverName == S("D3D12Driver"))
	{
		
	}
	else if (driverName == S("VulkanDriver"))
	{

	}
	else if (driverName == S("D3D11Driver"))
	{

	}
	else if (driverName == S("D3D10Driver"))
	{

	}
	else if (driverName == S("D3D9Driver"))
	{

	}
	else if (driverName == S("OpenGLDriver"))
	{

	}
	else if (driverName == S("SoftwareDriver"))
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
	currentDriver->StartupRender();
	return true;
}

bool Graphics::Shutdown()
{
	currentDriver->ShutdownRender();
	return true;
}

void Graphics::Swap()
{
	//currentDriver->BeginFrame();
	//currentDriver->EndFrame();
	currentDriver->Present();
}

void Graphics::BeginFrame()
{
	if (currentDriver != nullptr)
	{
		currentDriver->BeginFrame();
	}
}

void Graphics::EndFrame()
{
	if (currentDriver != nullptr)
	{
		currentDriver->EndFrame();
	}
}

void Graphics::ResetDefaultDriver()
{
	currentDriver = LoadDriver(gDriverPriority[0]);
}

void Graphics::Draw(Drawable* drawable)
{
	drawable->Draw(this);
}

void Graphics::DrawPrimitive(SwPrimitive *primitive) 
{
	currentDriver->DrawPrimitive(primitive);
}