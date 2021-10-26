#pragma once
#include"JStd.h"
class JTimer
{
private:
	LARGE_INTEGER m_Frequency; // 주파수
	LARGE_INTEGER m_Current; //현재시간
	LARGE_INTEGER m_Frame;//

	int m_iTmpCounter;
public:
	int m_iFPS;
	float m_fSecPerFrame;
	float m_fGameTimer;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	JTimer();

};

