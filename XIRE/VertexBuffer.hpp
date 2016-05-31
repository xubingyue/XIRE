#pragma once

#include "XIRE_Afx.h"
#include "MemoryPool.h"
#include "Vectorf4.h" 
#include "Vertex.hpp"

NS_Begin(XIRE)

XIRE_ALIGN
struct XIREAPI SwVertexBuffer
{
	U8 *data;
	U32 size;
	U32 count;

	void *userData;

	SwVertexBuffer()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(SwVertexBuffer)); 
	}

	void setData(void *srcData, U32 index)
	{
		if (index < count)
		{
			memcpy(data + size*index, srcData, size);
		}
	}

	static SwVertexBuffer* Allocate(U32 elementSize, U32 count)
	{
		SwVertexBuffer* vb = new SwVertexBuffer;
		vb->size = elementSize;
		vb->count = count;
		vb->data = (U8*)(MemoryPool::Get()._mm_malloc_16byte(vb->size * count, 16));

		return vb;
	}

	void Print()
	{ 
		for (int i = 0; i < this->count; ++i)
		{
			SwVertexP3N3T2 *data = (SwVertexP3N3T2 *)(this->data+i*this->size);

			//tranform Model Space into World Space
			core::Vectorf3 normal = data->normal;
			core::Vectorf4 pos = data->pos;
			core::Vectorf2 tex = data->texcoord;
 
			printf("%d %.4f %.4f %.4f %.4f\n", sizeof(SwVertexP3N3T2), pos.x, pos.y, pos.z, pos.w);
			//translate every vertex into world space  
		}
	}
}; 

NS_End(XIRE)