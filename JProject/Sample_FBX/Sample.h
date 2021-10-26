#pragma once
#include"JCore.h"
#include "JMap.h"
#include "JQuadtree.h"
#include"JFbxObj.h"



class Sample : public JCore
{
public:
	JFbxObj		m_FbxObj;
	JTexture	m_Texture;
public:
	bool Init() override;
	bool Frame() override;
	bool Render();
	bool Release();

public:
	Sample();
	virtual ~Sample();

};

