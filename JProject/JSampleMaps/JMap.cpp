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
    //m_VertexList
    // 0  1  2
    // 3  4  5
    // 6  7  8

    m_pVertexList.resize(m_info.m_iNumVertex);

    int iIndex = 0;
    for (int iRow = 0; iRow < m_info.m_iNumRowCell; iRow++)
    {
        for (int iCol = 0; iCol < m_info.m_iNumColCell; iCol++)
        {
            m_pVertexList[iIndex + 0].pos.x = m_info.m_fCellDistance * iCol;
            m_pVertexList[iIndex + 0].pos.y = 0.0f;
            m_pVertexList[iIndex + 0].pos.z = -m_info.m_fCellDistance * iRow;

            m_pVertexList[iIndex + 1].pos.x = m_pVertexList[iIndex + 0].pos.x + m_info.m_fCellDistance;
            m_pVertexList[iIndex + 1].pos.y = 0.0f;
            m_pVertexList[iIndex + 1].pos.z = m_pVertexList[iIndex + 0].pos.z;

            m_pVertexList[iIndex + 2].pos.x =
                m_pVertexList[iIndex + 0].pos.x;
            m_pVertexList[iIndex + 2].pos.y = 0.0f;
            m_pVertexList[iIndex + 2].pos.z =
                m_pVertexList[iIndex + 0].pos.z - m_info.m_fCellDistance;

            m_pVertexList[iIndex + 3].pos.x =
                m_pVertexList[iIndex + 0].pos.x;
            m_pVertexList[iIndex + 3].pos.y = 0.0f;
            m_pVertexList[iIndex + 3].pos.z =
                m_pVertexList[iIndex + 0].pos.z - m_info.m_fCellDistance;
            m_pVertexList[iIndex + 4].pos.x =
                m_pVertexList[iIndex + 0].pos.x + m_info.m_fCellDistance;
            m_pVertexList[iIndex + 4].pos.y = 0.0f;
            m_pVertexList[iIndex + 4].pos.z =
                m_pVertexList[iIndex + 0].pos.z;
            m_pVertexList[iIndex + 5].pos.x =
                m_pVertexList[iIndex + 0].pos.x + m_info.m_fCellDistance;
            m_pVertexList[iIndex + 5].pos.y = 0.0f;
            m_pVertexList[iIndex + 5].pos.z =
                m_pVertexList[iIndex + 0].pos.z - m_info.m_fCellDistance;

            m_pVertexList[iIndex + 5].color =
                TVector4(
                    randstep(0.0f, 1.0f),
                    randstep(0.0f, 1.0f),
                    randstep(0.0f, 1.0f), 1.0f);
            iIndex += 6;
        }
    }
    if (m_pVertexList.size() > 0) return true;
    return false;
}