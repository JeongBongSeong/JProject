#pragma once

#include"JStd.h"
#include "JVector.h"
#include "JMatrix.h"
#include "JTexture.h"
struct PC_VERTEX
{
	TVector3 pos;
	TVector4 color;
	PC_VERTEX()
	{
		color.x = 1.0f;
		color.y = 1.0f;
		color.z = 1.0f;
		color.w = 1.0f;
	}
};
struct PCT_VERTEX
{
	TVector3 pos;
	TVector4 color;
	TVector2 tex;
	PCT_VERTEX()
	{
		color.x = 1.0f;
		color.y = 1.0f;
		color.z = 1.0f;
		color.w = 1.0f;
	}
}; 
struct PNCT_VERTEX
{
	TVector3 pos;
	TVector3 normal;
	TVector4 color;
	TVector2 tex;
	PNCT_VERTEX()
	{
		color.x = 1.0f;
		color.y = 1.0f;
		color.z = 1.0f;
		color.w = 1.0f;
	}
};

struct CB_DATA
{
	TMatrix		matWorld;
	TMatrix		matView;
	TMatrix		matProj;
	TMatrix		matNormal;
	TVector4	vValue;
};

class JModel
{
public:
	JTexture			m_Tex;
	UINT				m_iVertexSize = 0;
	UINT				m_iNumIndex = 0;
	CB_DATA				m_cbData;
	ID3DBlob* m_pVSBlob = nullptr;

	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;
	ID3D11Buffer* m_pConstantBuffer = nullptr;

	ID3D11InputLayout* m_pVertexLayout = nullptr;

	ID3D11VertexShader* m_pVS = nullptr;
	ID3D11PixelShader* m_pMainPS = nullptr;
	ID3D11PixelShader* m_pPS = nullptr;
	
	std::vector< PNCT_VERTEX> m_pVertexList;
	std::vector< DWORD> m_pIndexList;

public:
	TMatrix m_matWorld;			//tmath

public:
	void SetMatrix(TMatrix* pMatWorld, TMatrix* pMatView, TMatrix* pMatProj);
	bool LoadTexture(std::wstring szTextureName);
	bool LoadObject(std::wstring filename);		//정점의 정보를 파일에서 읽어와 정점리스트에 넣는다.
	virtual HRESULT LoadShader(std::wstring vsstrFilename, std::wstring psstrFilename, std::string vsEntry, std::string psEntry);

public:
	virtual bool CreateVertexData();
	virtual bool CreateIndexData();

public:
	virtual HRESULT	CreateConstantBuffer();
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateVertexLayout();

public:
	static ID3DBlob* LoadShaderBlob(std::wstring strFilename, std::string sEntry, std::string version);


public:
	bool Init();
	bool Frame();
	virtual bool Create(std::wstring vsfilename, std::wstring psfilename, std::string vsEntry, std::string psEntry,std::wstring szTextureName = NULL);
	virtual bool PreRender(ID3D11DeviceContext* pContext);
	virtual bool Render(ID3D11DeviceContext* pContext);
	virtual bool PostRender(ID3D11DeviceContext* pContext, UINT iNumIndex);
	virtual bool Release();

public:
	JModel();
	virtual ~JModel();
};

