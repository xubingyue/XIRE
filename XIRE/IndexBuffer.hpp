#pragma once

#include "XIRE_Afx.h"

NS_Begin(XIRE)

struct XIREAPI SwIndexBuffer
{
	U32 *data;
	U32 count;
	U32 currentAddress;

	void *userData;

	SwIndexBuffer():
		data(NULL),
		count(0),
		currentAddress(0),
		userData(NULL)
	{

	}

	void setData(U32 srcData, U32 index)
	{
		if (index < count)
		{
			data[index] = srcData;
		}
	}

	void Clear()
	{
		memset(data, 0, sizeof(U32)*count);
		currentAddress = 0;
	}

	static SwIndexBuffer* Allocate(U32 count)
	{
		SwIndexBuffer* ib = new SwIndexBuffer;
		ib->data = new U32[count];
		ib->count = count; 

		return ib; 
	}
};


NS_End(XIRE)