#pragma once

#include"JWindow.h"
#include"JTimer.h"
#include"JInput.h"
#include"JWrite.h"
#include"JCamera.h"

#include "JShape.h"
#include "JCamera.h"
#include "JDxState.h"

class JCore : public JWindow
{
public:
	JTimer m_Timer;
	//JInput m_Input;
	JWrite m_Write;
	JDebugCamera		m_Camera;
	//JBoxShape			m_BoxObj[2];
	bool m_bDebugText = false;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();
public:
	bool CameraFrame();
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)override;
public:
	bool GameInit() override;
	bool GameRun() override;
	bool GameFrame();
	bool GameRender();
	bool GameRelease() override;
};

