#pragma once
#include "JModel.h"
class JShape : public JModel
{
};
class JBoxShape : public JShape
{
public:
	virtual bool Create(std::wstring filename, std::string vsEntry, std::string psEntry);
	virtual bool Render(ID3D11DeviceContext* pContext);
	virtual bool PostRender(ID3D11DeviceContext* pContext);
};
