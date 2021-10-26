#pragma once
#include"JWindow.h"
#include"JDevice.h"
class JCore : public JWindow
{
private:
	// 오버라이드를 이용하여 재정의 하여 호출한다.
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

