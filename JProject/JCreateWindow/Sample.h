#pragma once
#include"JWindow.h"

class Sample : public JWindow
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

