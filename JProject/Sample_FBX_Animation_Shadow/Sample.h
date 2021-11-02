#pragma once
#include"JCore.h"
#include"JFbxObj.h"
#include"JQuadtree.h"


class Sample : public JCore
{
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
	HRESULT     CreateDepthStencilView();
	HRESULT     CreateDepthStencilState();
public:
	bool Init() override;
	bool Frame() override;
	bool PreRender();
	bool Render() override;
	bool Release() override;

public:
	Sample();
	virtual ~Sample();

};

