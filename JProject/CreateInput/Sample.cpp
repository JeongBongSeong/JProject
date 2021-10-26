#include "Sample.h"

bool Sample::Init()
{
	//m_Timer.m_fSecPerFrame;
	//g_fSecPerFrame;
	return true;
}

bool Sample::Frame()
{
	if (g_Input.GetKey(VK_RBUTTON) == KEY_PUSH)
	{
		int kkkk = 0;
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


int APIENTRY wWinMain(	_In_		HINSTANCE	hInstance,
						_In_opt_	HINSTANCE	hPrevInstance,
						_In_		LPWSTR		lpCmdLine,
						_In_		int			nCmdShow)
{
	Sample gSample;
	gSample.InitWindows(hInstance, nCmdShow, L"CreateWindows");

	gSample.Run();

	return 1;
}

