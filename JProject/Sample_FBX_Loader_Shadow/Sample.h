#pragma once
#include"JCore.h"
#include"JFbxObj.h"
#include"JQuadtree.h"
#include"JShape.h"
#include"JMap.h"
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
struct cbDataShadow
{
    TMatrix g_matShadow1;
};
class JLight
{
public:
    TVector3    m_vPos;
    TVector3    m_vInitPos;
    TVector3    m_vTarget;
    TVector3    m_vDir;
    TMatrix     m_matWorld;
    TMatrix     m_matView;
    TMatrix     m_matProj;
public:
    void Set(TVector3 vPos, TVector3 vTarget)
    {
        m_vInitPos = vPos;
        m_vPos = vPos;
        m_vTarget = vTarget;
        m_vDir = m_vTarget - m_vPos;
        D3DXVec3Normalize(&m_vDir, &m_vDir);
        TVector3 vUp(0, 1, 0);
        D3DXMatrixLookAtLH(&m_matView, &m_vPos,&m_vTarget, &vUp);
        D3DXMatrixPerspectiveFovLH(&m_matProj, XM_PI * 0.25f, 1.0f, 1.0f, 1000.0f);
    }
    bool Frame()
    {
        D3DXMatrixRotationY(&m_matWorld, XM_PI * g_fGameTimer * 0.1f);
        D3DXVec3TransformCoord(&m_vPos, &m_vInitPos, &m_matWorld);


        m_vDir = m_vTarget - m_vPos;
        D3DXVec3Normalize(&m_vDir, &m_vDir);
        TVector3 vUp(0, 1, 0);
        D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vTarget, &vUp);
        D3DXMatrixPerspectiveFovLH(&m_matProj, XM_PI * 0.25f, 1.0f, 1.0f, 1000.0f);

        return true;
    }
    
};


class Sample : public JCore
{
public:
    TMatrix             m_matTex;
    cbDataShadow        m_ShadowCB;
    JLight              m_Light1;
public:
    JMiniMap    m_MiniMap;
    JPlaneShape m_MapObj;
public:
    JViewRT     m_Rt;
public:
	float		m_fNum;
	TVector3	m_vMovePos;
public:
	JFbxObj		m_FbxCharacter;
public:

	TMatrix		m_matShadow;
	ID3D11PixelShader* m_pPSShadow = nullptr;
public:
    bool    m_bChangeCamera = true;
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

