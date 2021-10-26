#pragma once
#include<windows.h>
#include"JDevice.h"


class JWindow : public JDevice
{
public:
	RECT m_rtWindow;
	RECT m_rtClient;

	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	bool		m_bGameRun;

public:
	bool InitWindows(HINSTANCE hInstance, int nCmdShow, const TCHAR* strWIndowTitle);

	virtual LRESULT			MsgProc(HWND, UINT, WPARAM, LPARAM);

public:
	bool			Run();
	virtual bool	GameInit();
	virtual bool	GameRun();
	virtual bool	GameRelease();

public:
	JWindow(void);

};

