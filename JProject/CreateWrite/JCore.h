#pragma once
#include"JWindow.h"
#include"JDevice.h"
#include"JTimer.h"
#include"JInput.h"
#include"JWrite.h"
class JCore : public JWindow
{
public:
	JTimer m_Timer;
	JWrite m_Write;
	bool		m_bDebugText = false;

private:
	bool	GameInit()			override;
	bool	GameRun()			override;
	bool	GameFrame();
	bool	GameRender();
	bool	GameRelease()		override;

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	PreRender();
	virtual bool	Render();
	virtual bool	PostRender();
	virtual bool	Release();
public:
};

