#include "JCore.h"

LRESULT JCore::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return g_Input.MsgProc(hWnd, message, wParam, lParam);
}

bool JCore::GameInit()
{
	JDevice::SetDevice();
	JDxState::Init();
	m_Timer.Init();
	g_Input.Init();
	m_Write.Init();

	m_Camera.Init();
	m_Camera.CreateViewMatrix(TVector3(16, 3, -31), TVector3(16, 3, 100000));
	m_Camera.CreateProjMatrix(1.0f, 1000.0f, JBASIS_PI * 0.5f, (float)g_rtClient.right / (float)g_rtClient.bottom);


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
	CameraFrame();
	if (g_Input.GetKey('1') == KEY_PUSH)
	{
		m_bDebugText = !m_bDebugText;
	}
	
	if (!JDxState::g_pCurrentRS)
	{
		JDxState::g_pCurrentRS = JDxState::g_pRSSolid;
	}
	else if (g_Input.GetKey(VK_F2) >= KEY_PUSH)
	{
		ApplyRS(m_pImmediateContext, JDxState::g_pRSWireFrame);
	}
	else if (g_Input.GetKey(VK_F3) >= KEY_PUSH)
	{
		ApplyRS(m_pImmediateContext, JDxState::g_pRSSolid);
	}
	
	Frame();
	g_Input.m_ptBeforePos = g_Input.m_ptPos;
	return true;
}
bool JCore::CameraFrame()
{
	if (g_Input.m_bDrag && g_Input.m_ptBeforePos.x == g_Input.m_pDragDown.x)
	{
		g_Input.m_pDrag.x = 0;
	}
	if (g_Input.m_bDrag && g_Input.m_ptBeforePos.y == g_Input.m_pDragDown.y)
	{
		g_Input.m_pDrag.y = 0;
	}
	float fYaw = g_fSecPerFrame * g_Input.m_pDrag.x * 5.0f;
	float fPitch = g_fSecPerFrame * g_Input.m_pDrag.y * 5.0f;
	
	m_Camera.Update(TVector4(fYaw, fPitch, 0.0f, 0.0f));
	m_Camera.Frame();

	


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
	//


	

	/*
	m_BoxObj[0].m_matWorld._41 = -3.0f;
	m_BoxObj[1].m_matWorld._41 = 3.0f;

	for (int iObj = 0; iObj < 2; iObj++)
	{
		m_BoxObj[iObj].SetMatrix(
			&m_BoxObj[iObj].m_matWorld,
			&m_Camera.m_matView,
			&m_Camera.m_matProj);
		m_BoxObj[iObj].Render(m_pImmediateContext);
	}
	*/

	//
	Render();
	PostRender();
	return true;
}

bool JCore::GameRelease()
{
	Release();
	JDxState::Release();
	m_Timer.Release();
	g_Input.Release();
	m_Write.Release();
	m_Camera.Release();

	
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
	float ClearColor[4] = { 0.125f, 0.5f, 0.5f, 1.0f };
	m_pImmediateContext->ClearRenderTargetView(
		m_DefaultRT.m_pRenderTargetView, ClearColor);
	m_pImmediateContext->ClearDepthStencilView(
		m_DefaultDS.m_pDepthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->OMSetRenderTargets(1,
		&m_DefaultRT.m_pRenderTargetView, m_DefaultDS.m_pDepthStencilView);

	ApplyDSS(m_pImmediateContext, JDxState::g_pLessEqualDSS);
	ApplySS(m_pImmediateContext, JDxState::g_pWrapSS, 0);
	ApplyRS(m_pImmediateContext, JDxState::g_pCurrentRS);
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
	m_Camera.Release();
	
	return true;
}
