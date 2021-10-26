#pragma once
#include "JStd.h"

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
	DWORD GetKey(DWORD dwKey);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	JInput();
public:
	~JInput();
};

#define g_Input JInput::Get()