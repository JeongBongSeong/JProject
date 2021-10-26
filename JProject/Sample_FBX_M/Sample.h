#pragma once
#include"JCore.h"
#include"JFbxObj.h"



class Sample : public JCore
{
public:
	JFbxObj		m_FbxObj;
	JTexture	m_Texture;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

public:
	Sample();
	virtual ~Sample();

};

