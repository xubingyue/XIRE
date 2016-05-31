/** XIRE( XIRE Is a Render Engine)
 * currently developed for Windows platform only
 */

#pragma once 
 
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <tchar.h>

#include "Const.hpp"

#ifndef XIRE_IMPORT_BUILD
#define XIREAPI _declspec(dllexport)
#else
#define XIREAPI _declspec(dllimport)
#endif

#define NS_Begin(l) namespace l {
#define NS_End(l) } 
#define NS_Using(l) using namespace l;

#include <string> 

#define S(l) TEXT(l)

NS_Begin(XIRE)

#ifdef _UNICODE 
typedef wchar_t Char;
typedef wchar_t* Text;
typedef std::wstring String;
#else
typedef char Char;
typedef char* Text;
typedef std::string String;
#endif

NS_End(XIRE)

#define MakeCCallback2(callback) std::bind(##callback##, this, std::placeholders::_1, std::placeholders::_2) 
#define MakeCallback2(callback) std::bind(##callback##,std::placeholders::_1, std::placeholders::_2)

#define SafeDelete(l) {if((l)!=NULL){delete (l);(l)=NULL;}}
#define SafeRelease(l) {if((l)!=NULL){(l)->Release();(l)=NULL;}}

typedef UINT64 U64;
typedef UINT32 U32;
typedef UINT16 U16;
typedef UINT8  U8;
typedef INT64  S64;
typedef INT32  S32;
typedef INT16  S16;
typedef INT8   S8;
typedef FLOAT  F32; 

#define XIRE_ALIGN _CRT_ALIGN(16)

#define EQUAL_EPSILON 0.001f  