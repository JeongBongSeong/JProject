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
    m_Model.Load(L"Shader.hlsl","VS","PS");
    return true;
}
bool Sample::Frame()
{
    
    m_Model.Frame();
    
    if (g_Input.GetKey('W') >= KEY_PUSH)
    {
        m_vCameraPos.z += m_pSpeed * g_fSecPerFrame;
        m_vCameraTarget.z += m_pSpeed * g_fSecPerFrame;
    }
    if (g_Input.GetKey('S') >= KEY_HOLD)
    {
        m_vCameraPos.z -= m_pSpeed * g_fSecPerFrame;
        m_vCameraTarget.z -= m_pSpeed * g_fSecPerFrame;
    }
    if (g_Input.GetKey('A') >= KEY_PUSH)
    {
        m_vCameraPos.x -= m_pSpeed * g_fSecPerFrame;
        m_vCameraTarget.x -= m_pSpeed * g_fSecPerFrame;
    }
    if (g_Input.GetKey('D') >= KEY_HOLD)
    {
        m_vCameraPos.x += m_pSpeed * g_fSecPerFrame;
        m_vCameraTarget.x += m_pSpeed * g_fSecPerFrame;
    }
    if (g_Input.GetKey('Q') >= KEY_PUSH)
    {
        m_vCameraPos.y -= m_pSpeed * g_fSecPerFrame;
        
    }
    if (g_Input.GetKey('E') >= KEY_HOLD)
    {
        m_vCameraPos.y += m_pSpeed * g_fSecPerFrame;
        
    }
    // -1 ~ +1 -> 0 ~ 1 => -1*0.5f+0.5f;
    // 0 ~ +1 -> -1 ~ 1 => 0.5f*2.0f-1.0f;
    // D3D11_USAGE_DEFAULT
    //m_cbData.matWorld._11 = cosf(g_fGameTimer)*0.5f+0.5f;
    //m_Model.m_cbData.matWorld = TMatrix::CreateRotationZ(g_fGameTimer);


    JVector3 vUp = { 0,1,0.0f };
    m_Model.m_cbData.matView = JMatrix::ViewLookAt(
        m_vCameraPos, m_vCameraTarget, vUp);

    m_Model.m_cbData.matProj = JMatrix::PerspectiveFovLH(1.0f,
        100.0f, JBASIS_PI * 0.5f,
        (float)g_rtClient.right / (float)g_rtClient.bottom);

    m_Model.m_cbData.matWorld = m_Model.m_cbData.matWorld.Transpose();
    m_Model.m_cbData.matView = m_Model.m_cbData.matView.Transpose();
    m_Model.m_cbData.matProj = m_Model.m_cbData.matProj.Transpose();
    m_pImmediateContext->UpdateSubresource(
        m_Model.m_pConstantBuffer, 0, NULL, &m_Model.m_cbData, 0, 0);
    


    return false;
    
}
bool Sample::Render()
{
    m_Model.Render(m_pImmediateContext);
    return true;
}
bool Sample::Release()
{
    m_Model.Release();
    return true;
}



Sample::Sample()
{
    m_pSpeed = 3.0f;
    m_vCameraPos = { 3,3, -5.0f };
    m_vCameraTarget = { 0,0,0.0f };
}