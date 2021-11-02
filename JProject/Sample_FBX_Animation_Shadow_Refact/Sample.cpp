#define _CRT_SECURE_NO_WARNINGS
#include "Sample.h"


//bool	Sample::PreRender()
//{
//	JCore::PreRender();
//	m_pImmediateContext->ClearDepthStencilView(
//		m_pDepthStencilView,
//		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//	return true;
//}
//HRESULT Sample::CreateDepthStencilView()
//{
//	HRESULT hr = S_OK;
//	DXGI_SWAP_CHAIN_DESC Desc;
//	m_pSwapChain->GetDesc(&Desc);
//	// 1)텍스처 생성 : 깊이,스텐실 값을 저장하는 버퍼용
//	ID3D11Texture2D* pTexture = nullptr;
//	D3D11_TEXTURE2D_DESC td;
//	td.Width = Desc.BufferDesc.Width;
//	td.Height = Desc.BufferDesc.Height;
//	td.MipLevels = 1;
//	td.ArraySize = 1;
//	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
//	td.Usage = D3D11_USAGE_DEFAULT;
//	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//	td.CPUAccessFlags = 0;
//	td.MiscFlags = 0;
//	td.SampleDesc.Count = 1;
//	td.SampleDesc.Quality = 0;
//	hr = m_pd3dDevice->CreateTexture2D(&td, NULL, &pTexture);
//	if (FAILED(hr))
//	{
//		return hr;
//	}
//	D3D11_DEPTH_STENCIL_VIEW_DESC svd;
//	ZeroMemory(&svd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
//	svd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
//	svd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
//	svd.Texture2D.MipSlice = 0;
//	hr = m_pd3dDevice->CreateDepthStencilView(pTexture, &svd,
//		&m_pDepthStencilView);
//	if (FAILED(hr))
//	{
//		return hr;
//	}
//	SAFE_RELEASE(pTexture);
//
//	m_pImmediateContext->OMSetRenderTargets(1,
//		&m_pRenderTargetView, m_pDepthStencilView);
//	return hr;
//}
HRESULT Sample::CreateDepthStencilState()
{
	HRESULT hr = S_OK;
	D3D11_DEPTH_STENCIL_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_DEPTH_STENCIL_DESC));
	sd.DepthEnable = TRUE;
	sd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	sd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	hr = m_pd3dDevice->CreateDepthStencilState(&sd, &m_pDsvState);
	if (FAILED(hr))
	{
		return hr;
	}
	m_pImmediateContext->OMSetDepthStencilState(m_pDsvState, 0x01);
	return hr;
}


