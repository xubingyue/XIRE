#pragma once

#include "XIRE_Afx.h" 
#include "Root.h"

NS_Begin(XIRE) 

class Graphics;
class Window;

enum XIREAPI EventType
{
	ET_KeyBoardEvent = 0x1,
	ET_MouseEvent = 0x1 << 1,
	ET_MiscEvent = 0x1 << 2,
	ET_WindowEvent = 0x1<<3,
	ET_ApplicationEvent = 0x1<<4
};

struct XIREAPI IEvent
{
public:
	EventType type;
};

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

struct XIREAPI ApplicationEvent : public IEvent
{
	Window *window;

	explicit ApplicationEvent(Window *_w)
	{
		type = ET_ApplicationEvent;
		window = _w;
	}
};
 
struct XIREAPI WindowEvent : public IEvent
{
	WindowEvent() 
	{
		type = ET_WindowEvent;
	} 

};

struct XIREAPI KeyEvent : public IEvent
{
	KeyEvent()
	{
		type = ET_KeyBoardEvent;
	}

	U8 keycode;

	bool IsPressed;
};

struct XIREAPI MouseEvent : public IEvent
{
	MouseEvent()
	{
		type = ET_MouseEvent;
	}

	U8 keycode;

	bool IsPressed;
};

//Custom event

#define ApplicationEventArgs				XIRE::EventArgs<XIRE::ApplicationEvent>
#define ApplicationEventHandler				XIRE::EventHandler<XIRE::ApplicationEvent> 

#define WindowEventArgs						XIRE::EventArgs<XIRE::WindowEvent> 
#define WindowEventHandler					XIRE::EventHandler<XIRE::WindowEvent> 

//Input event

#define KeyEventArgs						XIRE::EventArgs<XIRE::KeyEvent>
#define KeyEventHandler						XIRE::EventHandler<XIRE::KeyEvent>
#define KeyDownHandler						KeyEventHandler
#define KeyUpHandler						KeyEventHandler

#define MouseEventArgs						XIRE::EventArgs<XIRE::MouseEvent>
#define MouseEventHandler					XIRE::EventHandler<XIRE::MouseEvent>
#define MouseLeftButtonDownHandler			MouseEventHandler
#define MouseLeftButtonUpHandler			MouseEventHandler
#define MouseLeftButtonDoubleClickHandler	MouseEventHandler
#define MouseMiddleButtonDownHandler		MouseEventHandler
#define MouseMiddleButtonUpHandler			MouseEventHandler
#define MouseRightButtonDownHandler			MouseEventHandler
#define MouseRightButtonUpHandler			MouseEventHandler
#define MouseRightButtonDoubleClickHandler	MouseEventHandler
#define MouseEnterHandler					MouseEventHandler
#define MouseLeaveHandler					MouseEventHandler
#define MouseMoveHandler					MouseEventHandler 
#define MouseWheelHandler					MouseEventHandler  

NS_End(XIRE) 