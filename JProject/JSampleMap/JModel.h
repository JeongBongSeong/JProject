#pragma once
#include"JStd.h"
#include"JVector.h"
#include "JMatrix.h"
#include "JDevice.h"

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
	TMatrix  matWorld;
	TMatrix  matView;
	TMatrix  matProj;
};

class JModel
{
public:
	std::vector<SimpleVertex>	m_pVertexList;
	std::vector<DWORD>			m_pIndexList;
	CB_DATA						m_cbData;
public:
	
	ID3D11Buffer*		m_pVertexBuffer;
	ID3D11Buffer*		m_pIndexBuffer;
	ID3D11Buffer*		m_pConstantBuffer;
	ID3D11InputLayout*	m_pVertexLayout;			//정점버퍼 중에  어떤 성분을 정점쉐이더로 넘길 것인가에 대함
	ID3D11VertexShader*	m_pVS;					//
	ID3D11PixelShader*	m_pPS;					//
	ID3DBlob* m_pVSBlob = nullptr;
public:
	TMatrix		m_matWorld;
public:
	void			SetMatrix(TMatrix* pMatWorld,TMatrix* pMatView, TMatrix* pMatProj);
	virtual HRESULT CreateVertexBuffer();
	virtual bool	CreateVertexData();
	virtual HRESULT CreateIndexBuffer();
	virtual bool	CreateIndexData();
	virtual HRESULT	CreateConstantBuffer();
	virtual HRESULT CreateVertexLayout();
	virtual HRESULT CreateVertexShader(std::wstring filename,
		std::string entry);
	virtual HRESULT CreatePixelShader(std::wstring filename,
		std::string entry);
	virtual bool	LoadObject(std::wstring filename);
	bool Load(std::wstring filename, std::string vsEntry, std::string psEntry);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render(ID3D11DeviceContext* pContext);	//렌더링을 할 때는 컨텍스트를 넘겨 준다.
	virtual bool Release();
public:
	JModel();
};

