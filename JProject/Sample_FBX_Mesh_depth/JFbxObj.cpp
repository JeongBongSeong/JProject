#define _CRT_SECURE_NO_WARNINGS
#include "JFbxObj.h"


TMatrix   JFbxObj::ParseTransform(FbxNode* pNode, TMatrix& matParent)
{
	//// TODO : �������
	FbxVector4 rotLcl = pNode->LclRotation.Get();
	FbxVector4 transLcl = pNode->LclTranslation.Get();
	FbxVector4 scaleLcl = pNode->LclScaling.Get();
	FbxMatrix matTransform(transLcl, rotLcl, scaleLcl);
	TMatrix matLocal = DxConvertMatrix(ConvertMatrix(matTransform));
	TMatrix matWorld = matLocal * matParent;
	return matWorld;
}

TMatrix     JFbxObj::DxConvertMatrix(TMatrix m)
{
	TMatrix mat;
	mat._11 = m._11; mat._12 = m._13; mat._13 = m._12;
	mat._21 = m._31; mat._22 = m._33; mat._23 = m._32;
	mat._31 = m._21; mat._32 = m._23; mat._33 = m._22;
	mat._41 = m._41; mat._42 = m._43; mat._43 = m._42;
	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._44 = 1.0f;
	return mat;
}
TMatrix     JFbxObj::ConvertMatrix(FbxMatrix& m)
{
	TMatrix mat;
	float* pMatArray = reinterpret_cast<float*>(&mat);
	double* pSrcArray = reinterpret_cast<double*>(&m);
	for (int i = 0; i < 16; i++)
	{
		pMatArray[i] = pSrcArray[i];
	}
	return mat;
}

