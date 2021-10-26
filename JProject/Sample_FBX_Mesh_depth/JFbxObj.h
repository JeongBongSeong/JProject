#pragma once
#include "JModel.h"
#include <fbxsdk.h>
#pragma comment	(lib, "libfbxsdk.lib")
#pragma comment	(lib, "libxml2-md.lib")
#pragma comment	(lib, "zlib-md.lib")

const enum OBJECTCLASSTYPE {
	CLASS_GEOM = 0,
	CLASS_BONE,
	CLASS_DUMMY,
	CLASS_BIPED,
};

struct JMtrl
{
	FbxNode* m_pFbxNode;
	FbxSurfaceMaterial* m_pFbxSurfaceMtrl;
	JTexture	m_Texture;
	std::vector<JMtrl*> m_pSubMtrl;

	JMtrl() {}
	JMtrl(FbxNode* pFbxNode, FbxSurfaceMaterial* pFbxMtrl) 
	{
		m_pFbxNode = pFbxNode;
		m_pFbxSurfaceMtrl = pFbxMtrl;
	}

	void Release()
	{
		m_Texture.Release();
		for (auto& data : m_pSubMtrl)
		{
			data->Release();
			delete data;
		}
	}
};

struct JLayer
{
	FbxLayerElementUV* pUV;
	FbxLayerElementVertexColor* pColor;
	FbxLayerElementNormal* pNormal;
	FbxLayerElementMaterial* pMaterial;
};

struct JMesh : public JModel
{
	OBJECTCLASSTYPE		m_ClassType;
	std::wstring		m_szName;
	std::wstring		m_szParentName;
	int					m_iNumLayer;
	std::vector<JLayer> m_LayerList;
	int					m_iMtrlRef;
	TMatrix				m_matWorld;
	JMesh*				m_pParent;
	std::vector<JMesh*>	m_pSubMesh;
	

	virtual bool Release()
	{
		JModel::Release();
		for (auto data : m_pSubMesh)
		{
			data->Release();
			SAFE_DEL(data);
		}
		return true;
	}
	JMesh()
	{
		m_ClassType = CLASS_GEOM;
	}
};

class JFbxObj
{
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
public:
	std::vector<FbxNode*>  m_pFbxNodeList;
	std::vector<JMtrl*>  m_pFbxMaterialList;
	std::vector<JMesh*> m_pMeshList;
	CB_DATA				m_cbData;
	/// <summary>
	/// 가상함수 리스트
	/// </summary>
public:
	bool	LoadObject(std::string filename);
	bool    Release();

	TMatrix     DxConvertMatrix(TMatrix m);
	TMatrix     ConvertMatrix(FbxMatrix& m);
	
public:
	void	SetMatrix(TMatrix* pMatWorld, TMatrix* pMatView, TMatrix* pMatProj);
	bool    Render(ID3D11DeviceContext* pContext);
	int     GetRootMtrl(FbxSurfaceMaterial* pFbxMaterial);
	void	LoadMaterial(JMtrl* pMtrl);
	/// <summary>
	/// 일반함수 리스트
	/// </summary>
public:
	void	PreProcess(FbxNode* pNode);
	void	ParseNode(FbxNode* pNode, JMesh* pParentMesh);
	void	ParseMesh(FbxNode* pNode, JMesh* pMesh);
	TMatrix		ParseTransform(FbxNode* pNode, TMatrix& matParent);
public:
	FbxVector2 ReadTextureCoord(FbxMesh* pFbxMesh, DWORD dwVertexTextureCount, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex);
	FbxVector4  ReadNormal(const FbxMesh* mesh, DWORD dwVertexNormalCount, FbxLayerElementNormal* VertexNormalSets,int controlPointIndex, int dwVertexIndex);
	FbxColor	ReadColor(const FbxMesh* mesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* VertexColorSets, DWORD dwDCCIndex, DWORD dwVertexIndex);
	FbxVector4	ReadTangent(const FbxMesh* pFbxMesh,DWORD dwVertexTangentCount, FbxGeometryElementTangent* VertexTangentSets, DWORD dwDCCIndex, DWORD dwVertexIndex);
};
/*
#pragma once
#include "JModel.h"
#include <fbxsdk.h>
#pragma comment	(lib, "libfbxsdk.lib")
#pragma comment	(lib, "libxml2-md.lib")
#pragma comment	(lib, "zlib-md.lib")

struct JMtrl
{
	FbxNode* m_pFbxNode;
	FbxSurfaceMaterial* pFbxMtrl;
	JTexture m_Texture;
	std::vector<JMtrl> m_pSubMtrl;
	void Release()
	{
		m_Texture.Release();
		for (auto& data : m_pSubMtrl)
		{
			data.Release();
		}
	}
};

struct JMesh : public JModel
{
	int m_iMtrlRef;
	bool PostRender(ID3D11DeviceContext* pContext,UINT iNumIndex)
	{
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		pContext->Draw(m_pVertexList.size(), 0);
		return true;
	}
	bool Create(std::wstring filename, std::string vsEntry, std::string psEntry)
	{
		if (CreateVertexData())
		{
			CreateConstantBuffer();
			CreateVertexBuffer();
			CreateVertexShader(L"FbxShader.hlsl",, vsEntry);
			CreatePixelShader(filename, psEntry);
			CreateVertexLayout();
			return true;
		}
		return false;
	}
};


class JFbxObj
{
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
public:
	std::vector<FbxNode*> m_pFbxNodeList;
	std::vector<JMtrl*>	m_pFbxMaterialList;
	std::vector<JMesh*> m_pMeshList;

	CB_DATA m_cbData;
	/// <summary>
	/// 가상함수 리스트
	/// </summary>
public:
	bool	LoadObject(std::string filename);
	bool Release();
public:
	void SetMatrix(TMatrix* pMatWorld, TMatrix* pMatView, TMatrix* pMatProj);
	bool Render(ID3D11DeviceContext* pContext);
	int GetRootMtrl(FbxSurfaceMaterial* pFbxMaterial);
	void LoadMaterial(JMtrl* pMtrl);

	//bool	PostRender(ID3D11DeviceContext* pContext, UINT iNumIndex) override;
	/// <summary>
	/// 일반함수 리스트
	/// </summary>
public:
	void	PreProcess(FbxNode* pNode);
	void	ParseNode(FbxNode* pNode, JMesh* pMesh);
	FbxVector2 ReadTextureCoord(FbxMesh* pFbxMesh, DWORD dwVertexTextureCount, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex);

};

*/