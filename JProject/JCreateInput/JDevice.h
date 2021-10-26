#pragma once
#include"JStd.h"

class JDevice
{
public:
	ID3D11Device* m_pd3dDevice;
	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
	IDXGIFactory* m_pGIFactory;
	ID3D11DeviceContext* m_pImmediateContext;
	D3D11_VIEWPORT m_ViewPort;
	D3D_DRIVER_TYPE m_driverType;
	D3D_DRIVER_TYPE m_DriverType;
	D3D_FEATURE_LEVEL m_FeatureLevel;

public:
	HRESULT CreateDevice();
	HRESULT CreateGIFactory();
	HRESULT CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight);
	HRESULT SetRenderTargetView();
	HRESULT SetViewPort();
	bool CleanupDevice();



};

