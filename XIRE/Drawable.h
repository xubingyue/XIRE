#pragma once
  
#include "EventListener.h"
#include <vector>
#include "Primitive.hpp"
#include <map>

NS_Begin(XIRE) 

class Graphics;

class XIREAPI Drawable : public EventListener
{
public:

	Drawable();

	virtual ~Drawable();

	virtual void Draw(Graphics* g); 

	virtual void AddChild(Drawable *drawable);

	std::vector<Drawable*> ChildContainer;

protected:

	//���ɵ�ǰ����������˶����ע����¼�
	void UpdateEventRegistry();

	void RegisterEvent(EventType type, EventListener *component);

	void UnregisterEvent(EventType type, EventListener *component);
	 
protected:

	std::vector<SwPrimitive> primitives;

	EventRegistry eventRegistry;

};

NS_End(XIRE)
