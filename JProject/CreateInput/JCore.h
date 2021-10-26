#pragma once
#include"JWindow.h"

#include"JTimer.h"
#include"JInput.h"

class JCore : public JWindow
{
public:
	JTimer m_Timer;

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

