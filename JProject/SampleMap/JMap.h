#pragma once
#include "JModel.h"
struct TMapInfo
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
//public: 
    //TMapInfo m_info;
//public:
    //bool    Load(TMapInfo& info);
	//bool	CreateVertexData() override;
};

