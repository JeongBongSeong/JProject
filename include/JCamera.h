#pragma once
#include "JStd.h"
class JCamera
{
public:
	float				m_pSpeed;
	TVector3			m_vCameraPos;
	TVector3			m_vCameraTarget;
	TVector3			m_vLook;
	TVector3			m_vSide;
	TVector3			m_vUp;
public:
	float m_fYaw = 0.0f;
	float m_fPitch = 0.0f;
	float m_fRoll = 0.0f;
	float m_fRadius = 10.0f;
public:
	TMatrix m_matWorld;
	TMatrix m_matView;
	TMatrix m_matProj;
public:
	virtual TMatrix     CreateViewMatrix(TVector3 vPos, TVector3 vTarget, TVector3 vUp = TVector3(0, 1, 0));
	virtual TMatrix  	CreateProjMatrix(float fNear, float fFar, float fFov, float fAspect);
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();

public:
	JCamera();
	virtual ~JCamera();
};

class JDebugCamera : public JCamera
{
public:
	virtual bool		Frame() override;
	virtual TMatrix		Update(TVector4 vValue);
};
