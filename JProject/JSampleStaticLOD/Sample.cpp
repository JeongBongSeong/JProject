#define _CRT_SECURE_NO_WARNINGS
#include "Sample.h"

LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return g_Input.MsgProc(hWnd, message, wParam, lParam);
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

bool Sample::Init()
{
    D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
    rd.FillMode = D3D11_FILL_WIREFRAME;
    rd.CullMode = D3D11_CULL_BACK;
    g_pd3dDevice->CreateRasterizerState(&rd, &m_pRSWireFrame);
    ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_BACK;
    g_pd3dDevice->CreateRasterizerState(&rd, &m_pRSSolid);

    JMapInfo info{
       64 + 1,
       64 + 1, 0,0, 0,
       1.0f
    };
    if (m_Map.Load(info))
    {
        m_Map.Create(L"Shader.hlsl", "VS", "PS");
    }
    m_Quadtree.Build(&m_Map);
    /*
    for (int iObj = 0; iObj < _countof(m_BoxObj); iObj++)
    {
        m_BoxObj[iObj].Create(L"Shader.hlsl", "VS", "PS");
    }
    */
    m_Camera.Init();
    m_Camera.CreateViewMatrix(TVector3(16, 3, -31),
        TVector3(16, 3, 100000));
    m_Camera.CreateProjMatrix(1.0f,
        1000.0f, JBASIS_PI * 0.5f,
        (float)g_rtClient.right / (float)g_rtClient.bottom);
    return true;
}
bool Sample::Frame()
{
    if (g_Input.m_bDrag && g_Input.m_ptBeforePos.x == g_Input.m_pDragDown.x)
    {
        g_Input.m_pDrag.x = 0;
    }
    if (g_Input.m_bDrag && g_Input.m_ptBeforePos.y == g_Input.m_pDragDown.y)
    {
        g_Input.m_pDrag.y = 0;
    }
    m_fYaw += g_fSecPerFrame * g_Input.m_pDrag.x * 5.0f;
    m_fPitch += g_fSecPerFrame * g_Input.m_pDrag.y * 5.0f;
    m_Camera.Update(TVector4(m_fPitch, m_fYaw, 0.0f, 0.0f));
    m_Camera.Frame();

    m_Map.Frame();
    /*
    for (int iObj = 0; iObj < 2; iObj++)
    {
        m_BoxObj[iObj].Frame();
    }
    */
    g_Input.m_ptBeforePos = g_Input.m_ptPos;

    return true;
    
}
bool Sample::Render()
{

    if (g_Input.GetKey(VK_F2) >= KEY_PUSH)
    {
        m_pImmediateContext->RSSetState(m_pRSWireFrame);
    }
    else if (g_Input.GetKey(VK_F3) >= KEY_PUSH)
    {
        m_pImmediateContext->RSSetState(m_pRSSolid);
    }

    m_Map.SetMatrix(
        nullptr,
        &m_Camera.m_matView,
        &m_Camera.m_matProj);
    //m_Map.Render(m_pImmediateContext);
    m_Quadtree.Render(m_pImmediateContext, m_Camera.m_vCameraPos);

    /*
    m_BoxObj[0].m_matWorld._41 = -3.0f;
    m_BoxObj[1].m_matWorld._41 = 3.0f;

    for (int iObj = 0; iObj < 2; iObj++)
    {
        m_BoxObj[iObj].SetMatrix(
            &m_BoxObj[iObj].m_matWorld,
            &m_Camera.m_matView,
            &m_Camera.m_matProj);
        m_BoxObj[iObj].Render(m_pImmediateContext);
    }
    */

    return false;
}
bool Sample::Release()
{
    m_pRSWireFrame->Release();
    m_pRSSolid->Release();
    m_Map.Release();
    /*
    for (int iBox = 0; iBox < _countof(m_BoxObj); iBox++)
    {
        m_BoxObj[iBox].Release();
    }
    */
    m_Camera.Release();
    return true;
}



Sample::Sample()
{
}


Sample::~Sample()
{
}