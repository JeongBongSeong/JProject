#pragma once

#include"JDevice.h"

class JWindow : public JDevice
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

public:
	bool Run();
	//가상 함수를 이용하여 자식 클래스에서 사용할 예정
	virtual bool GameInit();
	virtual bool GameRun();
	virtual bool GameRelease();
	
public:
	JWindow();

};

