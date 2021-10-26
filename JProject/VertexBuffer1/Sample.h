#pragma once
#include"JCore.h"
#include<d3dcompiler.h>
#include"JVector.h"
#pragma comment (lib,"D3DCompiler.lib")

struct SimpleVertex
{
	JVector3 pos;
	JVector4 color;
	SimpleVertex(JVector3 p, JVector4 c)
	{
		pos = p;
		color = c;
	}
	SimpleVertex()
	{
		pos = { 0.5f ,0.5f ,0.5f };
		color = { 0.5f ,0.5f ,0.5f ,0.5f };
	}
};


class Sample : public JCore
{

	std::vector<SimpleVertex> m_VertexList;
	ID3DBlob* m_pVSBlob = nullptr;
	ID3DBlob* m_pPSBlob = nullptr;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
public:
	Sample();
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexLayout();
	HRESULT LoadShader();
	bool	LoadObject(std::wstring filename);

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

