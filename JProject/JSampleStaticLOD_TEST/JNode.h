#pragma once
#include "JStd.h"
#include "JMap.h"
struct Rect
{
	float  x, y, w, h;
};
struct JRect
{
	TVector2  p0;
	TVector2  p1;
	TVector2  wh;
};
typedef std::vector<DWORD>  DWORD_VECTOR;
struct JLodPatch
{
	UINT   iLodLevel;

	DWORD_VECTOR		IndexList[16];
	ID3D11Buffer* IndexBufferList[16] = { nullptr, };

	void Release()
	{
		for (int iBuffer = 0; iBuffer < 16; iBuffer++)
		{
			if (IndexBufferList[iBuffer])
			{
				IndexBufferList[iBuffer]->Release();
				IndexBufferList[iBuffer] = nullptr;
			}

		}
	}
	JLodPatch() {}
	~JLodPatch()
	{
		Release();
	}
};
class JNode
{
public:
	UINT		m_iLodLevel;
public:
	static      int g_iNewCounter;
	int			m_iIndex;
	JRect		m_tRect;
	std::vector<TVector2>  m_ObjectList;
	std::vector<DWORD>  m_CornerList;
	std::vector<DWORD>  m_IndexList;
	ID3D11Buffer* m_pIndexBuffer;
	std::vector<SimpleVertex>  m_pVertexList;
	ID3D11Buffer* m_pVertexBuffer;
	TVector3		m_vCenter;

	JNode* m_pChild[4];
	JNode* m_NeighborList[4];
	int			m_iDepth;
	bool		m_bLeaf;
	JNode* m_pParent;
public:
	bool		AddObject(float fX, float fY);
	bool		AddObject(TVector2 pos);
	bool		IsRect(TVector2 pos);
	void		SetRect(float x, float y, float w, float h);

public:
	JNode() {};
	JNode(UINT x, UINT y, UINT w, UINT h);
	~JNode();
};

