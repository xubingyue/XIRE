#include "EventListener.h"
#include <algorithm>

NS_Using(XIRE)
 
EventListener::EventListener(void *parent)
	:Root(parent)
{
	MouseLeftButtonDown += MakeCCallback2(&EventListener::onMouseLeftButtonDown);
	MouseLeftButtonUp += MakeCCallback2(&EventListener::onMouseLeftButtonUp);
	MouseLeftButtonDoubleClick += MakeCCallback2(&EventListener::onMouseLeftButtonDoubleClick);
	MouseMiddleButtonDown += MakeCCallback2(&EventListener::onMouseMiddleButtonDown);
	MouseMiddleButtonUp += MakeCCallback2(&EventListener::onMouseMiddleButtonUp);
	MouseRightButtonDown += MakeCCallback2(&EventListener::onMouseRightButtonDown);
	MouseRightButtonUp += MakeCCallback2(&EventListener::onMouseRightButtonUp);
	MouseRightButtonDoubleClick += MakeCCallback2(&EventListener::onMouseRightButtonDoubleClick);
	MouseEnter += MakeCCallback2(&EventListener::onMouseEnter);
	MouseLeave += MakeCCallback2(&EventListener::onMouseLeave);
	MouseMove += MakeCCallback2(&EventListener::onMouseMove);
	MouseWheel += MakeCCallback2(&EventListener::onMouseWheel);
	KeyDown +=						MakeCCallback2(&EventListener::onKeyDown);
	KeyUp +=						MakeCCallback2(&EventListener::onKeyUp);
}

EventListener::~EventListener()
{ 
	MouseLeftButtonDown -= MakeCCallback2(&EventListener::onMouseLeftButtonDown);
	MouseLeftButtonUp -= MakeCCallback2(&EventListener::onMouseLeftButtonUp);
	MouseLeftButtonDoubleClick -= MakeCCallback2(&EventListener::onMouseLeftButtonDoubleClick);
	MouseMiddleButtonDown -= MakeCCallback2(&EventListener::onMouseMiddleButtonDown);
	MouseMiddleButtonUp -= MakeCCallback2(&EventListener::onMouseMiddleButtonUp);
	MouseRightButtonDown -= MakeCCallback2(&EventListener::onMouseRightButtonDown);
	MouseRightButtonUp -= MakeCCallback2(&EventListener::onMouseRightButtonUp);
	MouseRightButtonDoubleClick -= MakeCCallback2(&EventListener::onMouseRightButtonDoubleClick);
	MouseEnter -= MakeCCallback2(&EventListener::onMouseEnter);
	MouseLeave -= MakeCCallback2(&EventListener::onMouseLeave);
	MouseMove -= MakeCCallback2(&EventListener::onMouseMove);
	MouseWheel -= MakeCCallback2(&EventListener::onMouseWheel);
	KeyDown -= MakeCCallback2(&EventListener::onKeyDown);
	KeyUp -= MakeCCallback2(&EventListener::onKeyUp);
}
	
void EventListener::RegisterEventListener(const U32& type)
{ 
	registeredEventType |= type;
}

void EventListener::RemoveEventListener(const U32 &type)
{
	registeredEventType &= ~type;  
}

void EventListener::RaiseEvent(IEvent e)
{
	switch (e.type)
	{
	case ET_ApplicationEvent:
	{

	}
		break;
	case ET_KeyBoardEvent:
	{
		if (!KeyDown.IsNull())
		{
			KeyDown(this, NULL);
		}
	}
		break;
	case ET_MouseEvent:
	{

	}
		break;
	case ET_WindowEvent:
	{

	}
		break;
	case ET_MiscEvent:
	{

	}
		break;
	default:
		break;
	}
}

void EventListener::DispatchEvent(EventListenerArray array, IEvent e)
{
	EventListenerArray::iterator itr;
	for (itr = array.begin(); itr != array.end(); ++itr)
	{
		EventListener *listener = *itr;
		listener->RaiseEvent(e);
	}
}