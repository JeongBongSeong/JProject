#include "JModel.h"

void		JModel::SetMatrix(TMatrix* pMatWorld, TMatrix* pMatView, TMatrix* pMatProj)
{
    if (pMatWorld != nullptr)
    {
        m_cbData.matWorld = pMatWorld->Transpose();
    }
    if (pMatView != nullptr)
    {
        m_cbData.matView = pMatView->Transpose();
    }
    if (pMatProj != nullptr)
    {
        m_cbData.matProj = pMatProj->Transpose();
    }
}

bool  JModel::LoadObject(std::wstring filename)
{
    FILE* fp = nullptr;
    _tfopen_s(&fp, filename.c_str(), _T("rt"));
    if (fp == NULL)
    {
        return false;
    }
    TCHAR buffer[256] = { 0, };
    int iVersion = 0;
    _fgetts(buffer, 256, fp);
    TCHAR tmp[256] = { 0, };
    _stscanf_s(buffer, _T("%s%d"), tmp, _countof(tmp), &iVersion);

    int iNumVertex = 0;
    _fgetts(buffer, 256, fp);
    _stscanf_s(buffer, _T("%d"), &iNumVertex);

    int index = 0;
    for (int iLine = 0; iLine < iNumVertex; iLine++)
    {
        PNCT_VERTEX v;
        _fgetts(buffer, 256, fp);
        _stscanf_s(buffer, _T("%d %f %f %f %f %f %f %f"),
            &index,
            &v.pos.x, &v.pos.y, &v.pos.z,
            &v.color.x, &v.color.y, &v.color.z, &v.color.w);
        m_pVertexList.push_back(v);
    }
    fclose(fp);
    return true;
}
HRESULT JModel::CreateVertexBuffer()
{
    HRESULT hr = S_OK;
    // 좌표계
    // 로컬 -> 월드 -> 투영 -> 화면
    // x = -1.0 ~ 1.0
    // y = -1.0 ~ 1.0
    // z = 0

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = m_iVertexSize * m_pVertexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
    data.pSysMem = &m_pVertexList.at(0);
    hr = g_pd3dDevice->CreateBuffer(&bd, &data, &m_pVertexBuffer);
    if (FAILED(hr)) return hr;
    return hr;
}

HRESULT JModel::CreateIndexBuffer()
{
    HRESULT hr = S_OK;
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = sizeof(DWORD) * m_pIndexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
    data.pSysMem = &m_pIndexList.at(0);
    hr = g_pd3dDevice->CreateBuffer(&bd, &data, &m_pIndexBuffer);
    if (FAILED(hr)) return hr;

    m_iNumIndex = m_pIndexList.size();
    return hr;
}

HRESULT JModel::CreateConstantBuffer()
{
    HRESULT hr = S_OK;
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = sizeof(CB_DATA);
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
    data.pSysMem = &m_cbData;
    hr = g_pd3dDevice->CreateBuffer(&bd, &data, &m_pConstantBuffer);
    if (FAILED(hr)) return hr;
    return hr;
}

HRESULT JModel::CreateVertexLayout()
{
    HRESULT hr = S_OK;
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    UINT numLayout = sizeof(layout) / sizeof(layout[0]);

    hr = g_pd3dDevice->CreateInputLayout(layout, numLayout,
        m_pVSBlob->GetBufferPointer(),
        m_pVSBlob->GetBufferSize(),
        &m_pVertexLayout);
    if (FAILED(hr)) return hr;
    m_pVSBlob->Release();
    return hr;
}
HRESULT JModel::CreateVertexShader(std::wstring strFilename, std::string vsEntry)
{
    HRESULT hr = S_OK;
    ID3DBlob* error = nullptr;
    hr = D3DCompileFromFile(
        strFilename.c_str(),
        nullptr,
        nullptr,
        vsEntry.c_str(),
        "vs_5_0",
        0,
        0,
        &m_pVSBlob,
        nullptr);
    if (FAILED(hr)) { return hr; }

    hr = g_pd3dDevice->CreateVertexShader(
        m_pVSBlob->GetBufferPointer(),
        m_pVSBlob->GetBufferSize(),
        NULL, &m_pVS);
    if (FAILED(hr)) return hr;
    return hr;
}
HRESULT JModel::CreatePixelShader(std::wstring strFilename, std::string psEntry)
{
    HRESULT hr = S_OK;
    ID3DBlob* PSBlob = nullptr;
    hr = D3DCompileFromFile(
        strFilename.c_str(),
        nullptr,
        nullptr,
        psEntry.c_str(),
        "ps_5_0",
        0,
        0,
        &PSBlob,
        nullptr);
    if (FAILED(hr)){return hr;}

    hr = g_pd3dDevice->CreatePixelShader(
        PSBlob->GetBufferPointer(),
        PSBlob->GetBufferSize(),
        NULL, &m_pPS);
    if (FAILED(hr)) return hr;
    PSBlob->Release();
    return hr;
}