void		JFbxObj::LoadMaterial(JMtrl* pMtrl)
{
	if (pMtrl == nullptr) return;
	if (pMtrl->m_pSubMtrl.size() > 0)
	{
		for (int iSub = 0; iSub < pMtrl->m_pSubMtrl.size(); iSub++)
		{
			JMtrl* pSubMtrl = pMtrl->m_pSubMtrl[iSub];
			FbxSurfaceMaterial* pFbxMaterial = pSubMtrl->m_pFbxSurfaceMtrl;
			FbxProperty prop = pFbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (prop.IsValid())
			{
				int iTexCount = prop.GetSrcObjectCount<FbxTexture>();
				for (int iTex = 0; iTex < iTexCount; iTex++)
				{
					FbxTexture* pTex = prop.GetSrcObject<FbxFileTexture>(iTex);
					if (pTex == nullptr) continue;
					FbxFileTexture* fileTexture = prop.GetSrcObject<FbxFileTexture>(iTex);

					std::string szFileName;
					char Drive[MAX_PATH] = { 0, };
					char Dir[MAX_PATH] = { 0, };
					char FName[MAX_PATH] = { 0, };
					char Ext[MAX_PATH] = { 0, };
					if (fileTexture->GetFileName())
					{
						_splitpath(fileTexture->GetFileName(), Drive, Dir, FName, Ext);
						Ext[4] = 0;
						szFileName = FName;
						if (_stricmp(Ext, ".tga") == 0)
						{
							szFileName += ".dds";
						}
						else
						{
							szFileName += Ext;
						}
					}

					pSubMtrl->m_Texture.m_szFileName = TBASIS::g_szDataPath;
					pSubMtrl->m_Texture.m_szFileName += L"object/";
					pSubMtrl->m_Texture.m_szFileName += TBASIS::mtw(szFileName);
					pSubMtrl->m_Texture.LoadTexture(
						pSubMtrl->m_Texture.m_szFileName);
				}
			}
		}
	}
	else
	{
		//FbxSurfaceMaterial* pFbxSurfaceMtrl = pMtrl->pFbxMtrl;
		FbxSurfaceMaterial* pFbxMaterial = pMtrl->m_pFbxNode->GetMaterial(0);
		FbxProperty prop = pFbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
		if (prop.IsValid())
		{
			int iTexCount = prop.GetSrcObjectCount<FbxTexture>();
			for (int iTex = 0; iTex < iTexCount; iTex++)
			{
				FbxTexture* pTex = prop.GetSrcObject<FbxFileTexture>(iTex);
				if (pTex == nullptr) continue;
				FbxFileTexture* fileTexture = prop.GetSrcObject<FbxFileTexture>(iTex);

				std::string szFileName;
				char Drive[MAX_PATH] = { 0, };
				char Dir[MAX_PATH] = { 0, };
				char FName[MAX_PATH] = { 0, };
				char Ext[MAX_PATH] = { 0, };
				if (fileTexture->GetFileName())
				{
					_splitpath(fileTexture->GetFileName(), Drive, Dir, FName, Ext);
					Ext[4] = 0;
					szFileName = FName;
					if (_stricmp(Ext, ".tga") == 0)
					{
						szFileName += ".dds";
					}
					else
					{
						szFileName += Ext;
					}
				}
				pMtrl->m_Texture.m_szFileName = TBASIS::g_szDataPath;
				pMtrl->m_Texture.m_szFileName += L"object\\";
				pMtrl->m_Texture.m_szFileName += TBASIS::mtw(szFileName);
				pMtrl->m_Texture.LoadTexture(pMtrl->m_Texture.m_szFileName);
			}
		}
	}
}
void		JFbxObj::SetMatrix(TMatrix* pMatWorld, TMatrix* pMatView, TMatrix* pMatProj)
{
	if (pMatWorld != nullptr)
	{
		m_cbData.matWorld = *pMatWorld;
	}
	if (pMatView != nullptr)
	{
		m_cbData.matView = *pMatView;
	}
	if (pMatProj != nullptr)
	{
		m_cbData.matProj = *pMatProj;
	}
}
bool    JFbxObj::Render(ID3D11DeviceContext* pContext)
{
	for (int iObj = 0; iObj < m_pMeshList.size(); iObj++)
	{
		JMesh* pMesh = m_pMeshList[iObj];
		if (pMesh->m_ClassType != CLASS_GEOM) continue;



		JMtrl* pMtrl = nullptr;
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ������͸��� ����  
		if (pMesh->m_pSubMesh.size() > 0)
		{
			for (int iSub = 0; iSub < pMesh->m_pSubMesh.size(); iSub++)
			{
				JMtrl* pSubMtrl =
					m_pFbxMaterialList[pMesh->m_iMtrlRef]->m_pSubMtrl[iSub];
				pContext->PSSetSamplers(0, 1, &pSubMtrl->m_Texture.m_pSampler);
				pContext->PSSetShaderResources(1, 1, &pSubMtrl->m_Texture.m_pTextureSRV);
				pMesh->m_pSubMesh[iSub]->SetMatrix(&pMesh->m_matWorld, &m_cbData.matView, &m_cbData.matProj);
				pMesh->m_pSubMesh[iSub]->Render(pContext);
			}
		}
		else
		{
			if (pMesh->m_iMtrlRef >= 0)
			{
				pMtrl = m_pFbxMaterialList[pMesh->m_iMtrlRef];
			}
			if (pMtrl != nullptr)
			{
				pContext->PSSetSamplers(0, 1, &pMtrl->m_Texture.m_pSampler);
				pContext->PSSetShaderResources(1, 1, &pMtrl->m_Texture.m_pTextureSRV);
			}
			pMesh->SetMatrix(&pMesh->m_matWorld, &m_cbData.matView, &m_cbData.matProj);
			pMesh->Render(pContext);
		}
	}
	return true;
}
int     JFbxObj::GetRootMtrl(FbxSurfaceMaterial* pFbxMaterial)
{
	for (int iMtrl = 0; iMtrl < m_pFbxMaterialList.size(); iMtrl++)
	{
		if (m_pFbxMaterialList[iMtrl]->m_pFbxSurfaceMtrl == pFbxMaterial)
		{
			return iMtrl;
		}
	}
	return -1;
}
void	JFbxObj::ParseNode(FbxNode* pNode, JMesh* pParentMesh)
{
	
	if (pNode->GetCamera() || pNode->GetLight()) { return; }

	JMesh* pMesh = new JMesh;
	pMesh->m_szName = TBASIS::mtw(pNode->GetName());
	TMatrix matParent;
	if (pParentMesh != nullptr)
	{
		pMesh->m_szParentName = pParentMesh->m_szName;
		matParent = pParentMesh->m_matWorld;
	}
	pMesh->m_pParent = pParentMesh;
	pMesh->m_matWorld = ParseTransform(pNode, matParent);



	if (pNode->GetMesh())
	{
		ParseMesh(pNode, pMesh);
		pMesh->m_ClassType = CLASS_GEOM;
	}
	else
	{
		pMesh->m_ClassType = CLASS_BONE;
	}
	m_pMeshList.push_back(pMesh);
	
	int iNumChild = pNode->GetChildCount();
	for (int iNode = 0; iNode < iNumChild; iNode++)
	{
		FbxNode* pChildNode = pNode->GetChild(iNode);
		ParseNode(pChildNode, pMesh);
	}

}

