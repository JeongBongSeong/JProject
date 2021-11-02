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
struct JWeight
{
	std::vector<int>     m_IndexList;
	std::vector<float>   m_WegihtList;
};
struct JSkinData
{
	std::vector<FbxNode*>  m_MatrixList;
	std::vector<JWeight>   m_VertexList;
};
struct PNCTIW_VERTEX
{
	float   index[4];
	float   weight[4];
};
struct JAnimMatrix
{
	TMatrix   matAnimation[255];
};
struct JMesh : public JModel
{
	std::vector<FbxNode*>	m_pFbxNodeList;
	std::vector<JMesh*>     m_pMeshLinkList;
	std::vector<TMatrix>	m_matBindPoseList;

	JAnimMatrix			m_matAnimMatrix;
	ID3D11Buffer* m_pAnimCB = nullptr;
	ID3D11Buffer* m_pIWVertrexBuffer = nullptr;
	std::vector<PNCTIW_VERTEX>	m_WeightList;
	FbxNode* m_pFbxNode = nullptr;
	OBJECTCLASSTYPE		m_ClassType;
	std::wstring		m_szName;
	std::wstring		m_szParentName;
	int					m_iNumLayer = 0;
	std::vector<JLayer> m_LayerList;
	int					m_iMtrlRef;
	TMatrix				m_matWorld;
	JMesh* m_pParent = nullptr;
	std::vector<TMatrix> m_AnimationTrack;
	std::vector<JMesh*>	m_pSubMesh;

public:
	virtual HRESULT		CreateConstantBuffer() override;
	virtual HRESULT		CreateVertexLayout() override;
	virtual HRESULT		CreateVertexBuffer() override;
	virtual bool		PreRender(ID3D11DeviceContext* pContext) override;
	virtual bool		Release() override;
public:
	JMesh();
	virtual ~JMesh();
};
