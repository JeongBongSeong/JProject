#include "JDevice.h"

HRESULT JDevice::CreateDevice()
{
	HRESULT hr = S_OK;
	UINT createDeviceFlags = 0;
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
	};
	UINT numDriverTypes = sizeof(driverTypes[0]) / sizeof(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
	};
	UINT numFeatureLevels = sizeof(featureLevels[0]) / sizeof(featureLevels);

	m_driverType = driverTypes[0];
	m_FeatureLevel = featureLevels[0];
	//D3D11_CREATE_DEVICE_SINGLETHREADED
	hr = D3D11CreateDevice(
		NULL, m_driverType, NULL, createDeviceFlags,
		featureLevels, numFeatureLevels,
		D3D11_SDK_VERSION,&m_pd3dDevice,&m_FeatureLevel,
		&m_pImmediateContext);
	return hr;

}
HRESULT JDevice::CreateGIFactory()
{
	HRESULT hr = S_OK;
	
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory),
		(void**)(&m_pGIFactory));
	return hr;
}
HRESULT JDevice::CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight)
{
	HRESULT hr;

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	

	//백버퍼 세팅
	sd.BufferDesc.Width = iWidth;
	sd.BufferDesc.Height = iHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//멀티 샘플링
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	hr = m_pGIFactory->CreateSwapChain(
		m_pd3dDevice, &sd, &m_pSwapChain);
	
	return hr;
}
HRESULT JDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	if (FAILED(hr))
	{
		pBackBuffer->Release();
		return hr;
	}
	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	if (FAILED(hr))
	{
		pBackBuffer->Release();
		return hr;
	}
	pBackBuffer->Release();
		
	m_pImmediateContext->OMSetRenderTargets(1,
		&m_pRenderTargetView,
		NULL);

	return hr;
}
HRESULT JDevice::SetViewPort()
{
	HRESULT hr = S_OK;
	DXGI_SWAP_CHAIN_DESC desc;
	m_pSwapChain->GetDesc(&desc);

	m_ViewPort.Width = desc.BufferDesc.Width;
	m_ViewPort.Height = desc.BufferDesc.Height;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_pImmediateContext->RSSetViewports(1,&m_ViewPort);


	return hr;
}
bool JDevice::CleanupDevice()
{
	if (m_pImmediateContext) { m_pImmediateContext->ClearState(); }
	if (m_pd3dDevice) { m_pd3dDevice->Release(); }
	if (m_pSwapChain) { m_pSwapChain->Release(); }
	if (m_pRenderTargetView) { m_pRenderTargetView->Release(); }
	if (m_pGIFactory) { m_pGIFactory->Release(); }
	if (m_pImmediateContext) { m_pImmediateContext->Release(); }
	m_pImmediateContext		= nullptr;
	m_pd3dDevice			= nullptr;
	m_pSwapChain			= nullptr;
	m_pRenderTargetView		= nullptr;
	m_pGIFactory			= nullptr;
	return true;
}