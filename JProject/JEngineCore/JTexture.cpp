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
    return true;
}

JTexture::JTexture()
{
    SAFE_ZERO(m_pTexture);
    SAFE_ZERO(m_pTextureSRV);
}