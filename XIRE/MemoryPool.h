#pragma once

#include "XIRE_Afx.h"
#include <map> 

NS_Begin(XIRE)

class XIREAPI MemoryPool
{ 
protected:
	
	MemoryPool()
	{
	}

public:

	static MemoryPool& Get()
	{
		static MemoryPool _inst;
		return _inst;
	}

	std::map<const void*, void*> m_align_pt_mapper;

	void* _mm_malloc_16byte(size_t sz, size_t align)
	{
		if (sz <= 0) 
		{
			return NULL;
		}

		unsigned char* pSystemPointer = (unsigned char*)_mm_malloc(sz + 15, 16);
		if (NULL == pSystemPointer) 
		{
			return NULL;
		}

		size_t offset = 16 - (((unsigned int)pSystemPointer) % 16);

		m_align_pt_mapper[pSystemPointer + offset] = pSystemPointer;

		return pSystemPointer + offset;
	}

	void _mm_free_16byte(void* p)
	{
		_mm_free(m_align_pt_mapper[p]);
	}
}; 

NS_End(XIRE)