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

struct XIREAPI ApplicationEvent
{
	Window *window;

	explicit ApplicationEvent(Window *_w)
	{
		window = _w;
	}
};
 
struct XIREAPI WindowEvent
{
	int x;
};

#define ApplicationEventArgs XIRE::EventArgs<XIRE::ApplicationEvent>
#define ApplicationEventHandler XIRE::EventHandler<XIRE::ApplicationEvent>
//#define ApplicationInitializedHandler ApplicationEventHandler
//#define ApplicationRenderHandler ApplicationEventHandler


#define WindowEventArgs XIRE::EventArgs<XIRE::WindowEvent> 
#define WindowEventHandler XIRE::EventHandler<XIRE::WindowEvent>
//#define WindowRenderEventHandler WindowEventHandler
//#define WindowUpdateEventHandler WindowEventHandler


NS_End(XIRE) 