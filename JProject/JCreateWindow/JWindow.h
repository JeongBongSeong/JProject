#pragma once
#include <iostream>
#include <windows.h>
#include <assert.h>
#include <string.h>

class JWindow
{
public:
	RECT m_rtWindow;
	RECT m_rtClient;
public:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	bool m_bGameRun;

public:
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	bool InitWindows(HINSTANCE hInstance, int nCmdShow, const TCHAR* strTitle);
	bool Run();
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	JWindow();

};

