#pragma once

#include "XIRE_Afx.h"
#include "EventHandler.h" 
#include "Root.h"

#include <map>
#include <vector>

NS_Begin(XIRE)  

class EventListener;

typedef std::vector<EventListener*> EventListenerArray;

typedef std::map<EventType, EventListenerArray> EventRegistry;

class XIREAPI EventListener : public Root
{
public:
 
	EventListener(void *parent = nullptr);

	virtual ~EventListener(); 

	void RegisterEventListener(const U32 &type = ET_KeyBoardEvent | ET_MouseEvent | ET_MiscEvent);

	void RemoveEventListener(const U32 &type = ET_KeyBoardEvent | ET_MouseEvent | ET_MiscEvent);
	 
	void RaiseEvent(IEvent e);

	static void DispatchEvent(EventListenerArray array, IEvent e);

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

protected:

	U32 registeredEventType;

private: 

};

NS_End(XIRE)