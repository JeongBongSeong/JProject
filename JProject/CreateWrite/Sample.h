#include"JCore.h"
#pragma once

class Sample : public JCore
{
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
};

