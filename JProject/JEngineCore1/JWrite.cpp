#include "JWrite.h"

HRESULT JWrite::CreateDeviceResources(IDXGISurface1* pSurface)
{
    HRESULT hr = S_OK;

    UINT dpi = GetDpiForWindow(g_hWnd);
    D2D1_RENDER_TARGET_PROPERTIES props;
    props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
    props.pixelFormat.format = DXGI_FORMAT_UNKNOWN;
    props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
    props.dpiX = dpi;
    props.dpiY = dpi;
    props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
    props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

    hr = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(
        pSurface,
        &props,
        &m_pRT
    );
    if (FAILED(hr)) return hr;

    hr = m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow),
        &m_pTextBrush);

    if (FAILED(hr)) return hr;

    return hr;
}

bool	JWrite::DrawText(RECT rt, const TCHAR* text, D2D1::ColorF color)
{
    if (m_pRT)
    {
        m_pRT->BeginDraw();
        m_pRT->SetTransform(D2D1::IdentityMatrix());
        D2D1_RECT_F rect = D2D1::RectF(rt.left, rt.top, rt.right, rt.bottom);
        m_pTextBrush->SetColor(color);

        m_pRT->DrawText(text, wcslen(text),
            m_pTextFormat, rect, m_pTextBrush);
        
        m_pRT->EndDraw();
    }
    return true;
}

bool	JWrite::Init()
{
    HRESULT hr;
    hr = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pd2dFactory);
    if (FAILED(hr)) return false;

    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
    if (FAILED(hr)) return false;

    hr = m_pDWriteFactory->CreateTextFormat(
        L"",
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        20,
        L"ko-kr",
        &m_pTextFormat
    );

    if (FAILED(hr)) return false;

    return true;
}

bool	JWrite::Frame()
{
    return true;
}

bool	JWrite::Render()
{
    return true;
}

bool	JWrite::Release()
{
    if (m_pRT) m_pRT->Release();
    if (m_pd2dFactory) m_pd2dFactory->Release();
    if (m_pTextBrush) m_pTextBrush->Release();
    if (m_pDWriteFactory) m_pDWriteFactory->Release();
    if (m_pTextFormat) m_pTextFormat->Release();
    if (m_pTextLayout) m_pTextLayout->Release();
    m_pRT = nullptr;
    m_pd2dFactory = nullptr;
    m_pTextBrush = nullptr;
    m_pDWriteFactory = nullptr;
    m_pTextFormat = nullptr;
    m_pTextLayout = nullptr;

    return true;
}