#pragma once
#include"JCore.h"
#include "JModel.h"





class Sample : public JCore
{
	JModel				m_Model;
	float				m_pSpeed;
	JVector3			m_vCameraPos;
	JVector3			m_vCameraTarget;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Sample();
};