bool JModel::CreateVertexData()
{
    if (m_pVertexList.size() > 0)
    {
        return true;
    }
    return false;
}

bool JModel::CreateIndexData()
{
    if (m_pIndexList.size() > 0)
    {
        return true;
    }
    return false;
}


bool JModel::Init()
{
    return true;
}

bool JModel::Create(std::wstring filename,std::string vsEntry, std::string psEntry)
{
    //LoadObject(L"..\\..\\data\\script\\ObjectData.txt");
    CreateConstantBuffer();
    if (CreateVertexData())
    {
        CreateVertexBuffer();
    }

    if (CreateIndexData())
    {
        CreateIndexBuffer();        
    }

    if (SUCCEEDED(CreateVertexShader(filename, vsEntry)))
    {
        if (SUCCEEDED(CreatePixelShader(filename, psEntry)))
        {
            if (SUCCEEDED(CreateVertexLayout()))
            {
                return true;
            }
        }
    }
    return false;
}
bool JModel::Frame()
{
    m_cbData.vValue.z = g_fGameTimer;
    return true;
}

bool JModel::PreRender(ID3D11DeviceContext* pContext)
{
    if (m_pVertexList.size() <= 0) return true;

    pContext->UpdateSubresource(
        m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
    pContext->VSSetConstantBuffers(
        0, 1, &m_pConstantBuffer);
    pContext->VSSetShader(m_pVS, NULL, 0);
    pContext->PSSetShader(m_pPS, NULL, 0);
    pContext->IASetInputLayout(m_pVertexLayout);
    UINT pStrides = m_iVertexSize;
    UINT pOffsets = 0;
    pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer,
        &pStrides, &pOffsets);
    pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    return true;
}

bool JModel::Render(ID3D11DeviceContext* pContext)
{
    if (PreRender(pContext) == false) return false;
    if (PostRender(pContext, m_iNumIndex) == false) return false;
    return true;
    
}

bool JModel::PostRender(ID3D11DeviceContext* pContext, UINT iNumIndex)
{

    if (iNumIndex > 0)
    {
        pContext->DrawIndexed(iNumIndex, 0, 0);
    }
    else
    {
        pContext->Draw(m_pVertexList.size(), 0);
    }
    return true;
}

bool JModel::Release()
{

    SAFE_RELEASE(m_pVertexBuffer);
    SAFE_RELEASE(m_pVertexLayout);
    SAFE_RELEASE(m_pIndexBuffer);
    SAFE_RELEASE(m_pConstantBuffer);
    SAFE_RELEASE(m_pVS);
    SAFE_RELEASE(m_pPS);
    return false;
}


JModel::JModel()
{
    SAFE_ZERO(m_pVertexBuffer);
    SAFE_ZERO(m_pIndexBuffer);
    SAFE_ZERO(m_pVertexLayout);
    SAFE_ZERO(m_pConstantBuffer);
    SAFE_ZERO(m_pVS);
    SAFE_ZERO(m_pPS);
    m_iVertexSize = sizeof(PNCT_VERTEX);
    m_iNumIndex = 0;
}
JModel::~JModel()
{
}