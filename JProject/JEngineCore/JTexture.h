#pragma once
#include "JStd.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"


class JTexture
{
public:
	int			 m_iTexType;
	std::wstring m_szFileName;
public:
	ID3D11Resource* m_pTexture;
	ID3D11ShaderResourceView* m_pTextureSRV;
public:
	bool   Init();
	bool   Frame();
	bool   Render();
	bool   Release();
	bool   LoadTexture(std::wstring texFileName);

public:
	JTexture();
};