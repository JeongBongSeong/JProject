#pragma once
#include"JCore.h"
#include"JFbxObj.h"
#include"JQuadtree.h"
#include"JShape.h"

class JMiniMap : public JPlaneShape
{
public:
    bool		LoadTexture()
    {
        m_Tex.LoadTexture(L"../../data/KGCAGK.bmp");
    }
    bool CreateVertexData()
    {
        m_pVertexList.resize(4);

        m_pVertexList[0].pos = TVector3(-1.0f, 1.0f, 0.0f);
        m_pVertexList[0].normal = TVector3(0.0f, 0.0f, -1.0f);
        m_pVertexList[0].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
        m_pVertexList[0].tex = TVector2(0.0f, 0.0f);

        m_pVertexList[1].pos = TVector3(-0.5f, 1.0f, 0.0f);
        m_pVertexList[1].normal = TVector3(0.0f, 0.0f, -1.0f);
        m_pVertexList[1].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
        m_pVertexList[1].tex = TVector2(1.0f, 0.0f);


        m_pVertexList[2].pos = TVector3(-1.0f, 0.5f, 0.0f);
        m_pVertexList[2].normal = TVector3(0.0f, 0.0f, -1.0f);
        m_pVertexList[2].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
        m_pVertexList[2].tex = TVector2(0.0f, 1.0f);


        m_pVertexList[3].pos = TVector3(-0.5f, 0.5f, 0.0f);
        m_pVertexList[3].normal = TVector3(0.0f, 0.0f, -1.0f);
        m_pVertexList[3].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
        m_pVertexList[3].tex = TVector2(1.0f, 1.0f);
        return true;
    }
};

class Sample : public JCore
{
public:
    JMiniMap    m_MiniMap;
    JPlaneShape m_MapObj;
public:
    JViewRT     m_Rt;
public:
	float		m_fNum;
	TVector3	m_vMovePos;
	JFbxObj		m_FbxObj;
	JFbxObj		m_FbxObjA;
	JFbxObj		m_FbxObjB;

	TVector4	m_vLight;
	JMap				m_Map;
	JQuadtree			m_Quadtree;


	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11DepthStencilState* m_pDsvState;
	TMatrix		m_matShadow;
	ID3D11PixelShader* m_pPSShadow;

public:
	//HRESULT     CreateDepthStencilView();
	HRESULT     CreateDepthStencilState();
public:
	bool Init() override;
	bool Frame() override;
	//bool PreRender();
	bool Render() override;
	bool Release() override;

public:
	Sample();
	virtual ~Sample();

};

