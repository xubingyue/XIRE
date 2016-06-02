#include "Drawable.h"
#include "Graphics.h"
#include <algorithm> 

NS_Using(XIRE)

Drawable::Drawable()
{

}

Drawable::~Drawable()
{
	std::vector<Drawable*>::iterator itr;
	for (itr = ChildContainer.begin(); itr != ChildContainer.end(); ++itr)
	{
		SafeDelete(*itr);
	}
} 

void Drawable::AddChild(Drawable *drawable)
{
	if (std::find(ChildContainer.begin(), ChildContainer.end(), drawable) == ChildContainer.end())
	{
		ChildContainer.push_back(drawable); 
		drawable->Parent = this;
		UpdateEventRegistry();
	}
}

void Drawable::Draw(Graphics *g)
{
	for (U32 i = 0; i < primitives.size(); ++i)
	{
		g->DrawPrimitive(&primitives[i]);
	}

	std::vector<Drawable*>::iterator itr;
	for (itr = ChildContainer.begin(); itr != ChildContainer.end(); ++itr)
	{
		(*itr)->Draw(g);
	}
}

void Drawable::UpdateEventRegistry()
{
	std::vector<Drawable*>::iterator itr;
	for (itr = ChildContainer.begin(); itr != ChildContainer.end(); ++itr)
	{
		if ((*itr)->registeredEventType & ET_MouseEvent)
			this->RegisterEvent(ET_MouseEvent,*itr);
		else 
			this->UnregisterEvent(ET_MouseEvent, *itr);

		if ((*itr)->registeredEventType & ET_KeyBoardEvent)
			this->RegisterEvent(ET_KeyBoardEvent, *itr);
		else 
			this->UnregisterEvent(ET_KeyBoardEvent, *itr);

		if ((*itr)->registeredEventType & ET_MiscEvent)
			this->RegisterEvent(ET_MiscEvent, *itr);
		else
			this->UnregisterEvent(ET_MiscEvent, *itr);
	}
}

void Drawable::RegisterEvent(EventType type,EventListener *component)
{ 
	auto itr = std::find(eventRegistry[type].begin(), eventRegistry[type].end(), component);

	if (itr == eventRegistry[type].end())
	{
		eventRegistry[type].push_back(component);
	}
}

void Drawable::UnregisterEvent(EventType type, EventListener *component)
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
