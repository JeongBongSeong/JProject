#pragma once
#include"JCore.h"
#include "JShape.h"
#include "JCamera.h"
#include "JMap.h"



class Sample : public JCore
{
	
	JBoxShape			m_BoxObj[2];
	JMap				m_Map;
	JDebugCamera		m_Camera;
	float m_fYaw = 0.0f;
	float m_fPitch = 0.0f;
public:
	bool Init()		override;
	bool Frame()	override;
	bool Render()	override;
	bool Release()	override;
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)override;
public:
	Sample();
	virtual ~Sample();

};

