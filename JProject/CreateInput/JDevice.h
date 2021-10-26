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
	ID3D11Device			*m_pd3dDevice;			// ����̽� ��ü
	IDXGISwapChain			*m_pSwapChain;			// ����ü�� ��ü
	ID3D11RenderTargetView	*m_pRenderTargetView;	// ���� ����Ÿ�� ��
	IDXGIFactory			*m_pGIFactory;			// DXGI ��ü
	ID3D11DeviceContext		*m_pImmediateContext;	// ����̽� ���ؽ�Ʈ
	D3D11_VIEWPORT			m_ViewPort;				// ����Ʈ 
	D3D_DRIVER_TYPE         m_driverType;			// ����̽� Ÿ��( ����Ʈ:�ϵ���� ���� )
	D3D_DRIVER_TYPE			m_DriverType;			// ����̽� Ÿ��
	D3D_FEATURE_LEVEL       m_FeatureLevel;			// DirectX�� ��ɼ���

public:
	bool		SetDevice();
	HRESULT		CreateDevice();
	HRESULT		CreateGIFactory();
	HRESULT		CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeigh);

	HRESULT		SetRenderTargetView();
	HRESULT		SetViewPort();
	bool		CleanupDevice();
};

