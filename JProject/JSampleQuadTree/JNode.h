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
	// x1,y1(p0)
	//
	//          x2, y2(p1)
};

class JNode
{
public:
	static      int g_iNewCounter;
	int			m_iIndex;
	JRect		m_tRect;
	std::vector<TVector2>  m_ObjectList;
	std::vector<DWORD>  m_CornerList;
	std::vector<DWORD>  m_IndexList;
	ID3D11Buffer* m_pIndexBuffer;
	JNode* m_pChild[4];
	int			m_iDepth;
	bool		m_bLeaf;
	JNode* m_pParent;
public:
	bool		AddObject(float fX, float fY);
	bool		AddObject(TVector2 pos);
	bool		IsRect(TVector2 pos);
public:
	JNode() {};
	JNode(UINT x, UINT y, UINT w, UINT h);
	~JNode();
};

