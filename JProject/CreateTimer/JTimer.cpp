#include "JTimer.h"
#include <tchar.h>
#include <stdio.h>
float g_fSecPerFrame = 0.0f;

bool JTimer::Init()
{
	QueryPerformanceCounter(&m_Frame);
	
	return false;
}

bool JTimer::Frame()
{
	QueryPerformanceCounter(&m_Current);

	// (현재시간 - 경과시간 ) / 고정 시간
	m_fSecPerFrame =	static_cast<float>(m_Current.QuadPart - m_Frame.QuadPart)
						/ static_cast<float>(m_Frequency.QuadPart);

	g_fSecPerFrame = m_fSecPerFrame;
	static float fpsTime = 0.0f;
	m_iTmpCounter++;
	fpsTime += m_fSecPerFrame;

	if (fpsTime >= 1.0f)
	{
		m_iFPS = m_iTmpCounter;
		m_iTmpCounter = 0;
		fpsTime -= 1.0f;
		//std::wstring time = ;
		TCHAR timerString[MAX_PATH] = { 0, };

		_stprintf_s(timerString, L"\nFPS=%d:Timer=%10.4f",m_iFPS, m_fGameTimer);
		OutputDebugString(timerString);
	}

	// 누적타임
	m_fGameTimer += m_fSecPerFrame;
	


	m_Frame = m_Current;

	return true;
}

bool JTimer::Render()
{
	
	return true;
}

bool JTimer::Release()
{
	return false;
}

JTimer::JTimer()
{
	m_iFPS = 0;
	m_iTmpCounter = 0;
	m_fSecPerFrame = 0.0f;
	m_fGameTimer = 0.0f;
	QueryPerformanceFrequency(&m_Frequency);
}
