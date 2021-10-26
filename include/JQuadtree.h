#pragma once
#include "JNode.h"
#include <queue>

class JQuadtree : public JMap
{
public:
	UINT		m_iMaxDepth;
	UINT		m_iNumCell;
	UINT		m_iNumPatch;
	std::vector<DWORD>  m_IndexList;
	ID3D11Buffer* m_pIndexBuffer;
	std::vector<JLodPatch>   m_LodPatchList;
public:
	JNode* m_pRootNode;
	int			m_iNumCol;
	int			m_iNumRow;
	std::queue<JNode*>  m_Queue;
	std::vector<JNode*>  m_pLeafList;
	JMap* m_pMap;
public:
	bool	UpdateIndexList(JNode* pNode);
	HRESULT CreateIndexBuffer(JNode* pNode);
	bool	UpdateVertexList(JNode* pNode);
	HRESULT CreateVertexBuffer(JNode* pNode);
public:
	void    Build(JMap* pMap);
	bool    Init();
	JNode* CreateNode(JNode* pParent, float x, float y, float w, float h);
	void	Buildtree(JNode*);
	bool    AddObject(TVector2 pos);
	JNode* FindNode(JNode* pNode, TVector2 pos);

	JNode* FindPlayerNode(TVector2 pos);
	bool	SubDivide(JNode* pNode);


	void	SetNeighborNode(JNode* pNode);
	bool    LoadObject(std::wstring filename);

public:
	bool	Frame();
	bool	Render(ID3D11DeviceContext* pContext, TVector3& vCamera);
	bool    Release();

public:
	bool    ComputeStaticLodIndex(int iMaxCells);
	HRESULT CreateIndexBuffer(JLodPatch& patch, int iCode);
	template <typename OutputIterator>
	void	Tokenize(const std::wstring& text, const std::wstring& delimiters, OutputIterator first);
public:
	JQuadtree();
	virtual ~JQuadtree();
};

