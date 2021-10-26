#pragma once
#include"JCore.h"
#include"JFbxObj.h"



class Sample : public JCore
{
public:
	JFbxObj		m_FbxObj;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11DepthStencilState* m_pDsvState;
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

