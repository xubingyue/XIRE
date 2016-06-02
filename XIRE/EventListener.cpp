#include "EventListener.h"
#include <algorithm>

NS_Using(XIRE)
 
EventListener::EventListener(void *parent)
	:Root(parent)
{
	MouseLeftButtonDown += CCallback2(&EventListener::onMouseLeftButtonDown);
	MouseLeftButtonUp += CCallback2(&EventListener::onMouseLeftButtonUp);
	MouseLeftButtonDoubleClick += CCallback2(&EventListener::onMouseLeftButtonDoubleClick);
	MouseMiddleButtonDown += CCallback2(&EventListener::onMouseMiddleButtonDown);
	MouseMiddleButtonUp += CCallback2(&EventListener::onMouseMiddleButtonUp);
	MouseRightButtonDown += CCallback2(&EventListener::onMouseRightButtonDown);
	MouseRightButtonUp += CCallback2(&EventListener::onMouseRightButtonUp);
	MouseRightButtonDoubleClick += CCallback2(&EventListener::onMouseRightButtonDoubleClick);
	MouseEnter += CCallback2(&EventListener::onMouseEnter);
	MouseLeave += CCallback2(&EventListener::onMouseLeave);
	MouseMove += CCallback2(&EventListener::onMouseMove);
	MouseWheel += CCallback2(&EventListener::onMouseWheel);
	KeyDown +=						CCallback2(&EventListener::onKeyDown);
	KeyUp +=						CCallback2(&EventListener::onKeyUp);
}

EventListener::~EventListener()
{ 
	MouseLeftButtonDown -= CCallback2(&EventListener::onMouseLeftButtonDown);
	MouseLeftButtonUp -= CCallback2(&EventListener::onMouseLeftButtonUp);
	MouseLeftButtonDoubleClick -= CCallback2(&EventListener::onMouseLeftButtonDoubleClick);
	MouseMiddleButtonDown -= CCallback2(&EventListener::onMouseMiddleButtonDown);
	MouseMiddleButtonUp -= CCallback2(&EventListener::onMouseMiddleButtonUp);
	MouseRightButtonDown -= CCallback2(&EventListener::onMouseRightButtonDown);
	MouseRightButtonUp -= CCallback2(&EventListener::onMouseRightButtonUp);
	MouseRightButtonDoubleClick -= CCallback2(&EventListener::onMouseRightButtonDoubleClick);
	MouseEnter -= CCallback2(&EventListener::onMouseEnter);
	MouseLeave -= CCallback2(&EventListener::onMouseLeave);
	MouseMove -= CCallback2(&EventListener::onMouseMove);
	MouseWheel -= CCallback2(&EventListener::onMouseWheel);
	KeyDown -= CCallback2(&EventListener::onKeyDown);
	KeyUp -= CCallback2(&EventListener::onKeyUp);
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