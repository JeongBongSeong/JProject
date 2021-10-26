#pragma once
#include "JModel.h"
#include <fbxsdk.h>
#pragma comment	(lib, "libfbxsdk.lib")
#pragma comment	(lib, "libxml2-md.lib")
#pragma comment	(lib, "zlib-md.lib")
class JFbxObj : public JModel
{
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	/// <summary>
	/// 가상함수 리스트
	/// </summary>
public:
	bool	LoadObject(std::string filename);
	virtual bool	Create(std::wstring filename, std::string vsEntry, std::string psEntry);
	bool	PostRender(ID3D11DeviceContext* pContext, UINT iNumIndex) override;
	/// <summary>
	/// 일반함수 리스트
	/// </summary>
public:
	void	PreProcess(FbxNode* pNode);
	void	ParseNode(FbxNode* pNode);
	FbxVector2 ReadTextureCoord(FbxMesh* pFbxMesh, DWORD dwVertexTextureCount, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex);

};

