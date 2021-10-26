#define _CRT_SECURE_NO_WARNINGS
#include "Sample.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    Sample game;
    //������ �������� ���
    game.InitWindows(hInstance, nCmdShow, L"JGame");

    game.Run();
    return 0;

}

bool Sample::Init()
{
    m_Texture.LoadTexture(L"../../data/bitmap1.BMP");
    JMapInfo info{
	   16 + 1,
	   16 + 1, 0,0, 0,
	   10.0f
	};
	if (m_Map.Load(info))
	{
		m_Map.Create(L"..\\..\\data\\shader\\Shader.hlsl", "VS", "PS");
	}
	m_Quadtree.Build(&m_Map);
    
    
    

    //m_BoxObj.Create(L"..\\..\\data\\shader\\Shader.hlsl", "VS", "PS");
    
    
    
    return true;
}
bool Sample::Frame()
{
    m_Map.Frame();


    //m_BoxObj.Frame();
    
    

    return true;
    
}
bool Sample::Render()
{
    m_Map.SetMatrix(
        nullptr,
        &m_Camera.m_matView,
        &m_Camera.m_matProj);

    //m_Map.Render(m_pImmediateContext);6
    m_pImmediateContext->PSSetSamplers(0, 1, &m_Texture.m_pSampler);
    m_pImmediateContext->PSSetShaderResources(1, 1, &m_Texture.m_pTextureSRV);
    m_Quadtree.Render(m_pImmediateContext, m_Camera.m_vCameraPos);
    
    /*m_BoxObj.SetMatrix(
        nullptr,
        &m_Camera.m_matView,
        &m_Camera.m_matProj);


    m_BoxObj.Render(m_pImmediateContext);*/

    return false;
}
bool Sample::Release()
{
    m_Map.Release();
    /*
    for (int iBox = 0; iBox < _countof(m_BoxObj); iBox++)
    {
        m_BoxObj[iBox].Release();
    }
    */

    return true;
}



Sample::Sample()
{
}


Sample::~Sample()
{
}