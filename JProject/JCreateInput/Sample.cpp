#include "Sample.h"


bool Sample::Init()
{
    return true;
}
bool Sample::Frame()
{
    if (g_Input.GetKey(VK_RBUTTON) == KEY_PUSH)
    {
        int a = 1;
    }
    return true;
}
bool Sample::Render()
{
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