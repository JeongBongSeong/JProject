#include "JTimer.h"

float g_fSecPerFrame = 0.0f;
float g_fGameTimer = 0.0f;

bool JTimer::Init()
{
	QueryPerformanceCounter(&m_Frame);
	return false;
}
bool JTimer::Frame()
{
	QueryPerformanceCounter(&m_Current);

	// 현재 시간 값과 초기화 때넣은 고정 시간을 뺀다
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
	}
	_stprintf_s(m_szTimerString, L"FPS=%d : Timer=%10.4f\n", m_iFPS, m_fGameTimer);
	m_fGameTimer += m_fSecPerFrame;
	g_fGameTimer = m_fGameTimer;
	m_Frame = m_Current;

	return true;
}
bool JTimer::Render()
{
	return true;
}
bool JTimer::Release()
{
	return true;
}
JTimer::JTimer()
{
	m_iFPS = 0;
	m_iTmpCounter = 0;
	m_fSecPerFrame = 0.0f;
	m_fGameTimer = 0.0f;
	QueryPerformanceFrequency(&m_Frequency);
}