void JFbxObj::ParseMesh(FbxNode* pNode, JMesh* pMesh)
{
	FbxSurfaceMaterial* pFbxMaterial = pNode->GetMaterial(0);
	pMesh->m_iMtrlRef = GetRootMtrl(pFbxMaterial);

	std::string name = pNode->GetName();
	FbxMesh* pFbxMesh = pNode->GetMesh();
	std::vector< std::string> fbxFileTexList;
	if (pFbxMesh != nullptr)
	{
		pMesh->m_iNumLayer = pFbxMesh->GetLayerCount();
		pMesh->m_LayerList.resize(pMesh->m_iNumLayer);
		// �������� ���̾� ����Ʈ
		for (int iLayer = 0; iLayer < pMesh->m_iNumLayer; iLayer++)
		{
			FbxLayer* pLayer = pFbxMesh->GetLayer(iLayer);
			if (pLayer->GetVertexColors() != nullptr)
			{
				pMesh->m_LayerList[iLayer].pColor = pLayer->GetVertexColors();
			}
			if (pLayer->GetNormals() != nullptr)
			{
				pMesh->m_LayerList[iLayer].pNormal = pLayer->GetNormals();
			}
			if (pLayer->GetMaterials() != nullptr)
			{
				pMesh->m_LayerList[iLayer].pMaterial = pLayer->GetMaterials();
			}
			if (pLayer->GetUVs() != nullptr)
			{
				pMesh->m_LayerList[iLayer].pUV = pLayer->GetUVs();
			}

		}

		FbxAMatrix matGeom;
		FbxVector4 rot = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
		FbxVector4 trans = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		FbxVector4 scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
		matGeom.SetT(trans);
		matGeom.SetR(rot);
		matGeom.SetS(scale);
		

		int m_iNumPolygon = pFbxMesh->GetPolygonCount();
		// ��������Ʈ �ּ�
		FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
		int iBasePlayIndex = 0;
		int iNumFbxMaterial = pNode->GetMaterialCount();
		if (iNumFbxMaterial > 1)
		{
			pMesh->m_pSubMesh.resize(iNumFbxMaterial);
			for (int iSub = 0; iSub < iNumFbxMaterial; iSub++)
			{
				pMesh->m_pSubMesh[iSub] = new JMesh;
			}
		}
		FbxLayerElementMaterial* fbxSubMaterial = pMesh->m_LayerList[0].pMaterial;
		FbxLayerElementUV* VertexUVList = pMesh->m_LayerList[0].pUV;
		FbxLayerElementVertexColor* VertexColorList = pMesh->m_LayerList[0].pColor;
		FbxLayerElementNormal* VertexNormalList = pMesh->m_LayerList[0].pNormal;
		for (int iPoly = 0; iPoly < m_iNumPolygon; iPoly++)
		{
			int iSubMtrlIndex = 0;
			if (fbxSubMaterial != nullptr)
			{
				switch (fbxSubMaterial->GetMappingMode())
				{
				case FbxLayerElement::eByPolygon:
				{
					switch (fbxSubMaterial->GetReferenceMode())
					{
					case FbxLayerElement::eDirect:
					{
						iSubMtrlIndex = iPoly;
					}break;
					case FbxLayerElement::eIndex:
					case FbxLayerElement::eIndexToDirect:
					{
						iSubMtrlIndex =
							fbxSubMaterial->GetIndexArray().GetAt(iPoly);
					}break;
					}
				}break;
				default:
				{
					iSubMtrlIndex = 0;
				}break;
				}
			}
			/*
			
			
			
			*/
			// �ﰢ��, �簢��
			int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
			int m_iNumTriangle = iPolySize - 2;
			int iCornerIndex[3];
			for (int iTriangle = 0;
				iTriangle < m_iNumTriangle;
				iTriangle++)
			{
				// ��ġ �ε���
				iCornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, 0);
				iCornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, iTriangle + 2);
				iCornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, iTriangle + 1);

				for (int iIndex = 0; iIndex < 3; iIndex++)
				{
					PNCT_VERTEX vertex;
					FbxVector4 pos = pVertexPositions[iCornerIndex[iIndex]];
					FbxVector4 vPos = matGeom.MultT(pos);
					vertex.pos.x = vPos.mData[0];
					vertex.pos.y = vPos.mData[2];
					vertex.pos.z = vPos.mData[1];
					if (VertexUVList != nullptr)
					{
						int uvIndex[3];
						uvIndex[0] = pFbxMesh->GetTextureUVIndex(iPoly, 0);
						uvIndex[1] = pFbxMesh->GetTextureUVIndex(iPoly, iTriangle + 2);
						uvIndex[2] = pFbxMesh->GetTextureUVIndex(iPoly, iTriangle + 1);
						FbxVector2 uv = ReadTextureCoord(
							pFbxMesh, 1, VertexUVList,
							iCornerIndex[iIndex], uvIndex[iIndex]);
						vertex.tex.x = uv.mData[0];
						vertex.tex.y = 1.0f - uv.mData[1];
					}
					if (VertexColorList != nullptr)
					{
						int iColorIndex[3];
						iColorIndex[0] = iBasePlayIndex + 0;
						iColorIndex[1] = iBasePlayIndex + iTriangle + 2;
						iColorIndex[2] = iBasePlayIndex + iTriangle + 1;

						FbxColor color = ReadColor(
							pFbxMesh, 1, VertexColorList,
							iCornerIndex[iIndex], iColorIndex[iIndex]);
						vertex.color.x = color.mRed;
						vertex.color.y = color.mGreen;
						vertex.color.z = color.mBlue;
						vertex.color.w = 1.0f;

					}
					if (VertexNormalList != nullptr)
					{
						int iNormalIndex[3];
						iNormalIndex[0] = iBasePlayIndex + 0;
						iNormalIndex[1] = iBasePlayIndex + iTriangle + 2;
						iNormalIndex[2] = iBasePlayIndex + iTriangle + 1;
						FbxVector4 normal = ReadNormal(
							pFbxMesh, 1, VertexNormalList,
							iCornerIndex[iIndex], iNormalIndex[iIndex]);
						vertex.normal.x = normal.mData[0];
						vertex.normal.y = normal.mData[2];
						vertex.normal.z = normal.mData[1];
					}
					if (iNumFbxMaterial > 1)
					{
						pMesh->m_pSubMesh[iSubMtrlIndex]->m_pVertexList.push_back(vertex);
					}
					else
					{
						pMesh->m_pVertexList.push_back(vertex);
					}
				}
			}
			iBasePlayIndex += iPolySize;
		}


	}
}

