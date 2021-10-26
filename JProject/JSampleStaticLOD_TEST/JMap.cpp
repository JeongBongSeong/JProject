#include "JMap.h"
bool    JMap::Load(JMapInfo& info)
{
    m_info = info;
    m_info.m_iNumColCell = m_info.m_iNumCol - 1;
    m_info.m_iNumRowCell = m_info.m_iNumRow - 1;
    m_info.m_iNumVertex = m_info.m_iNumColCell * m_info.m_iNumRowCell * 6;
    return true;
}
bool	JMap::CreateVertexData()
{
    m_pVertexList.resize(m_info.m_iNumVertex);

    int iIndex = 0;
    for (int iRow = 0; iRow < m_info.m_iNumRow; iRow++)
    {
        for (int iCol = 0; iCol < m_info.m_iNumCol; iCol++)
        {
            int iIndex = iRow * m_info.m_iNumRow + iCol;
            m_pVertexList[iIndex].pos.x = m_info.m_fCellDistance * iCol;
            m_pVertexList[iIndex].pos.y = 0.0f;
            m_pVertexList[iIndex].pos.z = -m_info.m_fCellDistance * iRow;

            m_pVertexList[iIndex].color =
                TVector4(
                    randstep(0.0f, 1.0f),
                    randstep(0.0f, 1.0f),
                    randstep(0.0f, 1.0f), 1.0f);
        }
    }
    if (m_pVertexList.size() > 0) return true;
    return false;
}bool	JMap::CreateIndexData()
{
    m_pIndexList.resize(m_info.m_iNumColCell * m_info.m_iNumRowCell * 2 * 3);

    int iIndex = 0;
    for (int iRow = 0; iRow < m_info.m_iNumRowCell; iRow++)
    {
        for (int iCol = 0; iCol < m_info.m_iNumColCell; iCol++)
        {
            int iCurrentIndex = iRow * m_info.m_iNumRow + iCol;
            int iNextRow = (iRow + 1) * m_info.m_iNumRow + iCol;
            m_pIndexList[iIndex + 0] = iCurrentIndex;
            m_pIndexList[iIndex + 1] = iCurrentIndex + 1;
            m_pIndexList[iIndex + 2] = iNextRow;

            m_pIndexList[iIndex + 3] = m_pIndexList[iIndex + 2];
            m_pIndexList[iIndex + 4] = m_pIndexList[iIndex + 1];
            m_pIndexList[iIndex + 5] = iNextRow + 1;
            iIndex += 6;
        }
    }
    if (m_pIndexList.size() > 0) return true;
    return false;
}
