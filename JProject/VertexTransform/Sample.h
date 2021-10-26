#pragma once
#include"JCore.h"
#include"JVector.h"
#include "JMatrix.h"



struct SimpleVertex
{
	JVector3 pos;
	JVector4 color;
	SimpleVertex()
	{
		color.x = 1.0f;
		color.y = 1.0f;
		color.z = 1.0f;
		color.w = 1.0f;
	}
};

struct CB_DATA
{
	JMatrix  matWorld;
	JMatrix  matView;
	JMatrix  matProj;
};

class Sample : public JCore
{
	float				m_pSpeed;
	JVector3			m_vCameraPos;
	JVector3			m_vCameraTarget;
	CB_DATA				m_cbData;
	ID3DBlob* m_pVSBlob = nullptr;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pConstantBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	std::vector< SimpleVertex> m_VertexList;
public:
	HRESULT	CreateConstantBuffer();
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexLayout();
	HRESULT LoadShader();
	bool	LoadObject(std::wstring filename);

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Sample();
};

