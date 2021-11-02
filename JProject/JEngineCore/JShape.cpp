#include "JShape.h"

bool JBoxShape::Create(std::wstring vsfilename, std::wstring psfilename, std::string vsEntry, std::string psEntry)
{
    if (CreateVertexData())
    {
        LoadObject(L"..\\..\\data\\script\\ObjectData.txt");
        CreateConstantBuffer();
        CreateVertexBuffer();
        //CreateIndexBuffer();
        LoadShader(vsfilename, psfilename, vsEntry, psEntry);
        CreateVertexLayout();

    }
    return true;
}

bool JBoxShape::Render(ID3D11DeviceContext* pContext)
{
    if (PreRender(pContext) == false) return false;
    if (PostRender(pContext) == false) return false;
    return true;

}
bool JBoxShape::PostRender(ID3D11DeviceContext* pContext)
{
    pContext->IASetPrimitiveTopology(
       D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    pContext->Draw(this->m_pVertexList.size(),0);
    return true;
}



bool JPlaneShape::CreateVertexData()
{
    m_pVertexList.resize(4);

    m_pVertexList[0].pos = TVector3(-1.0f, 1.0f, 0.0f);
    m_pVertexList[0].normal = TVector3(0.0f, 0.0f, -1.0f);
    m_pVertexList[0].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_pVertexList[0].tex = TVector2(0.0f, 0.0f);

    m_pVertexList[1].pos = TVector3(1.0f, 1.0f, 0.0f);
    m_pVertexList[1].normal = TVector3(0.0f, 0.0f, -1.0f);
    m_pVertexList[1].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_pVertexList[1].tex = TVector2(1.0f, 0.0f);


    m_pVertexList[2].pos = TVector3(-1.0f, -1.0f, 0.0f);
    m_pVertexList[2].normal = TVector3(0.0f, 0.0f, -1.0f);
    m_pVertexList[2].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_pVertexList[2].tex = TVector2(0.0f, 1.0f);


    m_pVertexList[3].pos = TVector3(1.0f, -1.0f, 0.0f);
    m_pVertexList[3].normal = TVector3(0.0f, 0.0f, -1.0f);
    m_pVertexList[3].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_pVertexList[3].tex = TVector2(1.0f, 1.0f);
    return true;
}
bool JPlaneShape::CreateIndexData()
{
    m_pIndexList.resize(6);
    m_pIndexList[0] = 0;
    m_pIndexList[1] = 1;
    m_pIndexList[2] = 2;
    m_pIndexList[3] = 2;
    m_pIndexList[4] = 1;
    m_pIndexList[5] = 3;
    return true;
}