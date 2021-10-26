#include "JWindow.h"

JWindow* g_pWindow = nullptr;
HWND g_hWnd;
RECT g_rtClient;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);
	return g_pWindow->MsgProc(hWnd, message, wParam, lParam);
}

LRESULT JWindow::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
bool JWindow::InitWindows(HINSTANCE hInstance, int nCmdShow, const TCHAR* strWindowTitle)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	//wcex.cbClsExtra = 0;
	//wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	//wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"3D11StudySample";
	//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
		return false;
	m_hInstance = hInstance;
	RECT rc = { 0,0,1024,768 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	m_hWnd = CreateWindowEx(
		WS_EX_TOPMOST,
		L"3D11StudySample",
		strWindowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // 0
		CW_USEDEFAULT, // 0
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (m_hWnd == NULL)
	{
		return false;
	}

	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);

	g_hWnd = m_hWnd;
	g_rtClient = g_rtClient;


	ShowWindow(m_hWnd, nCmdShow);


	return true;
}
bool JWindow::Run()
{
	GameInit();
	MSG msg;
	while (m_bGameRun)
	{
		if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else
		{
			m_bGameRun = GameRun();
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

