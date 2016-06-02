#pragma once
  
#include "EventListener.h"
#include <vector>
#include "Primitive.hpp"

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

	std::vector<SwPrimitive> primitives;
};

NS_End(XIRE)
