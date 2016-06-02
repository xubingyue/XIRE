#include "Application.h"
#include <algorithm>

NS_Using(XIRE)

//traditionally we have only one window for a game instance
//so a main window is created upon application startup
//however with AddWindow method you can add any amount of window at the same time

Application::Application(String title, U32 width, U32 height)
{
	handleApp = ::GetModuleHandle(NULL);

	AddWindow(title, width, height);
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

Window* Application::GetWindow(String title)
{
	for (int i = 0; i < windows.size(); ++i)
	{
		if (windows[i]->Name == title)
		{
			return windows[i];
		}
	}

	return nullptr;
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
	window->WindowRender += MakeCCallback2(&Application::OnWindowRender);
	window->WindowClosed += MakeCCallback2(&Application::OnWindowClosed);
	window->Show();

	windows.push_back(window);

	if (mainWindow == nullptr)
	{
		mainWindow = windows.front();
		SetForegroundWindow(mainWindow->GetWindowHandle());
	}
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

void Application::OnApplicationRender()
{
	for (int i = 0; i < windows.size(); ++i)
	{ 
		windows[i]->OnRender(); 
	}
}

void Application::Exit(bool force)
{
	if (force == false)
	{
		::PostQuitMessage(0);
	}
	else
	{
		::TerminateProcess(handleApp, 0);
	} 
}

void Application::OnWindowRender(void* sender, WindowEventArgs e)
{
	if (!ApplicationRender.IsNull())
	{
		ApplicationRender(this,  &ApplicationEvent((Window*)sender));  
	}
}

void Application::OnWindowClosed(void* sender, WindowEventArgs e)
{
	Window* wnd = (Window*)sender;

	auto itr = std::find(windows.begin(), windows.end(), wnd);
	 
	windows.erase(itr);

	if (windows.size() == 0)
	{
		this->Exit();
		return;
	}

	if (wnd == mainWindow)
	{
		mainWindow = windows.front();
	}  
}