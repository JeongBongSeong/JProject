#include "JWindow.h"

JWindow* g_pWindow = nullptr;
HWND g_hWnd;
RECT g_rtClient;
LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    assert(g_pWindow);
    return g_pWindow->WndProc(hWnd, message, wParam, lParam);
}
LRESULT JWindow::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return 0;
}
LRESULT JWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (MsgProc(hWnd, message, wParam, lParam))
    {
        return 1;
    }
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;

}

bool JWindow::InitWindows(HINSTANCE hInstance,int nCmdShow,const TCHAR* strTitle)
{
    WNDCLASSEXW wcex;
    RECT rc = { 0,0,1280,768 };

    ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = StaticWndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(1, 1, 1));
    wcex.lpszClassName = L"test";
    //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    if (!RegisterClassExW(&wcex))
        //실패 시 리턴
    {
        return false;
    }
    m_hInstance = hInstance;
    m_hWnd = CreateWindowExW(
        WS_EX_OVERLAPPEDWINDOW,
        L"test",
        strTitle,
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        rc.right - rc.left,
        rc.bottom - rc.top,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (m_hWnd == NULL)
    {
        return false;
    }
    
    GetWindowRect(m_hWnd, &m_rtWindow);
    GetClientRect(m_hWnd, &m_rtClient);
    
    g_hWnd = m_hWnd;
    g_rtClient = m_rtClient;

    ShowWindow(m_hWnd, nCmdShow);

    return true;
}


bool JWindow::Run()
{
    GameInit();
    // 코어의 함수를 이용   한다.
    MSG msg;
    while (m_bGameRun)
    {
        if (PeekMessageW(&msg,NULL,0,0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
             m_bGameRun = GameRun();
            //코어의 런
        }

        
    }
    GameRelease();
    return true;
}
bool JWindow::GameInit()
{
    return true;
}

bool JWindow::GameRun()
{
    return true;
}

bool JWindow::GameRelease()
{
    return true;
}

JWindow::JWindow() : m_bGameRun(true)
{
    g_pWindow = this;
}
