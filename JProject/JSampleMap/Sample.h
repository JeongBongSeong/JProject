#pragma once
#include"JCore.h"
#include"JVector.h"
#include"JMap.h"
#include "JCamera.h"
#include "JShape.h"

class Sample : public JCore
{
public:
	JMap				m_MapObj;
	JDebugCamera		m_Camera;
	JBoxShape			m_BoxObj[2];
	float m_fYaw = 0.0f;
	float m_fPitch = 0.0f;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)override;
public:
	Sample();
	virtual ~Sample();
};

