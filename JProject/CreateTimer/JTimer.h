#pragma once
#include"JStd.h"
#include <string>
//1.
//2.
//3.
//
//
class JTimer
{
private:
	LARGE_INTEGER	m_Frequency;	//주파수
	LARGE_INTEGER	m_Current;
	LARGE_INTEGER	m_Frame;
	
	int				m_iTmpCounter;	//프레임마다 초기화되는 변수
public:
	int		m_iFPS;
	float	m_fSecPerFrame;
	float	m_fGameTimer;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	JTimer();
};

