#pragma once

#include "EventHandler.h"
#include "Window.h"

NS_Begin(XIRE)
 
class XIREAPI Application
{
public:

	Application(String title = XIRE_DEFAULT_TITLE, U32 width=XIRE_DEFAULT_WND_W, U32 height=XIRE_DEFAULT_WND_H);
	
	virtual ~Application();

//public:
//
//	static Application* get()
//	{
//		static Application _inst;
//		return &_inst;
//	}

public:

	void AddWindow(Window* window); 

	Window* AddWindow(String title,U32 Width= XIRE_DEFAULT_WND_W,U32 Height= XIRE_DEFAULT_WND_H);
 
	Window* GetMainWindow();

	Window* GetWindow(String title);

	virtual void Startup();

	virtual void Run();

	virtual void Pause();

	virtual void Resume();

	virtual void Exit(bool force=false);

	virtual void OnApplicationInitialized();

	virtual void OnApplicationDestroy();

	virtual void OnApplicationUpdate();  

	virtual void OnApplicationRender();
	
	void OnWindowRender(void* sender, WindowEventArgs e);

	void OnWindowClosed(void* sender, WindowEventArgs e);

	ApplicationEventHandler ApplicationInitialized;   

	ApplicationEventHandler ApplicationRender;

public:

	HINSTANCE GetAppHandle();

private:

	HINSTANCE handleApp;

	std::vector<Window*> windows;

	Window* mainWindow;
}; 

NS_End(XIRE)


