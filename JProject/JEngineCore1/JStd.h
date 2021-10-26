#pragma once

#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>
#include <map>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include "TMath.h"
#include "iterator"
//#include "SimpleMath.h"

#include<dxgi.h>
#include<d3d11.h>
#include<d3dcompiler.h>

#pragma comment (lib,"D3DCompiler.lib")
#pragma comment (lib,"JEngineCore.lib")
#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"dxgi.lib")
#pragma comment (lib,"d2d1.lib")
#pragma comment (lib,"dwrite.lib")
#pragma comment	(lib, "DirectXTK.lib")

//using namespace DirectX::SimpleMath;
extern float g_fSecPerFrame;
extern float g_fGameTimer;
extern HWND g_hWnd;
extern RECT g_rtClient;
extern ID3D11Device* g_pd3dDevice;

template<typename T>
class JSingleton 
{
public:
	static T& Get() 
	{
		static T theSingle;
		return theSingle;
	}


};



#define randf(x) (x*rand()/(float)RAND_MAX)
#define randf2(x,off) (off+x*rand()/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)


//#define SAVE_RELEASE(s) ( if(s) s->Release(); s= nullptr;)