void	JFbxObj::PreProcess(FbxNode* pNode)
{
	if (pNode->GetCamera() || pNode->GetLight()){return;}

	int iNumFbxMaterial = pNode->GetMaterialCount();
	FbxSurfaceMaterial* pFbxMaterial = pNode->GetMaterial(0);
	if (GetRootMtrl(pFbxMaterial) == -1)
	{
		if(iNumFbxMaterial > 1)
		{
			JMtrl* pMtrl = new JMtrl(pNode, pFbxMaterial);
			for (int iSub = 0; iSub < iNumFbxMaterial; iSub++)
			{
				FbxSurfaceMaterial* pFbxSubMaterial = pNode->GetMaterial(iSub);
				_ASSERT(pFbxSubMaterial != nullptr);
				JMtrl* pSubMtrl = new JMtrl(pNode, pFbxSubMaterial);
				pMtrl->m_pSubMtrl.push_back(pSubMtrl);
			}
			m_pFbxMaterialList.push_back(pMtrl);
		}
		else
		{
			if (pFbxMaterial != nullptr)
			{
				JMtrl* pMtrl = new JMtrl(pNode, pFbxMaterial);
				m_pFbxMaterialList.push_back(pMtrl);
			}
		}
	}

	int iNumChild = pNode->GetChildCount();
	for (int iNode = 0; iNode < iNumChild; iNode++)
	{
		FbxNode* pChildNode = pNode->GetChild(iNode);
		FbxNodeAttribute::EType type =
			pChildNode->GetNodeAttribute()->GetAttributeType();
		if (/*type == FbxNodeAttribute::eMesh ||
			type == FbxNodeAttribute::eSkeleton*/
			pChildNode->GetNodeAttribute() != nullptr)
		{
			m_pFbxNodeList.push_back(pChildNode);
		}
		PreProcess(pChildNode);
	}
}
bool	JFbxObj::LoadObject(std::string filename)
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
	bool bRet = m_pFbxImporter->Initialize(filename.c_str());
	bRet = m_pFbxImporter->Import(m_pFbxScene);
	FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);

	FbxNode* m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode);

	for (int iMtrl = 0; iMtrl < m_pFbxMaterialList.size(); iMtrl++)
	{
		JMtrl* pMtrl = m_pFbxMaterialList[iMtrl];
		LoadMaterial(pMtrl);
	}

	ParseNode(m_pRootNode, nullptr);

	for (int iMesh = 0; iMesh < m_pMeshList.size(); iMesh++)
	{
		JMesh* pMesh = m_pMeshList[iMesh];
		if (pMesh->m_pSubMesh.size() > 0)
		{
			for (int iSubMesh = 0; iSubMesh < m_pMeshList[iMesh]->m_pSubMesh.size(); iSubMesh++)
			{
				JMesh* pSubMesh = m_pMeshList[iMesh]->m_pSubMesh[iSubMesh];

				pSubMesh->Create(L"../../data/shader/DefaultShader.hlsl", "VS", "PS");
			}
		}
		else
		{
			pMesh->Create(L"../../data/shader/DefaultShader.hlsl", "VS", "PS");
		}
	}
	m_pFbxScene->Destroy();
	m_pFbxImporter->Destroy();
	m_pFbxManager->Destroy();
	return bRet;
}
bool    JFbxObj::Release()
{
	for (int iObj = 0; iObj < m_pMeshList.size(); iObj++)
	{
		m_pMeshList[iObj]->Release();
		SAFE_DEL(m_pMeshList[iObj]);
	}
	for (int iObj = 0; iObj < m_pFbxMaterialList.size(); iObj++)
	{
		m_pFbxMaterialList[iObj]->Release();
		delete m_pFbxMaterialList[iObj];
	}
	return true;
}


