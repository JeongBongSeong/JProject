#pragma once
#include "JModel.h"
struct JMapInfo
{
    int m_iNumRow; // 2^n+1
    int m_iNumCol;
    int m_iNumRowCell;
    int m_iNumColCell;
    int m_iNumVertex;
    float m_fCellDistance;
};
class JMap :public JModel
{
public:
    JMapInfo m_info;
public:
    bool    Load(JMapInfo& info);
    bool	CreateVertexData() override;
};

