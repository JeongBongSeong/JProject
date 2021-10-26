#define _CRT_SECURE_NO_WARNINGS
#include "Sample.h"
#include "JVector.h"
Sample::Sample()
{
}

bool Sample::Init()
{
    m_Box.Init();
    return true;
}
bool Sample::Frame()
{
    m_Box.Frame();
    return true;
}
bool Sample::Render()
{
    m_Box.Render();
    return true;
}
bool Sample::Release()
{
    m_Box.Release();
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