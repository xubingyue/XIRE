#pragma once

#include "XIRE_Afx.h"
#include "ObjLoader.h"
#include "Memfile.hpp"
#include "Primitive.hpp"
#include "RenderBase.h"

NS_Begin(XIRE)

struct XIREAPI SwMesh : public Drawable
{
public: 

	SwMesh(String filename)
	{
		RegisterEventType(ET_KeyboardEvent | ET_MouseEvent);

		primitives.clear();
		LoadFromObj(filename);
	}

	void LoadFromObj(String filepath)
	{
		ObjLoader loader;
		io::Memfile memfile;
		loader.LoadGeometryFromObj(filepath, primitives);

		return;

		std::string s_filepath = WStringToString(filepath);

		memfile.Open(s_filepath.c_str()); 

		loader.LoadGeometryFromObj(StringToWString(memfile.Data()), primitives); 
	}
 
	std::wstring StringToWString(const std::string &str)
	{
		std::wstring wstr(str.length(), L' ');
		std::copy(str.begin(), str.end(), wstr.begin());
		return wstr;
	}
	 
	std::string WStringToString(const std::wstring &wstr)
	{
		std::string str(wstr.length(), ' ');
		std::copy(wstr.begin(), wstr.end(), str.begin());
		return str;
	}

};

NS_End(XIRE)