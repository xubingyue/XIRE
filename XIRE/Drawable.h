#pragma once
  
#include "Callable.h"
#include <vector>
#include "Primitive.hpp"
#include <map>

NS_Begin(XIRE) 

class Graphics;

class XIREAPI Drawable : public Callable
{
public:

	Drawable();

	virtual ~Drawable();

	virtual void Draw(Graphics* g); 
	 
protected:

	std::vector<SwPrimitive> primitives;
};

NS_End(XIRE)
