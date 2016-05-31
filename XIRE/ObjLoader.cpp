#include "ObjLoader.h"
#include <fstream>

NS_Using(XIRE)
 
ObjLoader::ObjLoader()
{

}

ObjLoader::~ObjLoader()
{

}

bool ObjLoader::LoadGeometryFromObj(const String& meshData, std::vector<SwPrimitive>& primitives)
{ 
	std::wfstream fin(meshData);
	String strCommand; //[256] = { 0 };
	//std::wstringstream fin(meshData);

	if (!fin)
	{
		return false;
	}

	bool flushFace = false;
	String currMtlName;

	int vertexIndexStart = 0;
	int normalIndexStart = 0;
	int texcoordIndexStart = 0;

	for (; ;)
	{
		fin >> strCommand;
		if (!fin)
		{
			break;
		}

		//if (0 == _tcscmp(strCommand, S("#")))
		if(0 == strCommand.compare(S("#")))
		{
			//Comment
		}
		else if (0 == strCommand.compare(S("g")))
		{
			// 物体
			flushFace = true;
		}
		else if (0 == strCommand.compare(S("usemtl")))
		{
			// 物体材质
			fin >> currMtlName;
		}
		else if (0 == strCommand.compare(S("mtllib")))
		{
			// 物体材质
		}
		else if (0 == strCommand.compare(S("v")))
		{
			if (flushFace)
			{
				flushFace = false;

				//CreateMesh
				CreateMeshInternal(primitives);

				//primitives.back().material = gEnv->resourceMgr->LoadMaterial(currMtlName.c_str());
			}

			// Vertex Position
			float x, y, z;
			fin >> x >> y >> z;

			Positions.push_back(core::Vectorf4(x, y, z, 1));

			// for3DsMax, 加入点列，随后方便走面的时候，输入normal和tc
		}
		else if (0 == strCommand.compare(_T("vt")))
		{
			// Vertex TexCoord
			float u, v;
			fin >> u >> v;
			// for3DsMax, 加入点列，随后方便走面的时候，输入normal和tc
			TexCoords.push_back(core::Vectorf2(u, 1 - v));
		}
		else if (0 == strCommand.compare(_T("vn")))
		{
			// Vertex Normal
			float x, y, z;
			fin >> x >> y >> z;
			Normals.push_back(core::Vectorf3(x, y, z));
		}
		else if (0 == strCommand.compare(_T("f")))
		{
			// Face
			int iPosition, iTexCoord, iNormal;
			SwVertexP3N3T2 vertex;
			U16	dwIndex[3];
			for (U32 iFace = 0; iFace < 3; iFace++)
			{
				memset(&vertex, 0, sizeof(SwVertexP3N3T2));

				// OBJ format uses 1-based arrays
				fin >> iPosition;
				iPosition = abs(iPosition);
				vertex.pos = Positions[iPosition - 1];

				if ('/' == fin.peek())
				{
					fin.ignore();

					if ('/' != fin.peek())
					{
						// Optional texture coordinate
						fin >> iTexCoord;
						iTexCoord = abs(iTexCoord);
						vertex.texcoord = TexCoords[iTexCoord - 1];

					}

					if ('/' == fin.peek())
					{
						fin.ignore();

						// Optional vertex normal
						fin >> iNormal;
						iNormal = abs(iNormal);
						vertex.normal = Normals[iNormal - 1];
					}
				}

				dwIndex[iFace] = AddVertex(iPosition, &vertex);
			}
			// gkEngine, Add Indice
			m_Indices.push_back(dwIndex[0]);
			m_Indices.push_back(dwIndex[1]);
			m_Indices.push_back(dwIndex[2]);
		}
		else
		{
			// Unimplemented or unrecognized command
		}

		fin.ignore(1000, '\n');
	}

	if (flushFace)
	{
		flushFace = false;

		// CreateMesh
		CreateMeshInternal(primitives);
		//primitives.back().material = gEnv->resourceMgr->LoadMaterial(currMtlName.c_str());
	}

	return true;
}

