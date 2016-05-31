#include "Application.h"

NS_Using(XIRE)

//traditionally we have only one window for a game instance
//so a window is created upon application startup

Application::Application(String title, U32 width, U32 height)
{
	handleApp = ::GetModuleHandle(NULL);

	mainWindow = AddWindow(title, width, height);
	mainWindow->WindowRender += MakeCCallback2(&Application::OnWindowRender);
	mainWindow->Show();
}
 
Application::~Application()
{
	for (int i = 0; i < windows.size(); ++i)
	{
		SafeDelete(windows[i]); 
	}

	windows.clear();
}

Window* Application::GetMainWindow()
{
	return mainWindow;
}

HINSTANCE Application::GetAppHandle()
{
	if (handleApp == NULL)
	{
		handleApp = ::GetModuleHandle(NULL);
	}

	return handleApp;
}

void Application::AddWindow(Window* window)
{
	windows.push_back(window);
}

Window* Application::AddWindow(String title, U32 width, U32 height)
{
	Window* window = new Window(this->GetAppHandle(), title, width, height);
	AddWindow(window);

	return window;
}

void Application::Startup()
{
	//Initialization code goes here
	OnApplicationInitialized(); 
}

void Application::Run()
{
	Startup();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	for (; msg.message != WM_QUIT;)
	{
		if (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) != NULL)
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			//render & update here
			
			OnApplicationUpdate();
			OnApplicationBeginFrame();
			OnApplicationEndFrame();
			OnApplicationRender(); 
		}
	}
}

void Application::Pause()
{

}

void Application::Resume()
{

}

void Application::OnApplicationInitialized()
{
	if (!ApplicationInitialized.IsNull())
	{
		ApplicationInitialized(this, NULL);
	}
}

void Application::OnApplicationDestroy()
{

}

void Application::OnApplicationUpdate()
{

}

void Application::OnApplicationBeginFrame()
{

}

void Application::OnApplicationEndFrame()
{

}

void Application::OnApplicationRender()
{
	for (int i = 0; i < windows.size(); ++i)
	{ 
		windows[i]->OnRender(); 
	}
}

void Application::OnWindowRender(void* sender, RenderEventArgs e)
{
	if (!ApplicationRender.IsNull())
	{
		ApplicationRender(this, new AppRenderEvent(mainWindow));
	}
}