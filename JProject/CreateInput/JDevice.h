#pragma once
#include"JStd.h"
#include<assert.h>
#include<dxgi.h>
#include<d3d11.h>
#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"dxgi.lib")

class JDevice
{
public:
	ID3D11Device			*m_pd3dDevice;			// 디바이스 객체
	IDXGISwapChain			*m_pSwapChain;			// 스왑체인 객체
	ID3D11RenderTargetView	*m_pRenderTargetView;	// 메인 랜더타켓 뷰
	IDXGIFactory			*m_pGIFactory;			// DXGI 객체
	ID3D11DeviceContext		*m_pImmediateContext;	// 디바이스 컨텍스트
	D3D11_VIEWPORT			m_ViewPort;				// 뷰포트 
	D3D_DRIVER_TYPE         m_driverType;			// 디바이스 타입( 디폴트:하드웨어 가속 )
	D3D_DRIVER_TYPE			m_DriverType;			// 디바이스 타입
	D3D_FEATURE_LEVEL       m_FeatureLevel;			// DirectX의 기능수준

public:
	bool		SetDevice();
	HRESULT		CreateDevice();
	HRESULT		CreateGIFactory();
	HRESULT		CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeigh);

	HRESULT		SetRenderTargetView();
	HRESULT		SetViewPort();
	bool		CleanupDevice();
};

