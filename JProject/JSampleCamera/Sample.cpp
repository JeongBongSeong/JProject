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
    for (int iObj = 0; iObj < _countof(m_BoxObj); iObj++)
    {
        m_BoxObj[iObj].Init();
        m_BoxObj[iObj].Load(L"Shader.hlsl", "VS", "PS");
    }
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

    for (int iObj = 0; iObj < 2; iObj++)
    {
        m_BoxObj[iObj].Frame();
    }
    g_Input.m_ptBeforePos = g_Input.m_ptPos;
    return true;
    
}
bool Sample::Render()
{

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

    return false;
}
bool Sample::Release()
{
    for (int iBox = 0; iBox < _countof(m_BoxObj); iBox++)
    {
        m_BoxObj[iBox].Release();
    }
    return true;
}



Sample::Sample()
{
}


Sample::~Sample()
{
}