#pragma once

#include "XIRE_Afx.h"

NS_Begin(XIRE) 
NS_Begin(core)

struct XIREAPI Vector2i
{
public:
	union
	{
		int m[2];
		struct { int x; int y; };
	};

	Vector2i()
	{
	}

	Vector2i(const int * const p)
	{
		x = p[0];
		y = p[1];
	}

	Vector2i(const int px, const int py)
	{
		x = px;
		y = py;
	} 
};

NS_End(core) 
NS_End(XIRE)