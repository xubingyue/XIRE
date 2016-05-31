#pragma once
  
#include "EventListener.h"

NS_Begin(XIRE)

class Graphics;

class XIREAPI Drawable : public EventListener
{
public:

	Drawable();

	virtual ~Drawable();

	virtual void Draw(Graphics* g) {}
};

NS_End(XIRE)
