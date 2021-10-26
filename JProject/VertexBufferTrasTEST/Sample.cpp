#define _CRT_SECURE_NO_WARNINGS
#include "Sample.h"
#include "JVector.h"
Sample::Sample()
{
    m_pVertexBuffer = nullptr;
    m_pVertexLayout = nullptr;
    m_pVS = nullptr;
    m_pPS = nullptr;
}
HRESULT Sample::CreateVertexBuffer()
{
    HRESULT hr = S_OK;
    // 좌표계
    // 로컬 - > 월드 -> 투영 -> 화면
    // x = -1.0 ~ 1.0
    // y = -1.0 ~ 1.0
    // z = 0

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = sizeof(SimpleVertex) * m_VertexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
    data.pSysMem = &m_VertexList.at(0);
    hr = g_pd3dDevice->CreateBuffer(&bd,&data,&m_pVertexBuffer);
    if (FAILED(hr)) return hr;
    return hr;
}
HRESULT Sample::CreateVertexLayout()
{
    HRESULT hr = S_OK;
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    UINT numLayout = sizeof(layout) / sizeof(layout[0]);
    hr = g_pd3dDevice->CreateInputLayout(layout, numLayout,
        m_pVSBlob->GetBufferPointer(),
        m_pVSBlob->GetBufferSize(),
        &m_pVertexLayout);
    if (FAILED(hr)) return hr;
    return hr;
}
HRESULT Sample::LoadShader()
{
    HRESULT hr = S_OK;
    ID3DBlob* error = nullptr;
    hr = D3DCompileFromFile(
        L"VertexShader.txt",
        nullptr,
        nullptr,
        "VS",
        "vs_5_0",
        0,
        0,
        &m_pVSBlob,
        &error);
    if (FAILED(hr))
    {
        MessageBoxA(NULL,
            (char*)error->GetBufferPointer(),
            "error", MB_OK);
        return hr;
    }

    hr = g_pd3dDevice->CreateVertexShader(
        m_pVSBlob->GetBufferPointer(),
        m_pVSBlob->GetBufferSize(),
        NULL, &m_pVS);
    if (FAILED(hr)) return hr;
    ID3DBlob* PSBlob = nullptr;
    hr = D3DCompileFromFile(
        L"PixelShader.txt",
        nullptr,
        nullptr,
        "PS",
        "ps_5_0",
        0,
        0,
        &PSBlob,
        &error);
    if (FAILED(hr))
    {
        MessageBoxA(NULL,
            (char*)error->GetBufferPointer(),
            "error", MB_OK);
        return hr;
    }

    hr = g_pd3dDevice->CreatePixelShader(
        PSBlob->GetBufferPointer(),
        PSBlob->GetBufferSize(),
        NULL, &m_pPS);
    if (FAILED(hr)) return hr;
    PSBlob->Release();
    return hr;
}

template <typename OutputIterator>
void Sample::Tokenize(const std::wstring& text, const std::wstring& delimiters, OutputIterator first)
{
    size_t start, stop, n = text.length();

    for (start = text.find_first_not_of(delimiters); 0 <= start && start < n;
        start = text.find_first_not_of(delimiters, stop + 1))
    {
        stop = text.find_first_of(delimiters, start);
        if (stop < 0 || stop > n)
        {
            stop = n;
        }
        *first++ = text.substr(start, stop - start);
    }
}

