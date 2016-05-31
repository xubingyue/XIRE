#pragma once

#include "XIRE_Afx.h"

#include "Primitive.hpp"
#include <vector>
#include <sstream>

#include "Vectorf2.hpp"
#include "Vectorf3.hpp"
#include "Vectorf4.h"

#include "Vertex.hpp"

NS_Begin(XIRE)

class XIREAPI ObjLoader
{
	XIRE_ALIGN struct CacheEntry
	{
		U32 index;
		CacheEntry* pNext;
	};

public:
	ObjLoader();

	~ObjLoader();

	bool LoadGeometryFromObj(const String &meshData, std::vector<SwPrimitive>& primitives);

	void CreateMeshInternal(std::vector<SwPrimitive>& primitives);

	void DeleteCache();

	void ClearData();

	WORD AddVertex(U32 hash, SwVertexP3N3T2* pVertex);

protected:

	std::vector<core::Vectorf4> Positions;
	std::vector<core::Vectorf2> TexCoords;
	std::vector<core::Vectorf3> Normals;

	std::vector<CacheEntry*> m_VertexCache;   // Hashtable cache for locating duplicate vertices
	std::vector<SwVertexP3N3T2> m_Vertices;     // Filled and copied to the vertex buffer
	std::vector<U32> m_Indices;       // Filled and copied to the index buffer
	std::vector<U32> m_Attributes;    // Filled and copied to the attribute buffer

	bool	m_bIsLoaded; 
	CacheEntry* nullCache; 
};

NS_End(XIRE)