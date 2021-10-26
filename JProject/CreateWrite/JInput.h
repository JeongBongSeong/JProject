#pragma once
#include"JStd.h"
//키보드, 마우스 -> 윈도우API 사용

enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};

class JInput : public JSingleton<JInput>
{
	friend class JSingleton<JInput>;
private:
	DWORD m_dwKeyState[256];
	POINT m_ptPos;
public:
	DWORD	GetKey(DWORD dwKey);

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

private:
	JInput();
public:
	~JInput();
};


#define g_Input JInput::Get()