#pragma once
#include<windows.h>
#include<tchar.h>
#include<string>
#include<map>
#include<vector>
#include<list>

//#pragma comment(lib,"JEngineCore.lib")
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