bool		Sample::Init()
{
	m_MiniMap.Create(L"../../data/shader/PlaneVS.txt", L"../../data/shader/PlanePS.txt", "VS", "PS",L"");
	m_MapObj.Create(L"../../data/shader/PlaneVS.txt", L"../../data/shader/PlanePS.txt","VS", "PS", L"../../data/bitmap1.bmp");

	TMatrix matWorld, matScale;
	D3DXMatrixRotationX(&matWorld, XM_PI / 2.0f);
	D3DXMatrixScaling(&matScale, 100.0f, 100.0f, 100.0f);
	m_MapObj.m_matWorld = matScale * matWorld;
	m_Rt.Create(4096, 4096);

	//
	TPlane  p;
	p.x = 0.0f;
	p.y = 1.0f;
	p.z = 0.0f;
	p.w = -0.1f;
		
	m_vLight.x = 100.0f;
	m_vLight.y = 100.0f;
	m_vLight.z = 100.0f;
	m_vLight.w = 0.0f;
	D3DXMatrixShadow(&m_matShadow, &m_vLight, &p);
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
		if (FAILED(hr)) return hr;
		PSBlob->Release();
	}


	CreateDepthStencilState();

	//
	/*float pos = 350.0f;
	m_vMovePos.x = pos;
	
	m_vMovePos.z = -pos;
	m_FbxObjA.m_matWorld._41 = pos;
	
	m_FbxObjA.m_matWorld._43 = -pos;*/
	//
	CStopwatch stop;
	//m_FbxObj.LoadObject("../../data/object/ship.fbx","../../data/shader/DefaultShader.hlsl");
	m_FbxObjA.LoadObject("../../data/object/man.fbx", "../../data/shader/CharacterShader.hlsl");
	stop.Output(L"a");
	//m_FbxObjB.LoadObject("../../data/object/Turret.fbx");
	//m_Texture.LoadTexture(L"../../data/wireframe.dds");
	//m_FbxObj.LoadObject("../../data/box.fbx");
	m_Camera.CreateViewMatrix(TVector3(0, 0, -100), TVector3(0, 0, 0));
	m_Camera.CreateProjMatrix(1.0f, 1000.0f, XM_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);

	//JMapInfo info{
	//   64 + 1,
	//   64 + 1, 0,0, 0,
	//   10.0f
	//};
	//if (!m_Map.Load(info, L"..\\..\\data\\shader\\Shader.hlsl", "VS", "PS"))
	//{
	//	return false;
	//}
	//m_Quadtree.Build(&m_Map);
	return true;
}
bool		Sample::Frame() 
{
	//m_Map.Frame();
	float fSpeed = 0.01f;

	if (g_Input.GetKey('Q') >= KEY_PUSH)
	{
		m_fNum -= fSpeed / 10;
		D3DXMatrixRotationY(&m_FbxObjA.m_matWorld, m_fNum);
	}
	if (g_Input.GetKey('E') >= KEY_PUSH)
	{
		m_fNum += fSpeed / 10;
		D3DXMatrixRotationY(&m_FbxObjA.m_matWorld, m_fNum);

	}
	TVector3 vLook;
	vLook.x = m_FbxObjA.m_matWorld._31;
	vLook.y = m_FbxObjA.m_matWorld._32;
	vLook.z = m_FbxObjA.m_matWorld._33;
	vLook.Normalize();

	if (g_Input.GetKey(VK_F4) == KEY_PUSH)
	{
		m_FbxObjA.m_bAnimPlay = !m_FbxObjA.m_bAnimPlay;
	}
	if (g_Input.GetKey(VK_UP) >= KEY_PUSH)
	{
		m_vMovePos -= fSpeed * vLook;
	}
	if (g_Input.GetKey(VK_DOWN) >= KEY_PUSH)
	{
		m_vMovePos += vLook * fSpeed;
	}

	TVector3 vSide;
	vSide.x = m_FbxObjA.m_matWorld._11;
	vSide.y = m_FbxObjA.m_matWorld._12;
	vSide.z = m_FbxObjA.m_matWorld._13;
	vSide.Normalize();

	if (g_Input.GetKey(VK_LEFT) >= KEY_PUSH)
	{
		m_vMovePos += fSpeed * vSide;
	}
	if (g_Input.GetKey(VK_RIGHT) >= KEY_PUSH)
	{
		m_vMovePos -= fSpeed * vSide;
	}
	

	m_FbxObjA.Frame();
	return true;
}
bool		Sample::Render()
{
	//m_pImmediateContext->RSSetState(m_pRSSolid);

	if (m_Rt.Begin(m_pImmediateContext))
	{
		m_FbxObjA.SetMatrix(&m_FbxObjA.m_matWorld,
			&m_Camera.m_matView, &m_Camera.m_matProj);
		m_FbxObjA.SetPixelShader(m_pPSShadow);
		m_FbxObjA.Render(m_pImmediateContext);
		m_Rt.End(m_pImmediateContext);
	}

	m_MapObj.SetMatrix(&m_MapObj.m_matWorld, &m_Camera.m_matView, &m_Camera.m_matProj);
	m_MapObj.Render(m_pImmediateContext);

	m_MiniMap.SetMatrix(nullptr, nullptr, nullptr);
	m_MiniMap.PreRender(m_pImmediateContext);
	m_pImmediateContext->PSSetShaderResources(
		1, 1, &m_Rt.m_pTextureSRV);
	m_MiniMap.PostRender(m_pImmediateContext,
		m_MiniMap.m_iNumIndex);

	m_FbxObjA.m_matWorld._41 = m_vMovePos.x;
	m_FbxObjA.m_matWorld._42 = m_vMovePos.y;
	m_FbxObjA.m_matWorld._43 = m_vMovePos.z;
	m_FbxObjA.SetMatrix(&m_FbxObjA.m_matWorld, &m_Camera.m_matView, &m_Camera.m_matProj);
	m_FbxObjA.SetPixelShader(nullptr);
	m_FbxObjA.Render(m_pImmediateContext);

	m_matShadow._41 = m_vLight.x * m_FbxObjA.m_matWorld._41;
	m_matShadow._42 = m_vLight.y * m_FbxObjA.m_matWorld._42;
	m_matShadow._43 = m_vLight.z * m_FbxObjA.m_matWorld._43;
	
	m_matShadow._11 = m_vLight.x * m_FbxObjA.m_matWorld._11;
	m_matShadow._13 = m_vLight.z * m_FbxObjA.m_matWorld._13;
	m_matShadow._31 = m_vLight.x * m_FbxObjA.m_matWorld._31;
	m_matShadow._33 = m_vLight.z * m_FbxObjA.m_matWorld._33;

	
	m_FbxObjA.SetMatrix(&m_matShadow, &m_Camera.m_matView, &m_Camera.m_matProj);
	m_FbxObjA.SetPixelShader(m_pPSShadow);
	m_FbxObjA.Render(m_pImmediateContext);

	if (g_Input.GetKey(VK_F5) == KEY_PUSH)
	{
		m_Rt.Save(m_pImmediateContext, L"frame.bmp");
	}
	return true;
	//m_Map.SetMatrix(
	//	nullptr,
	//	&m_Camera.m_matView,
	//	&m_Camera.m_matProj);

	////m_Map.Render(m_pImmediateContext);
	//
	//m_Quadtree.Render(m_pImmediateContext, m_Camera.m_vCameraPos);
	////m_FbxObj.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
	////m_FbxObj.Render(m_pImmediateContext);
	//

	//m_FbxObjA.m_matWorld._41 = m_vMovePos.x;
	//m_FbxObjA.m_matWorld._42 = m_vMovePos.y;
	//m_FbxObjA.m_matWorld._43 = m_vMovePos.z;
	//m_FbxObjA.SetMatrix(&m_FbxObjA.m_matWorld, &m_Camera.m_matView, &m_Camera.m_matProj);
	//m_FbxObjA.SetPixelShader(nullptr);
	//m_FbxObjA.Render(m_pImmediateContext);

	//m_matShadow._41 = m_vLight.x * m_FbxObjA.m_matWorld._41;
	//m_matShadow._42 = m_vLight.y * m_FbxObjA.m_matWorld._42;
	//m_matShadow._43 = m_vLight.z * m_FbxObjA.m_matWorld._43;
	//
	//m_matShadow._11 = m_vLight.x * m_FbxObjA.m_matWorld._11;
	//m_matShadow._13 = m_vLight.z * m_FbxObjA.m_matWorld._13;
	//m_matShadow._31 = m_vLight.x * m_FbxObjA.m_matWorld._31;
	//m_matShadow._33 = m_vLight.z * m_FbxObjA.m_matWorld._33;

	//
	//m_FbxObjA.SetMatrix(&m_matShadow, &m_Camera.m_matView, &m_Camera.m_matProj);
	//m_FbxObjA.SetPixelShader(m_pPSShadow);
	//m_FbxObjA.Render(m_pImmediateContext);
	////m_FbxObjB.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
	////m_FbxObjB.Render(m_pImmediateContext);
	//return true;
}


bool		Sample::Release()
{
	m_Map.Release();
	SAFE_RELEASE(m_pDsvState);
	SAFE_RELEASE(m_pDepthStencilView);
	//m_FbxObj.Release();
	m_FbxObjA.Release();
	m_FbxObjB.Release();
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