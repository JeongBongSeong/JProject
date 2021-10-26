#include "JCore.h"

bool JCore::GameInit()
{
	
	JDevice::SetDevice();
	// TODO : create Timer
	m_Timer.Init();
	g_Input.Init();
	Init();
	return true;
}

bool JCore::GameRun()
{
	if (!GameFrame()) return false;
	if (!GameRender()) return false;
	return true;
}

bool JCore::GameFrame()
{
	// TODO : Frame Timer
	m_Timer.Frame();
	g_Input.Frame();
	Frame();
	return true;
}

bool JCore::GameRender()
{
	PreRender();
	// TODO : create Timer
	m_Timer.Render();
	g_Input.Render();
	Render();
	PostRender();
	return true;
}

bool JCore::GameRelease()
{
	Release();
	// TODO : create Timer
	m_Timer.Release();
	g_Input.Release();
	CleanupDevice();
	return true;
}

bool JCore::Init()
{
	return true;
}

bool JCore::Frame()
{
	return true;
}

bool JCore::PreRender()
{
	//srand((unsigned int)time(NULL));
	float ClearColor[4] = { 1,1,1,1 };
	//float ClearColor[4] = { static_cast<float>(rand() % 1000) / 1000, static_cast<float>(rand() % 1000) / 1000, static_cast<float>(rand() % 1000) / 1000, static_cast<float>(rand() % 1000) / 1000 };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);

	return true;
}

bool JCore::Render()
{
	return true;
}

bool JCore::PostRender()
{
	assert(m_pSwapChain);
	m_pSwapChain->Present(0, 0);
	return true;
}

bool JCore::Release()
{
	return true;
}
