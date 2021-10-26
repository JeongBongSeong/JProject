#include "Sample.h"


bool Sample::Init()
{
    return true;
}
bool Sample::Frame()
{
    return true;
}
bool Sample::Render()
{
    /*RECT rt = { 600,300,1280,768 };
    m_Write.DrawTextW(rt, L"Game", D2D1::ColorF(1, 0, 0, 1));*/

    return true;
}
bool Sample::Release()
{
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