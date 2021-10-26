#pragma once

#include"JStd.h"

class JWrite
{
public:
	ID2D1RenderTarget* m_pRT;
	ID2D1Factory* m_pd2dFactory;
	ID2D1SolidColorBrush* m_pTextBrush;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	IDWriteTextLayout* m_pTextLayout;



public:
	HRESULT CreateDeviceResources(IDXGISurface1* pSurface);
	bool DrawText(RECT rt, const TCHAR* text, D2D1::ColorF color);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

