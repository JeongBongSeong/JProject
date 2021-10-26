#pragma once
#include"JCore.h"

class Sample : public JCore
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

