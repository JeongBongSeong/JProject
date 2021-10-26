#include "JCore.h"

bool JCore::GameInit()
{
	JDevice::SetDevice();
	
	m_Timer.Init();
	g_Input.Init();
	m_Write.Init();

	IDXGISurface1* m_pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&m_pBackBuffer);
	m_Write.CreateDeviceResources(m_pBackBuffer);


	if (m_pBackBuffer) m_pBackBuffer->Release();

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
	m_Timer.Frame();
	g_Input.Frame();
	m_Write.Frame();
	if (g_Input.GetKey('1') == KEY_PUSH)
	{
		m_bDebugText = !m_bDebugText;
	}
	Frame();
	return true;
}

bool JCore::GameRender()
{
	PreRender();
	m_Timer.Render();
	g_Input.Render();
	m_Write.Render();
	if (m_bDebugText)
	{
		RECT  rt = { 0, 0, 1280, 768 };
		m_Write.DrawText(rt, m_Timer.m_szTimerString,
			D2D1::ColorF(0, 0, 1, 1));
	}
	Render();
	PostRender();
	return true;
}

bool JCore::GameRelease()
{
	Release();
	m_Timer.Release();
	g_Input.Release();
	m_Write.Release();


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
	float ClearColor[4] = { 0.0f, 0.2f, 0.3f, 1.0f };
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
