#pragma once
#include"JCore.h"
#include "JMap.h"
#include "JQuadtree.h"




class Sample : public JCore
{
public:
	JMap				m_Map;
	JBoxShape			m_BoxObj;

	JQuadtree			m_Quadtree;
public:
	bool Init() override;
	bool Frame() override;
	bool Render();
	bool Release();
	
public:
	Sample();
	virtual ~Sample();

};

