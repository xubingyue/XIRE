#include "Callable.h"
#include <algorithm>

NS_Using(XIRE)
 
Callable::Callable(void *parent)
	:Root(parent)
{
	MouseLeftButtonDown +=			CCallback2(&Callable::onMouseLeftButtonDown);
	MouseLeftButtonUp +=			CCallback2(&Callable::onMouseLeftButtonUp);
	MouseLeftButtonDoubleClick +=	CCallback2(&Callable::onMouseLeftButtonDoubleClick);
	MouseMiddleButtonDown +=		CCallback2(&Callable::onMouseMiddleButtonDown);
	MouseMiddleButtonUp +=			CCallback2(&Callable::onMouseMiddleButtonUp);
	MouseRightButtonDown +=			CCallback2(&Callable::onMouseRightButtonDown);
	MouseRightButtonUp +=			CCallback2(&Callable::onMouseRightButtonUp);
	MouseRightButtonDoubleClick +=	CCallback2(&Callable::onMouseRightButtonDoubleClick);
	MouseEnter +=					CCallback2(&Callable::onMouseEnter);
	MouseLeave +=					CCallback2(&Callable::onMouseLeave);
	MouseMove +=					CCallback2(&Callable::onMouseMove);
	MouseWheel +=					CCallback2(&Callable::onMouseWheel);
	KeyDown +=						CCallback2(&Callable::onKeyDown);
	KeyUp +=						CCallback2(&Callable::onKeyUp);

	UpdateEventRegistry();
}

Callable::~Callable()
{ 
	MouseLeftButtonDown -=			CCallback2(&Callable::onMouseLeftButtonDown);
	MouseLeftButtonUp -=			CCallback2(&Callable::onMouseLeftButtonUp);
	MouseLeftButtonDoubleClick -=	CCallback2(&Callable::onMouseLeftButtonDoubleClick);
	MouseMiddleButtonDown -=		CCallback2(&Callable::onMouseMiddleButtonDown);
	MouseMiddleButtonUp -=			CCallback2(&Callable::onMouseMiddleButtonUp);
	MouseRightButtonDown -=			CCallback2(&Callable::onMouseRightButtonDown);
	MouseRightButtonUp -=			CCallback2(&Callable::onMouseRightButtonUp);
	MouseRightButtonDoubleClick -=	CCallback2(&Callable::onMouseRightButtonDoubleClick);
	MouseEnter -=					CCallback2(&Callable::onMouseEnter);
	MouseLeave -=					CCallback2(&Callable::onMouseLeave);
	MouseMove -=					CCallback2(&Callable::onMouseMove);
	MouseWheel -=					CCallback2(&Callable::onMouseWheel);
	KeyDown -=						CCallback2(&Callable::onKeyDown);
	KeyUp -=						CCallback2(&Callable::onKeyUp);

	std::vector<Callable*>::iterator itr;
	for (itr = ChildContainer.begin(); itr != ChildContainer.end(); ++itr)
	{
		SafeDelete(*itr);
	}
}
	
void Callable::RegisterEventType(const U32& type)
{ 
	registeredEventType |= type;
}

void Callable::RemoveEventType(const U32 &type)
{
	registeredEventType &= ~type;  
}

void Callable::AddChild(Callable *node)
{
	if (std::find(ChildContainer.begin(), ChildContainer.end(), node) == ChildContainer.end())
	{
		ChildContainer.push_back(node);
		node->Parent = this;
		UpdateEventRegistry();
	}
}

void Callable::RaiseEvent(IEvent e)
{
	switch (e.type)
	{
	case ET_ApplicationEvent:
	{

	} break;
	case ET_KeyboardEvent:
	{
		if (!KeyDown.IsNull())
		{
			KeyDown(this, NULL);
		}
	} break;
	case ET_MouseMoveEvent:
	{
		if (!MouseMove.IsNull())
		{
			MouseMove(this, NULL);
		}
	}
	break;
	case ET_WindowEvent:
	{

	} break;
	default:
	{

	} break;
	}
}

void Callable::DispatchEvent(CallableArray array, IEvent e)
{
	CallableArray::iterator itr;
	for (itr = array.begin(); itr != array.end(); ++itr)
	{
		Callable *listener = *itr;
		listener->RaiseEvent(e);
	}
}

void Callable::UpdateEventRegistry()
{
	UpdateEventRegistry(this);

	std::vector<Callable*>::iterator itr;
	for (itr = ChildContainer.begin(); itr != ChildContainer.end(); ++itr)
	{
		UpdateEventRegistry(*itr);
	}
}

void Callable::UpdateEventRegistry(Callable *callable)
{  
	if(callable->registeredEventType & ET_MouseEvent)
		this->RegisterEvent(ET_MouseEvent, callable);
	else
		this->UnregisterEvent(ET_MouseEvent, callable);

	if (callable->registeredEventType & ET_KeyboardEvent)
		this->RegisterEvent(ET_KeyboardEvent, callable);
	else
		this->UnregisterEvent(ET_KeyboardEvent, callable); 
}

void Callable::RegisterEvent(EventType type, Callable *component)
{
	auto itr = std::find(eventRegistry[type].begin(), eventRegistry[type].end(), component);

	if (itr == eventRegistry[type].end())
	{
		eventRegistry[type].push_back(component);
	}
}

void Callable::UnregisterEvent(EventType type, Callable *component)
{
	if (eventRegistry.find(type) == eventRegistry.end())
	{
		return;
	}

	auto itr = std::find(eventRegistry[type].begin(), eventRegistry[type].end(), component);

	if (itr != eventRegistry[type].end())
	{
		eventRegistry[type].erase(itr);
	}
}