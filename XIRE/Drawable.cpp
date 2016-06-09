#include "Drawable.h"
#include "Graphics.h"
#include <algorithm> 

NS_Using(XIRE)

Drawable::Drawable()
{ 
	RegisterEventType(ET_KeyboardEvent | ET_MouseEvent | ET_ApplicationEvent);
}

Drawable::~Drawable()
{ 
} 

void Drawable::Draw(Graphics *g)
{
	for (U32 i = 0; i < primitives.size(); ++i)
	{
		g->DrawPrimitive(&primitives[i]);
	}

	std::vector<Callable*>::iterator itr;
	for (itr = ChildContainer.begin(); itr != ChildContainer.end(); ++itr)
	{
		((Drawable*)(*itr))->Draw(g);
	}
}
 