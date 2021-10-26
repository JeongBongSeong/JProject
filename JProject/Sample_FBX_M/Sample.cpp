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

bool		Sample::Init()
{
	//m_Texture.LoadTexture(L"../../data/wireframe.dds");
	m_FbxObj.LoadObject("../../data/box.fbx");

	return true;
}
bool		Sample::Frame() {
	return true;
}
bool		Sample::Render()
{
	m_FbxObj.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
	

	m_FbxObj.Render(m_pImmediateContext);
	return true;
}
bool		Sample::Release()
{
	m_FbxObj.Release();
	//m_Texture.Release();
	return true;
}
Sample::Sample()
{
}
Sample::~Sample()
{
}