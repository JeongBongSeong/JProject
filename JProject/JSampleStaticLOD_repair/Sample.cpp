#define _CRT_SECURE_NO_WARNINGS
#include "Sample.h"



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

bool Sample::Init()
{
    
    JMapInfo info{
	   64 + 1,
	   64 + 1, 0,0, 0,
	   1.0f
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
    
    //m_Map.Render(m_pImmediateContext);
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