WORD ObjLoader::AddVertex(U32 hash, SwVertexP3N3T2* pVertex)
{
	// If this vertex doesn't already exist in the Vertices list, create a new entry.
	// Add the index of the vertex to the Indices list.
	bool bFoundInList = false;
	WORD index = 0;

	// Since it's very slow to check every element in the vertex list, a hashtable stores
	// vertex indices according to the vertex position's index as reported by the OBJ file
	if ((U32)m_VertexCache.size() > hash)
	{
		CacheEntry* pEntry = m_VertexCache[hash];
		while (pEntry != NULL)
		{
			SwVertexP3N3T2* pCacheVertex = m_Vertices.data() + pEntry->index;

			// If this vertex is identical to the vertex already in the list, simply
			// point the index buffer to the existing vertex
			if (0 == memcmp(pVertex, pCacheVertex, sizeof(SwVertexP3N3T2)))
			{
				bFoundInList = true;
				index = pEntry->index;
				break;
			}

			pEntry = pEntry->pNext;
		}
	}

	// Vertex was not found in the list. Create a new entry, both within the Vertices list
	// and also within the hashtable cache
	if (!bFoundInList)
	{
		// Add to the Vertices list
		index = m_Vertices.size();
		m_Vertices.push_back(*pVertex);

		// Add this to the hashtable
		CacheEntry* pNewEntry = new CacheEntry;
		if (pNewEntry == NULL)
			return 0;

		pNewEntry->index = index;
		pNewEntry->pNext = NULL;

		// Grow the cache if needed
		if ((U32)m_VertexCache.size() <= hash)
		{
			m_VertexCache.resize(hash + 1, nullCache);
		}
		// 		while( ( uint32 )m_VertexCache.size() <= hash )
		// 		{
		// 			m_VertexCache.push_back( NULL );
		// 		}

		// Add to the end of the linked list
		CacheEntry* pCurEntry = m_VertexCache[hash];
		if (pCurEntry == NULL)
		{
			// This is the head element
			m_VertexCache[hash] = pNewEntry;
		}
		else
		{
			// Find the tail
			while (pCurEntry->pNext != NULL)
			{
				pCurEntry = pCurEntry->pNext;
			}

			pCurEntry->pNext = pNewEntry;
		}
	}

	return index;
}


void ObjLoader::CreateMeshInternal(std::vector<SwPrimitive>& primitives)
{ 
	DeleteCache();
	m_bIsLoaded = true;

	// Create Mesh
	SwVertexBuffer* vb = SwVertexBuffer::Allocate(sizeof(SwVertexP3N3T2), m_Vertices.size());
	SwIndexBuffer* ib =  SwIndexBuffer::Allocate(m_Indices.size());

	U32 sz = sizeof(SwVertexP3N3T2);
	U32 sz1 = sizeof(m_Vertices.front());
	memcpy(vb->data, m_Vertices.data(), sizeof(SwVertexP3N3T2) * m_Vertices.size());
	memcpy(ib->data, m_Indices.data(), sizeof(U32) * m_Indices.size());
 
	SwPrimitive primitive;
	primitive.vb = vb;
	primitive.ib = ib;
	//primitive.cachedVb = NULL;
	//vb->Print();
	primitives.push_back(primitive);

	ClearData(); 
}

void ObjLoader::DeleteCache()
{
	// Iterate through all the elements in the cache and subsequent linked lists
	/*for (U32 i = 0; i < m_VertexCache.size(); i++)
	{
		CacheEntry* pEntry = m_VertexCache[i];
		while (pEntry != NULL)
		{
			CacheEntry* pNext = pEntry->pNext;
			if (pEntry)
			{
				delete pEntry;
			}
			pEntry = pNext;
		}
	}

	m_VertexCache.clear();*/
} 

void ObjLoader::ClearData()
{
	m_Vertices.clear();     // Filled and copied to the vertex buffer
	m_Indices.clear();       // Filled and copied to the index buffer
	m_Attributes.clear();    // Filled and copied to the attribute buffer
}