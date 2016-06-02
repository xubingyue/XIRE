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

