#pragma once

#include"JWindow.h"
#include"JTimer.h"
#include"JInput.h"
#include"JWrite.h"

class JCore : public JWindow
{
public:
	JTimer m_Timer;
	//JInput m_Input;
	JWrite m_Write;
	bool m_bDebugText = false;
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

