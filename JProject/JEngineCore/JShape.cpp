#include "JShape.h"

bool JBoxShape::Create(std::wstring filename, std::string vsEntry, std::string psEntry)
{
    if (CreateVertexData())
    {
        LoadObject(L"..\\..\\data\\script\\ObjectData.txt");
        CreateConstantBuffer();
        CreateVertexBuffer();
        //CreateIndexBuffer();
        CreateVertexShader(filename, vsEntry);
        CreatePixelShader(filename, psEntry);
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