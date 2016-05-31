#pragma once

#include "XIRE_Afx.h"

#include "Mesh.hpp"
#include "Material.hpp"

NS_Begin(XIRE)

class AssetManager
{
private:

	AssetManager()
	{
		//
	}

public:

	static AssetManager* get()
	{
		static AssetManager _inst;
		return &_inst;
	}

	SwMesh *LoadMeshFromObj(String filename)
	{
		
	}
};

NS_End(XIRE)