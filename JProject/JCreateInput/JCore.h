#pragma once

#include"JWindow.h"
#include"JTimer.h"
#include"JInput.h"



class JCore : public JWindow
{
public:
	JTimer m_Timer;
//	JInput m_Input;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();

public:
	bool GameInit() override;
	bool GameRun() override;
	bool GameFrame();
	bool GameRender();
	bool GameRelease() override;
};

