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
    std::wstring szDefaultTexture;
};
class JMap :public JModel
{
public:
    JMapInfo m_info;
public:
    bool    Load(JMapInfo& info, std::wstring vsfilename, std::wstring psfilename, std::string vsEntry, std::string psEntry);
    bool	CreateVertexData() override;
    bool    CreateIndexData() override;
};

