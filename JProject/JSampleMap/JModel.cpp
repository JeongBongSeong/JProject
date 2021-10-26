#include "JModel.h"

void		JModel::SetMatrix(
    TMatrix* pMatWorld,
    TMatrix* pMatView, TMatrix* pMatProj)
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

HRESULT JModel::CreateVertexBuffer()
{
    HRESULT hr = S_OK;

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = sizeof(SimpleVertex) * m_pVertexList.size();
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


bool	JModel::CreateVertexData()
{
    if(m_pVertexList.size() > 0)
    {
        return true;
    }
    return false;
}
bool	JModel::CreateIndexData()
{
    if (m_pIndexList.size() > 0)
    {
        return true;
    }
    return false;
}


HRESULT JModel::CreateVertexLayout()
{
    HRESULT hr = S_OK;
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    //UINT numLayout = sizeof(layout) / sizeof(layout[0]);
    hr = g_pd3dDevice->CreateInputLayout(layout, _countof(layout),
        m_pVSBlob->GetBufferPointer(),
        m_pVSBlob->GetBufferSize(),
        &m_pVertexLayout);
    if (FAILED(hr)) return hr;

    m_pVSBlob->Release();
    return hr;
}

HRESULT JModel::CreateVertexShader(std::wstring filename,
    std::string entry)
{
    HRESULT hr = S_OK;

    hr = D3DCompileFromFile(
        filename.c_str(),
        nullptr,
        nullptr,
        entry.c_str(),
        "vs_5_0",
        0,
        0,
        &m_pVSBlob,
        NULL);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = g_pd3dDevice->CreateVertexShader(
        m_pVSBlob->GetBufferPointer(),
        m_pVSBlob->GetBufferSize(),
        NULL, &m_pVS);
    if (FAILED(hr)) return hr;
    return hr;
}

HRESULT JModel::CreatePixelShader(std::wstring filename,
    std::string entry)
{
    HRESULT hr = S_OK;
    ID3DBlob* PSBlob = nullptr;
    hr = D3DCompileFromFile(
        filename.c_str(),
        nullptr,
        nullptr,
        entry.c_str(),
        "ps_5_0",
        0,
        0,
        &PSBlob,
        NULL);
    if (FAILED(hr))
    {
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


bool	JModel::LoadObject(std::wstring filename)
{
    FILE* fp = nullptr;
    _tfopen_s(&fp, filename.c_str(), _T("rt"));
    if (fp == nullptr)
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
        SimpleVertex v;
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


bool JModel::Init()
{
    return false;
}
bool JModel::Load(std::wstring filename,
    std::string vsEntry, std::string psEntry)
{
    if(CreateIndexData() && CreateVertexData())
    {
        CreateVertexBuffer();
        CreateIndexBuffer();
        CreateConstantBuffer();

        CreateVertexShader(filename, vsEntry);
        CreatePixelShader(filename, psEntry);

        CreateVertexLayout();

        LoadObject(L"ObjectData.txt");
    }
    return true;
}

bool JModel::Frame()
{
    return true;
}


bool JModel::Render(ID3D11DeviceContext* pContext)
{
    pContext->UpdateSubresource(
        m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
    pContext->VSSetConstantBuffers(
        0, 1, &m_pConstantBuffer);
    pContext->VSSetShader(m_pVS, NULL, 0);
    pContext->PSSetShader(m_pPS, NULL, 0);
    pContext->IASetInputLayout(m_pVertexLayout);
    UINT pStrides = sizeof(SimpleVertex);
    UINT pOffsets = 0;
    pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer,
        &pStrides, &pOffsets);
    pContext->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    pContext->Draw(m_pVertexList.size(), 0);
    return false;
}

bool JModel::Release()
{
    m_pVertexBuffer->Release();
    m_pVertexLayout->Release();
    m_pConstantBuffer->Release();
    m_pIndexBuffer->Release();
    m_pVS->Release();
    m_pPS->Release();
    return false;
}



JModel::JModel()
{
    m_pVertexBuffer = nullptr;
    m_pVertexLayout = nullptr;
    m_pIndexBuffer = nullptr;
    m_pConstantBuffer = nullptr;
    m_pVS = nullptr;
    m_pPS = nullptr;

}