//#include "JFbxObj.h"
//
//void JFbxObj::LoadMaterial(JMtrl* pMtrl)
//{
//	FbxSurfaceMaterial* pFbxMaterial = pMtrl->m_pFbxNode->GetMaterial(0);
//	FbxProperty prop = pFbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
//
//	if (prop.IsValid())
//	{
//		int iTexCount = prop.GetSrcObjectCount<FbxTexture>();
//		for (int iTex = 0; iTex < iTexCount; iTex++)
//		{
//			FbxTexture* pTex = prop.GetSrcObject<FbxFileTexture>(iTex);
//			if (pTex == nullptr) continue;
//			FbxFileTexture* fileTexture = prop.GetSrcObject<FbxFileTexture>(iTex);
//
//			std::string szFileName;
//			char Drive[MAX_PATH] = { 0, };
//			char Dir[MAX_PATH] = { 0, };
//			char FName[MAX_PATH] = { 0, };
//			char Ext[MAX_PATH] = { 0, };
//			if (fileTexture->GetFileName())
//			{
//				_splitpath(fileTexture->GetFileName(), Drive, Dir, FName, Ext);
//				Ext[4] = 0;
//				szFileName = FName;
//				szFileName += Ext;
//			}
//			pMtrl->m_Texture.m_szFileName = TBASIS::g_szDataPath;
//			pMtrl->m_Texture.m_szFileName += TBASIS::mtw(szFileName);
//			pMtrl->m_Texture.LoadTexture(pMtrl->m_Texture.m_szFileName);
//		}
//	}
//}
//void		JFbxObj::SetMatrix(
//	TMatrix* pMatWorld,
//	TMatrix* pMatView, TMatrix* pMatProj)
//{
//	if (pMatWorld != nullptr)
//	{
//		m_cbData.matWorld = *pMatWorld;
//	}
//	if (pMatView != nullptr)
//	{
//		m_cbData.matView = *pMatView;
//	}
//	if (pMatProj != nullptr)
//	{
//		m_cbData.matProj = *pMatProj;
//	}
//}
//bool JFbxObj::Render(ID3D11DeviceContext* pContext)
//{
//	for (int iObj = 0; iObj < m_pMeshList.size(); iObj++)
//	{
//		JMesh* pMesh = m_pMeshList[iObj];
//		JMtrl* pMtrl = nullptr;
//		if (pMesh->m_iMtrlRef >= 0)
//		{
//			pMtrl = m_pFbxMaterialList[pMesh->m_iMtrlRef];
//		}
//		pMesh->SetMatrix(nullptr, &m_cbData.matView, &m_cbData.matProj);
//		if (pMtrl != nullptr)
//		{
//			pContext->PSSetShaderResources(1, 1, &pMtrl->m_Texture.m_pTextureSRV);
//		}
//		pMesh->Render(pContext);
//	}
//	return true;
//}
//int JFbxObj::GetRootMtrl(FbxSurfaceMaterial* pFbxMaterial)
//{
//	for (int iMtrl = 0; iMtrl < m_pFbxMaterialList.size(); iMtrl++)
//	{
//		if (m_pFbxMaterialList[iMtrl]->pFbxMtrl == pFbxMaterial)
//		{
//			return iMtrl;
//		}
//	}
//	return -1;
//}
//
//void	JFbxObj::ParseNode(FbxNode* pNode, JMesh* pMesh)
//{
//	FbxSurfaceMaterial* pFbxMaterial = pNode->GetMaterial(0);
//	pMesh->m_iMtrlRef = GetRootMtrl(pFbxMaterial);
//	std::string name = pNode->GetName();
//	FbxMesh* pFbxMesh = pNode->GetMesh();
//	std::vector<std::string> fbxFileTexList;
//
//	if (pFbxMesh != nullptr)
//	{
//		int iNumLayer = pFbxMesh->GetLayerCount();
//		std::vector<FbxLayerElementUV*> VertexUVList;
//
//		// �������� ����Ʈ
//		for (int iLayer = 0; iLayer < iNumLayer; iLayer++)
//		{
//			FbxLayer* pLayer = pFbxMesh->GetLayer(0);
//			if (pLayer->GetVertexColors() != nullptr) {}
//			if (pLayer->GetNormals() != nullptr) {}
//			if (pLayer->GetTangents() != nullptr) {}
//			if (pLayer->GetUVs() != nullptr) {
//				VertexUVList.push_back(pLayer->GetUVs());
//			}
//
//			if (pLayer->GetMaterials() != nullptr)
//			{
//				FbxLayerElementMaterial* fbxMaterial = pLayer->GetMaterials();
//				//	int iMtrlCount = fbxMaterial->mDirectArray->GetCount();
//				//	// ������͸��� ����
//				//	if (iMtrlCount > 1)
//				//	{
//				//		for (int iSub=0;iSub < iMtrlCount; iSub++)
//				//		{
//
//				//		}
//				//	}
//				//	else
//				//	{
//				//		FbxSurfaceMaterial* pFbxMaterial = pNode->GetMaterial(0);
//				//		FbxProperty prop= pFbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
//				//		if (prop.IsValid())
//				//		{
//				//			int iTexCount = prop.GetSrcObjectCount<FbxTexture>();
//				//			for (int iTex = 0; iTex < iTexCount; iTex++)
//				//			{
//				//				FbxTexture* pTex =	prop.GetSrcObject<FbxFileTexture>(iTex);
//				//				if (pTex == nullptr) continue;
//				//				FbxFileTexture* fileTexture =prop.GetSrcObject<FbxFileTexture>(iTex);
//				//				fbxFileTexList.push_back(fileTexture->GetFileName());
//				//			}						
//				//		}
//				//	}
//				//}
//			}
//
//		}
//		
//
//		int m_iNumPolygon = pFbxMesh->GetPolygonCount();
//		// ��������Ʈ �ּ�
//		FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
//		for (int iPoly = 0; iPoly < m_iNumPolygon; iPoly++)
//		{
//			// �ﰢ��, �簢��
//			int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
//			int m_iNumTriangle = iPolySize - 2;
//			int iCornerIndex[3];
//			for (int iTriangle = 0;
//				iTriangle < m_iNumTriangle;
//				iTriangle++)
//			{
//				// ��ġ �ε���
//				iCornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, 0);
//				iCornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, iTriangle + 2);
//				iCornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, iTriangle + 1);
//				// UV �ε���
//				int u[3];
//				u[0] = pFbxMesh->GetTextureUVIndex(iPoly, 0);
//				u[1] = pFbxMesh->GetTextureUVIndex(iPoly, iTriangle + 2);
//				u[2] = pFbxMesh->GetTextureUVIndex(iPoly, iTriangle + 1);
//
//				for (int iIndex = 0;
//					iIndex < 3;
//					iIndex++)
//				{
//					
//					PNCT_VERTEX  vertex;
//					FbxVector4 pos = pVertexPositions[iCornerIndex[iIndex]];
//					vertex.pos.x = pos.mData[0];
//					vertex.pos.y = pos.mData[2];
//					vertex.pos.z = pos.mData[1];
//
//					if (VertexUVList.size())
//					{
//						FbxLayerElementUV* pUVElement = VertexUVList[0];
//						FbxVector2 uv = ReadTextureCoord(
//							pFbxMesh, 1, pUVElement,
//							iCornerIndex[iIndex], u[iIndex]);
//						vertex.tex.x = uv.mData[0];
//						vertex.tex.y = 1.0f - uv.mData[1];
//					}
//					pMesh->m_pVertexList.push_back(vertex);
//				}
//			}
//		}
//	}
//}
//
//FbxVector2 JFbxObj::ReadTextureCoord(FbxMesh* pFbxMesh, DWORD dwVertexTextureCount, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex)
//{
//	FbxVector2 uv(0, 0);
//	if (dwVertexTextureCount < 1 || pUVSet == nullptr)
//	{
//		return uv;
//	}
//	int iVertexTextureCountLayer = pFbxMesh->GetElementUVCount();
//	FbxLayerElementUV* pFbxLayerElementUV = pFbxMesh->GetElementUV(0);
//
//	// �������� ����� 4�� ����, ������ ������ 6�� ������ �����Ѵ�.
//	// �׷��� �ؽ�ó ��ǥ�� ���� ���̾� ���� ������ �Ǵ� �������� ���еȴ�.
//	switch (pUVSet->GetMappingMode())
//	{
//	case FbxLayerElementUV::eByControlPoint: // ������ �� 1���� �ؽ�ó ��ǥ�� �ִ�.
//	{
//		switch (pUVSet->GetReferenceMode())
//		{
//		case FbxLayerElementUV::eDirect: // �迭���� ���� ��´�.
//		{
//			FbxVector2 fbxUv = pUVSet->GetDirectArray().GetAt(vertexIndex);
//			uv.mData[0] = fbxUv.mData[0];
//			uv.mData[1] = fbxUv.mData[1];
//			break;
//		}
//		case FbxLayerElementUV::eIndexToDirect: // �迭�� �ش��ϴ� �ε����� ���Ͽ� ��´�.
//		{
//			int id = pUVSet->GetIndexArray().GetAt(vertexIndex);
//			FbxVector2 fbxUv = pUVSet->GetDirectArray().GetAt(id);
//			uv.mData[0] = fbxUv.mData[0];
//			uv.mData[1] = fbxUv.mData[1];
//			break;
//		}
//		}
//		break;
//	}
//	case FbxLayerElementUV::eByPolygonVertex: // ���� �� 1���� ���� ��ǥ�� �ִ�.
//	{
//		switch (pUVSet->GetReferenceMode())
//		{
//		case FbxLayerElementUV::eDirect:
//		case FbxLayerElementUV::eIndexToDirect:
//		{
//			uv.mData[0] = pUVSet->GetDirectArray().GetAt(uvIndex).mData[0];
//			uv.mData[1] = pUVSet->GetDirectArray().GetAt(uvIndex).mData[1];
//			break;
//		}
//		}
//		break;
//	}
//	}
//	return uv;
//}
//void	JFbxObj::PreProcess(FbxNode* pNode)
//{
//	// pNode ���� ���
//	FbxSurfaceMaterial* pFbxMaterial = pNode->GetMaterial(0);
//	if (pFbxMaterial != nullptr)
//	{
//		JMtrl* pMtrl = new JMtrl;
//		pMtrl->pFbxMtrl = pFbxMaterial;
//		pMtrl->m_pFbxNode = pNode;
//		m_pFbxMaterialList.push_back(pMtrl);
//	}
//
//
//	int iNumChild = pNode->GetChildCount();
//	for (int iNode = 0; iNode < iNumChild; iNode++)
//	{
//		FbxNode* pChildNode = pNode->GetChild(iNode);
//		FbxNodeAttribute::EType type =
//			pChildNode->GetNodeAttribute()->GetAttributeType();
//		if (type == FbxNodeAttribute::eMesh)
//		{
//			m_pFbxNodeList.push_back(pChildNode);
//		}
//		PreProcess(pChildNode);
//	}
//}
//bool	JFbxObj::LoadObject(std::string filename)
//{
//	// todo  : �޸� ����;
//	m_pFbxManager = FbxManager::Create();
//	// �ͽ����� or ������;
//	FbxIOSettings* ios = FbxIOSettings::Create(m_pFbxManager, IOSROOT);
//	m_pFbxManager->SetIOSettings(ios);
//	//todo  : FbxImporter* m_pFbxImporter;
//	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
//	//todo  : FbxScene* m_pFbxScene;
//	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
//	INT iFileFormat = -1;
//	bool bRet = m_pFbxImporter->Initialize(filename.c_str(),
//		iFileFormat,
//		m_pFbxManager->GetIOSettings());
//	bRet = m_pFbxImporter->Import(m_pFbxScene);
//	FbxNode* m_pRootNode = m_pFbxScene->GetRootNode();
//	PreProcess(m_pRootNode);
//
//	//Create(L"..\\..\\data\\shader\\Shader.hlsl", "VS","PS");
//
//	for (int iMtrl = 0; iMtrl < m_pFbxMaterialList.size(); iMtrl++)
//	{
//		JMtrl* pMtrl = m_pFbxMaterialList[iMtrl];
//		LoadMaterial(pMtrl);
//	}
//
//	for (int iObj = 0; iObj < m_pFbxNodeList.size(); iObj++)
//	{
//		FbxNode* pNode = m_pFbxNodeList[iObj];
//		JMesh* pMesh = new JMesh;
//		m_pMeshList.push_back(pMesh);
//		ParseNode(pNode, pMesh);
//		pMesh->Create(L"..\\..\\data\\shader\\Shader.hlsl", "VS", "PS");
//	}
//	return bRet;
//}
//
////bool JFbxObj::PostRender(ID3D11DeviceContext* pContext, UINT iNumIndex)
////{
////	pContext->IASetPrimitiveTopology(
////		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
////	pContext->Draw(m_pVertexList.size(), 0);
////	return true;
////}
//
//bool JFbxObj::Release()
//{
//	for (int iObj = 0; iObj < m_pMeshList.size(); iObj++)
//	{
//		m_pMeshList[iObj]->Release();
//	}
//	for (int iObj = 0; iObj < m_pFbxMaterialList.size(); iObj++)
//	{
//		m_pFbxMaterialList[iObj]->Release();
//		delete m_pFbxMaterialList[iObj];
//	}
//	return true;
//}