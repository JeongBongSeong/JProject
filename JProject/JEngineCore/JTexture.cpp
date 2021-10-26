#include "JTexture.h"
bool  JTexture::LoadTexture(std::wstring texFileName)
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(
        g_pd3dDevice,
        texFileName.c_str(),
        &m_pTexture,
        &m_pTextureSRV);
    if (FAILED(hr))
    {
        hr = DirectX::CreateDDSTextureFromFile(
            g_pd3dDevice,
            texFileName.c_str(),
            &m_pTexture,
            &m_pTextureSRV);
    }
    if (FAILED(hr)) return false;
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    hr = g_pd3dDevice->CreateSamplerState(&sd, &m_pSampler);
    if (FAILED(hr)) return false;
    return true;
}
bool JTexture::Init()
{
    return false;
}
bool JTexture::Frame()
{
    return false;
}
bool JTexture::Render()
{
    return false;
}
bool JTexture::Release()
{
    SAFE_RELEASE(m_pTexture);
    SAFE_RELEASE(m_pTextureSRV);
    SAFE_RELEASE(m_pSampler);
    return true;
}

JTexture::JTexture()
{
    SAFE_ZERO(m_pTexture);
    SAFE_ZERO(m_pTextureSRV);
    SAFE_ZERO(m_pSampler);
}