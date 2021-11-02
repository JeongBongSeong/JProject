#pragma once
#include "JModel.h"
class JShape : public JModel
{
};
class JBoxShape : public JShape
{
public:
	virtual bool Create(std::wstring vsfilename, std::wstring psfilename, std::string vsEntry, std::string psEntry);
	virtual bool Render(ID3D11DeviceContext* pContext);
	virtual bool PostRender(ID3D11DeviceContext* pContext);
};
class JPlaneShape : public JShape
{
public:
	bool CreateVertexData() override;
	bool CreateIndexData() override;
};