#pragma once
#include"JCore.h"
#include"JModel.h"



class Sample : public JCore
{
public:
	JModel	m_Box;
public:
	Sample();
	

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

