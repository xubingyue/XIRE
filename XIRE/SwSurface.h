#pragma once

#include "XIRE_Afx.h"
#include "Root.h"

NS_Begin(XIRE)

struct XIREAPI SwSurface : public Root
{
public:
	
	SwSurface(String _name,int _width,int _height,int _bpp);
	
	virtual ~SwSurface();

public:

	const U8* getBuffer() const { return data; }

	int getBpp() const { return bpp; }
	
	int getWidth() const { return width; }

	int getHeight() const { return height; }

	U32 Get(const U32& x, const U32& y)
	{
		U32 ret = 0;
		U8* _data = data;

		if (bpp == 3)
		{
			ret = U8BGR_2_U32(data + (bpp*x + pitch*y));
		}
		else
		{
			ret = *(U32*)(data + (bpp*x + pitch*y));
		}

		return ret;
	}

	U32 U8BGR_2_U32(U8* ch)
	{
		U32 r = (ch[0] | ch[1]<<8 | ch[2]<<16 | 0xff<<24);
		return r;
	}

	//TODO

protected:

	int width;
	int height;
	int bpp;
	int pitch;

	U8* data;
};

NS_End(XIRE)