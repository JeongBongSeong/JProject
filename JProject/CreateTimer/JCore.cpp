#include "JCore.h"
#include<iostream>
bool JCore::GameInit()
{
	if (FAILED(CreateGIFactory()))
	{
		return false;
	}
	if (FAILED(CreateDevice()))
	{
		return false;
	}
	if (FAILED(CreateSwapChain(m_hWnd,
		m_rtClient.right,
		m_rtClient.bottom)))
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

	// TODO : create Timer
	m_Timer.Init();

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
	Frame();
	return true;
}

bool JCore::GameRender()
{
	PreRender();
	// TODO : create Timer
	m_Timer.Render();
	Render();
	PostRender();
	return true;
}

bool JCore::GameRelease()
{
	Release();
	// TODO : create Timer
	m_Timer.Release();
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
	float ClearColor[4] = { static_cast<float>(rand() % 1000)/1000, static_cast<float>(rand() % 1000)/1000, static_cast<float>(rand() % 1000)/1000, static_cast<float>(rand() % 1000) / 1000 };
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
