#include "SwSurface.h"
#include "MemoryPool.h"

NS_Using(XIRE)

SwSurface::SwSurface(String _name, int _width, int _height, int _bpp)
	:width(_width),height(_height),bpp(_bpp)
{ 
	Name = _name;

	pitch = bpp * width;

	data = (U8*)MemoryPool::Get()._mm_malloc_16byte(pitch * height, 16);
	memset(data, 0, pitch*height);
}


SwSurface::~SwSurface()
{
	if (data != NULL)
	{
		MemoryPool::Get()._mm_free_16byte(data);
	}
}
