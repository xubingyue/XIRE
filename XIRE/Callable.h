#pragma once

#include "XIRE_Afx.h"
#include "EventHandler.h" 
#include "Root.h"

#include <map>
#include <vector>

NS_Begin(XIRE)   
 
class XIREAPI Callable : public Root
{
public:
 
	typedef std::vector<Callable*> CallableArray;

	typedef std::map<EventType, CallableArray> EventRegistry;

	Callable(void *parent = nullptr);

	virtual ~Callable(); 

	void RegisterEventType(const U32 &type = ET_KeyboardEvent | ET_MouseEvent );

	void RemoveEventType(const U32 &type = ET_KeyboardEvent | ET_MouseEvent ); 

	void RaiseEvent(IEvent e);

	static void DispatchEvent(CallableArray array, IEvent e);

public:

	virtual void onMouseLeftButtonDown(void *sender, MouseEventArgs e)  {}

	virtual void onMouseLeftButtonUp(void *sender, MouseEventArgs e)  {}

	virtual void onMouseMiddleButtonDown(void *sender, MouseEventArgs e)  {}

	virtual void onMouseMiddleButtonUp(void *sender, MouseEventArgs e)  {}

	virtual void onMouseRightButtonDown(void *sender, MouseEventArgs e)  {}

	virtual void onMouseRightButtonUp(void *sender, MouseEventArgs e)  {}

	virtual void onMouseWheel(void *sender, MouseEventArgs e)  {}

	virtual void onMouseEnter(void *sender, MouseEventArgs e)  {}

	virtual void onMouseLeave(void *sender, MouseEventArgs e)  {}

	virtual void onMouseMove(void *sender, MouseEventArgs e)  {}

	virtual void onMouseLeftButtonDoubleClick(void *sender, MouseEventArgs e)  {}

	virtual void onMouseRightButtonDoubleClick(void *sender, MouseEventArgs e)  {}

	virtual void onKeyDown(void *sender, KeyEventArgs e)  {}

	virtual void onKeyUp(void *sender, KeyEventArgs e)  {}

	MouseLeftButtonDownHandler MouseLeftButtonDown;

	MouseLeftButtonUpHandler MouseLeftButtonUp;

	MouseLeftButtonDoubleClickHandler MouseLeftButtonDoubleClick;

	MouseMiddleButtonDownHandler MouseMiddleButtonDown;

	MouseMiddleButtonUpHandler MouseMiddleButtonUp;

	MouseRightButtonDownHandler MouseRightButtonDown;

	MouseRightButtonUpHandler MouseRightButtonUp;

	MouseRightButtonDoubleClickHandler MouseRightButtonDoubleClick;

	MouseEnterHandler MouseEnter;

	MouseLeaveHandler MouseLeave;

	MouseMoveHandler MouseMove;

	MouseWheelHandler MouseWheel;

	KeyDownHandler KeyDown;

	KeyUpHandler KeyUp;

public:

	virtual void AddChild(Callable *drawable);

	std::vector<Callable*> ChildContainer;

protected: 

	//生成对象的事件注册件表
	void UpdateEventRegistry();

	void UpdateEventRegistry(Callable* callable);

	void RegisterEvent(EventType type, Callable *component);

	void UnregisterEvent(EventType type, Callable *component);

protected:

	EventRegistry eventRegistry;

	U32 registeredEventType;

private: 

};

NS_End(XIRE)