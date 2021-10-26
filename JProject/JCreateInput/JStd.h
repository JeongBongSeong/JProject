#pragma once

#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>
#include <map>

#include<dxgi.h>
#include<d3d11.h>

#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"dxgi.lib")

extern float g_fSecPerFrame;
extern HWND g_hWnd;
extern RECT g_rtClient;

template<typename T>
class JSingleton 
{
public:
	static T& Get() 
	{
		static T theSingle;
		return theSingle;
	}


};






