#include "JCore.h"
bool JCore::GameInit()
{
	if (FAILED(CreateDevice()))
	{
		return false;
	}
	if (FAILED(CreateGIFactory()))
	{
		return false;
	}
	if (FAILED(CreateSwapChain(m_hWnd, m_rtClient.right, m_rtClient.bottom)))
	{
		return false;
	}
	if (FAILED(SetRenderTargetView()))
	{
		return false;
	}
	if (FAILED(SetViewPort()))
	{
		return false;
	}
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
	Frame();
	return true;
}

bool JCore::GameRender()
{
	PreRender();
	Render();
	PostRender();
	return true;
}

bool JCore::GameRelease()
{
	Release();

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
	float ClearColor[4] = { 255.0f, 255.0f, 0.0f, 1.0f };
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
