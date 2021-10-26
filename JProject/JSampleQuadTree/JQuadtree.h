#pragma once
#include "JNode.h"
#include <queue>

class JQuadtree
{
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
	void    Build(JMap* pMap);
	bool    Init();
	JNode* CreateNode(JNode* pParent, float x, float y, float w, float h);
	void	Buildtree(JNode*);
	bool    AddObject(TVector2 pos);
	JNode* FindNode(JNode* pNode, TVector2 pos);

	JNode* FindPlayerNode(TVector2 pos);
	bool	SubDivide(JNode* pNode);
public:
	bool	Frame();
	bool	Render(ID3D11DeviceContext* pContext);
	bool    Release();
public:
	JQuadtree();
	virtual ~JQuadtree();
};

