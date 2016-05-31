#pragma once

#include "XIRE_Afx.h" 

NS_Begin(XIRE) 

class Graphics;
class Window;

template<class T>  
class XIREAPI EventArgs
{
public: 

	EventArgs()
		:Handled(false)
	{
		Data = new T();
	}

	EventArgs(T *data)
		:Handled(false)
	{
		Data = data;
	} 

	~EventArgs()
	{
		//SafeDelete(Data);
	}

	T *Data;
	bool Handled;
};

struct XIREAPI AppStartupEvent
{ 
	int x;
};  


struct XIREAPI AppRenderEvent
{
	Window *window;

	explicit AppRenderEvent(Window *_w)
	{
		window = _w;
	}
};
 
struct XIREAPI RenderEvent
{
	int x;
};

#define ApplicationInitializedHandler XIRE::EventHandler<XIRE::AppStartupEvent>
#define AppStartupEventArgs XIRE::EventArgs<XIRE::AppStartupEvent>

#define ApplicationRenderHandler XIRE::EventHandler<XIRE::AppRenderEvent>
#define ApplicationRenderEventArgs XIRE::EventArgs<XIRE::AppRenderEvent>

#define RenderEventHandler XIRE::EventHandler<XIRE::RenderEvent>
#define RenderEventArgs XIRE::EventArgs<XIRE::RenderEvent>

NS_End(XIRE) 