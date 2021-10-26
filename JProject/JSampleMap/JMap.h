#pragma once
#include "JModel.h"

struct JMapInfo
{
	UINT m_iNumRows;
	UINT m_iNumCols;
	UINT m_iNumRowCell;
	UINT m_iNumColCell;
	UINT m_iNumFaces;
	float m_fCellDistance;
};

class JMap : public JModel
{
public:
	JMapInfo m_info;

public:
	virtual bool	Create(JMapInfo& info);
	bool	CreateVertexData() override;
	
	virtual bool	CreateIndexData();
};

