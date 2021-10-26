#pragma once
#include<windows.h>
#include < tchar.h >
#include <string>
#include <map>
#include <vector>
#include <list>
#pragma comment(lib,"TEngineCore.lib")

extern float g_fSecPerFrame;
extern HWND  g_hWnd;
extern RECT  g_rtClient;

#define	GAME_START int APIENTRY wWinMain(_In_		HINSTANCE	hInstance,	_In_opt_	HINSTANCE	hPrevInstance,	_In_		LPWSTR		lpCmdLine,	_In_		int			nCmdShow){	Sample gSample;
#define	GAME_RUN(s,x,y) gSample.InitWindows(hInstance, nCmdShow, L#s,x,y);	gSample.Run();	return 1;}
#define	GAME_SIMPLE_RUN(s) gSample.InitWindows(hInstance, nCmdShow, L#s);	gSample.Run();	return 1;}
#define	GAMECORE(s,x,y) GAME_START GAME_RUN(s,x,y)
#define	GAME_SIMPLE_CORE(s) GAME_START GAME_SIMPLE_RUN(s)
template<class T>
class TSingleton
{
public:
	static T& Get()
	{
		static T theSingle;
		return theSingle;
	}
};