bool	Sample::LoadObject(std::wstring filename)
{
    FILE* fp = nullptr;
    _tfopen_s(&fp, filename.c_str(), _T("rt"));
    if (fp == NULL)
    {
        return false;
    }

    TCHAR data[256] = { 0, };

    TCHAR buffer[256] = { 0, };
    int iVersion = 0;
    _fgetts(buffer, 256, fp);
    TCHAR tmp[256] = { 0, };
    _stscanf_s(buffer, _T("%s%d"), tmp, _countof(tmp), &iVersion);

    int index = 0;

    
    std::vector<std::wstring>	ListTokens;
    _fgetts(buffer, 256, fp);
    _stscanf_s(buffer, _T("%d %s"), &index, data, _countof(data));
    
    std::wstring sentence = data;
    Tokenize(sentence, L",", std::back_inserter(ListTokens));
    int iMaxCnt = (int)ListTokens.size();
    
    for (int iLine = 0; iLine < iMaxCnt; iLine++)
    {
        
        
            //&v.pos.x, &v.pos.y, &v.pos.z,
            //&v.color.x, &v.color.y, &v.color.z, &v.color.w);
        UINT x = (UINT)(_tstoi(ListTokens[iLine].c_str()));
        SimpleVertex v = test(x, iLine % 3);
        
        m_VertexList.push_back(v);
    }
    
    fclose(fp);
    return true;



}
SimpleVertex Sample::test( UINT x, UINT y)
{
    SimpleVertex v;
    if (x == 0)
    {
        v.pos.x = -1.0f;
        v.pos.y = 1.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 1)
    {
        v.pos.x = -0.5f;
        v.pos.y = 1.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 2)
    {
        v.pos.x = 0.0f;
        v.pos.y = 1.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 3)
    {
        v.pos.x = 0.5f;
        v.pos.y = 1.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 4)
    {
        v.pos.x = 1.0f;
        v.pos.y = 1.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 5)
    {
        v.pos.x = -1.0f;
        v.pos.y = 0.5f;
        v.pos.z = 0.5f;
    }
    else if (x == 9)
    {
        v.pos.x = 1.0f;
        v.pos.y = 0.5f;
        v.pos.z = 0.5f;
    }
    else if (x == 10)
    {
        v.pos.x = -1.0f;
        v.pos.y = 0.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 11)
    {
        v.pos.x = -0.5f;
        v.pos.y = 0.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 12)
    {
        v.pos.x = 0.0f;
        v.pos.y = 0.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 13)
    {
        v.pos.x = 0.5f;
        v.pos.y = 0.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 14)
    {
        v.pos.x = 1.0f;
        v.pos.y = 0.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 15)
    {
        v.pos.x = -1.0f;
        v.pos.y = -0.5f;
        v.pos.z = 0.5f;
    }
    else if (x == 19)
    {
        v.pos.x = 1.0f;
        v.pos.y = -0.5f;
        v.pos.z = 0.5f;
    }
    else if (x == 20)
    {
        v.pos.x = -1.0f;
        v.pos.y = -1.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 21)
    {
        v.pos.x = -0.5f;
        v.pos.y = -1.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 22)
    {
        v.pos.x = 0.0f;
        v.pos.y = -1.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 23)
    {
        v.pos.x = 0.5f;
        v.pos.y = -1.0f;
        v.pos.z = 0.5f;
    }
    else if (x == 24)
    {
        v.pos.x = 1.0f;
        v.pos.y = -1.0f;
        v.pos.z = 0.5f;
    }


    if (y == 0)
    {
        v.color.x = 1.0f;
        v.color.y = 0.0f;
        v.color.z = 0.0f;
        v.color.w = 1.0f;
    }
    else if (y == 1)
    {
        v.color.x = 0.0f;
        v.color.y = 1.0f;
        v.color.z = 0.0f;
        v.color.w = 1.0f;
    }
    else if (y == 2)
    {
        v.color.x = 0.0f;
        v.color.y = 0.0f;
        v.color.z = 1.0f;
        v.color.w = 1.0f;
    }
    return v;
}
bool Sample::Init()
{

    LoadObject(L"ObjectData.txt");
    CreateVertexBuffer();
    LoadShader();
    CreateVertexLayout();

    return true;
}
bool Sample::Frame()
{
    return true;
}
bool Sample::Render()
{
    m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    UINT pStrides = sizeof(SimpleVertex);
    UINT pOffsets = 0;
    m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer,
        &pStrides, &pOffsets);
    m_pImmediateContext->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pImmediateContext->Draw(m_VertexList.size(), 0);
    return true;
}
bool Sample::Release()
{
    m_pVertexBuffer->Release();
    m_pVertexLayout->Release();
    m_pVS->Release();
    m_pPS->Release();
    return true;
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