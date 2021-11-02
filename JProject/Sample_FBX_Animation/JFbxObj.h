#pragma once
#include"JMesh.h"

class JFbxObj
{
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
public:
	TMatrix		m_matWorld;
	JAnimMatrix m_matAnimMatrix;
	bool	m_bAnimPlay = false;
	float   m_fElpaseTime = 0.0f;
	int		m_iAnimIndex = 0;
	float m_fStartTime;
	float m_fEndTime;
	float m_fSampleTime;
	std::vector<FbxNode*>  m_pFbxNodeList;
	std::vector<JMtrl*>  m_pFbxMaterialList;
	std::vector<JMesh*> m_pMeshList;
	CB_DATA				m_cbData;
	/// <summary>
	/// 가상함수 리스트
	/// </summary>
public:
	JMesh*	GetFindInedx(FbxNode* pNode);
	bool	LoadObject(std::string filename, std::string shaderfilename);
	bool	Frame();
	bool    Release();

	TMatrix     DxConvertMatrix(TMatrix m);
	TMatrix     ConvertMatrix(FbxMatrix& m);
	TMatrix     ConvertAMatrix(FbxAMatrix& m);

	void SetPixelShader(ID3D11PixelShader* ps);
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
	void	ParseAnimationNode();
	void	ParseAnimation();
	void	ParseAnimStack(FbxString* szData);
	bool	ParseMeshSkinning(FbxMesh* pFbxMesh, JMesh* pMesh, JSkinData* pSkindata);

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