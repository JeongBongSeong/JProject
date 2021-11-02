#define _CRT_SECURE_NO_WARNINGS
#include "Sample.h"

//HRESULT Sample::CreateDepthStencilState()
//{
//	HRESULT hr = S_OK;
//	D3D11_DEPTH_STENCIL_DESC sd;
//	ZeroMemory(&sd, sizeof(D3D11_DEPTH_STENCIL_DESC));
//	sd.DepthEnable = TRUE;
//	sd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
//	sd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
//	hr = m_pd3dDevice->CreateDepthStencilState(&sd, &m_pDsvState);
//	if (FAILED(hr))
//	{
//		return hr;
//	}
//	m_pImmediateContext->OMSetDepthStencilState(m_pDsvState, 0x01);
//	return hr;
//}


bool		Sample::Init()
{
	m_matTex._11 = 0.5f; m_matTex._22 = -0.5f;
	m_matTex._41 = 0.5f; m_matTex._42 = 0.5f;
	m_Light1.Set(TVector3(150, 150, 150), TVector3(0, 0, 0));

	//
	m_MiniMap.Create(L"../../data/shader/PlaneVS.txt", L"../../data/shader/PlanePS.txt", "VS", "PS",L"");
	m_MapObj.Create(L"../../data/shader/ProjectionShadow.txt", L"../../data/shader/ProjectionShadow.txt","VS", "PS", L"../../data/object/Chrome1.bmp");

	TMatrix matWorld, matScale;
	D3DXMatrixRotationX(&matWorld, XM_PI / 2.0f);
	D3DXMatrixScaling(&matScale, 1000.0f, 1000.0f, 1000.0f);

	m_MapObj.m_matWorld = matScale * matWorld;
	m_Rt.Create(4096, 4096);

	//
	ID3DBlob* PSBlob = nullptr;
	PSBlob = JModel::LoadShaderBlob(L"../../data/shader/CharacterShader.hlsl", "PSShadow", "ps_5_0");
	if(PSBlob != nullptr)
	{
		HRESULT hr = S_OK;
		hr = g_pd3dDevice->CreatePixelShader(
			PSBlob->GetBufferPointer(),
			PSBlob->GetBufferSize(),
			NULL, &m_pPSShadow);
		if (FAILED(hr)) return false;
		PSBlob->Release();
	}

	m_FbxCharacter.LoadObject("../../data/object/man.fbx", "../../data/shader/CharacterShader.hlsl");

	m_Camera.CreateViewMatrix(TVector3(0, 0, -100), TVector3(0, 0, 0));
	m_Camera.CreateProjMatrix(1.0f, 1000.0f, XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);


	return true;
}
bool		Sample::Frame() 
{

	if (g_Input.GetKey(VK_F4) == KEY_PUSH)
	{
		m_FbxCharacter.m_bAnimPlay = !m_FbxCharacter.m_bAnimPlay;
	}

	float fSpeed = 0.01f;

	if (g_Input.GetKey('Q') >= KEY_PUSH)
	{
		m_fNum -= fSpeed / 10;
		m_FbxCharacter.m_matWorld._11 = cos(m_fNum);
		m_FbxCharacter.m_matWorld._13 = -sin(m_fNum);
		m_FbxCharacter.m_matWorld._31 = sin(m_fNum);
		m_FbxCharacter.m_matWorld._33 = cos(m_fNum);
		//D3DXMatrixRotationY(&m_FbxCharacter.m_matWorld, m_fNum);
	}
	if (g_Input.GetKey('E') >= KEY_PUSH)
	{
		m_fNum += fSpeed / 10;
		D3DXMatrixRotationY(&m_FbxCharacter.m_matWorld, m_fNum);

	}
	TVector3 vLook;
	vLook.x = m_FbxCharacter.m_matWorld._31;
	vLook.y = m_FbxCharacter.m_matWorld._32;
	vLook.z = m_FbxCharacter.m_matWorld._33;
	vLook.Normalize();

	
	if (g_Input.GetKey(VK_UP) >= KEY_PUSH)
	{
		m_vMovePos -= fSpeed * vLook;
	}
	if (g_Input.GetKey(VK_DOWN) >= KEY_PUSH)
	{
		m_vMovePos += vLook * fSpeed;
	}

	TVector3 vSide;
	vSide.x = m_FbxCharacter.m_matWorld._11;
	vSide.y = m_FbxCharacter.m_matWorld._12;
	vSide.z = m_FbxCharacter.m_matWorld._13;
	vSide.Normalize();

	if (g_Input.GetKey(VK_LEFT) >= KEY_PUSH)
	{
		m_vMovePos += fSpeed * vSide;
	}
	if (g_Input.GetKey(VK_RIGHT) >= KEY_PUSH)
	{
		m_vMovePos -= fSpeed * vSide;
	}
	if (g_Input.GetKey(VK_F6) == KEY_PUSH)
	{
		m_bChangeCamera = !m_bChangeCamera;
	}
	m_FbxCharacter.m_matWorld._41 = m_vMovePos.x;
	m_FbxCharacter.m_matWorld._42 = m_vMovePos.y;
	m_FbxCharacter.m_matWorld._43 = m_vMovePos.z;
	
	m_FbxCharacter.Frame();
	m_Light1.Frame();
	m_ShadowCB.g_matShadow1 = m_Light1.m_matView * m_Light1.m_matProj * m_matTex;


	return true;
}
bool		Sample::Render()
{
	//ApplyRS(m_pImmediateContext, JDxState::g_pRSWireFrame);

	if (m_Rt.Begin(m_pImmediateContext))
	{
		m_FbxCharacter.SetMatrix(&m_FbxCharacter.m_matWorld,
			&m_Light1.m_matView, &m_Light1.m_matProj);
		m_FbxCharacter.SetPixelShader(m_pPSShadow);
		m_FbxCharacter.Render(m_pImmediateContext);
		m_Rt.End(m_pImmediateContext);
	}
	ApplySS(m_pImmediateContext, JDxState::g_pClampSS, 1);

	m_MapObj.m_cbData.matNormal = m_ShadowCB.g_matShadow1;
	if (m_bChangeCamera)
		m_MapObj.SetMatrix(&m_MapObj.m_matWorld, &m_Camera.m_matView, &m_Camera.m_matProj);
	else
		m_MapObj.SetMatrix(&m_MapObj.m_matWorld, &m_Light1.m_matView, &m_Light1.m_matProj);
	m_pImmediateContext->PSSetShaderResources(1, 1, &m_Rt.m_pTextureSRV);
	m_MapObj.Render(m_pImmediateContext);
	

	m_MiniMap.SetMatrix(nullptr, nullptr, nullptr);
	m_MiniMap.PreRender(m_pImmediateContext);
	m_pImmediateContext->PSSetShaderResources(0, 1, &m_Rt.m_pTextureSRV);
	m_MiniMap.PostRender(m_pImmediateContext,m_MiniMap.m_iNumIndex);

	if (m_bChangeCamera)
		m_FbxCharacter.SetMatrix(&m_FbxCharacter.m_matWorld, &m_Camera.m_matView, &m_Camera.m_matProj);
	else
		m_FbxCharacter.SetMatrix(&m_FbxCharacter.m_matWorld, &m_Light1.m_matView, &m_Light1.m_matProj);
	m_FbxCharacter.SetPixelShader(nullptr);
	m_FbxCharacter.Render(m_pImmediateContext);


	if (g_Input.GetKey(VK_F5) == KEY_PUSH)
	{
		m_Rt.Save(m_pImmediateContext, L"frame.bmp");
	}
	return true;
}


bool		Sample::Release()
{
	m_MapObj.Release();
	m_MiniMap.Release();
	m_Rt.Release();
	m_FbxCharacter.Release();
	//m_Texture.Release();
	SAFE_RELEASE(m_pPSShadow);
	return true;
}
Sample::Sample()
{
}
Sample::~Sample()
{
}






int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Sample game;
	//윈도우 레지스터 등록
	game.InitWindows(hInstance, nCmdShow, L"JGame");

	game.Run();
	return 0;

}