#ifndef __RBSPOBJECT_H
#define __RBSPOBJECT_H

#include <stdio.h>
#include <list>
#include <thread>
#include "RTypes.h"
//#include "RPath.h"
#include "RLightList.h"
#include "RMeshMgr.h"
#include "RAnimationMgr.h"
#include "RMaterialList.h"
#include "ROcclusionList.h"
#include "RSolidBsp.h"
#include "RNavigationMesh.h"
#include "ABspObject.h"
class MZFile;
class MZFileSystem;

_NAMESPACE_REALSPACE2_BEGIN

///TODO: finish sorting this mess of a file, group all the bools/voids/etc together
class RBspObject : public ABspObject
{ 
public:
	ROpenFlag m_OpenMode;

	RBspObject();
	virtual ~RBspObject();

	void ClearLightmaps();

	// open �� �����ϸ� �⺻ Ȯ���ڷ� ������ Open...��ǵ��� ������� �θ���.
	virtual bool Open(const char *, const char* descExtension, ROpenFlag nOpenFlag=ROF_RUNTIME,RFPROGRESSCALLBACK pfnProgressCallback=NULL, void *CallbackParam=NULL) override;
	virtual bool IsVisible(rboundingbox &bb) override;		// occlusion �� ���� ������������ false �� ����.
	virtual bool Draw() override;
	virtual bool Pick(const rvector &pos, const rvector &dir, RBSPPICKINFO *pOut, DWORD dwPassFlag = RM_FLAG_ADDITIVE | RM_FLAG_USEOPACITY | RM_FLAG_HIDE) override;
	virtual bool PickTo(const rvector &pos, const rvector &to, RBSPPICKINFO *pOut, DWORD dwPassFlag = RM_FLAG_ADDITIVE | RM_FLAG_USEOPACITY | RM_FLAG_HIDE) override;
	virtual bool PickOcTree(rvector &pos, rvector &dir, RBSPPICKINFO *pOut, DWORD dwPassFlag = RM_FLAG_ADDITIVE | RM_FLAG_USEOPACITY | RM_FLAG_HIDE) override;
	// origin ���� targetpos �� �̵��ϴµ� �̲������� �����ؼ� targetpos �� �����ؼ� �������ش�.
	virtual bool CheckWall(rvector &origin, rvector &targetpos, float fRadius, float fHeight = 0.f, RCOLLISIONMETHOD method = RCW_CYLINDER, int nDepth = 0, rplane *pimpactplane = NULL) override;
	// solid ���� �ȿ� �ִ��� ?
	virtual bool CheckSolid(rvector &pos, float fRadius, float fHeight = 0.f, RCOLLISIONMETHOD method = RCW_CYLINDER) override;
	virtual bool GetShadowPosition(rvector& pos_, rvector& dir_, rvector* outNormal_, rvector* outPos_) override;

	bool OpenDescription(const char *);				// ��ũ���� ����		.xml ������ ����.
	bool OpenRs(const char *);						// ���� ���� ��������	.rs ������ ����. 
	bool OpenBsp(const char *);						// bsp ���� ����		.bsp ������ ����. 
	bool OpenLightmap();							// ����Ʈ�� ��������	.lm  ������ ����.
//	bool OpenPathNode(const char *);				// ��� ��������		.pat ������ ����.
	bool OpenCol(const char *);						// collision ���� ����	.col ������ ����. 
	bool OpenNav(const char *);						// �׺���̼Ǹ� �������� .nav ������ ����.
	bool DrawLight(RSBspNode *pNode, int nMaterial);
	bool GenerateLightmap(const char *filename, int nMaxLightmapSize, int nMinLightmapSize, int nSuperSample, float fToler, RGENERATELIGHTMAPCALLBACK pProgressFn = NULL);
	bool GetWireframeMode() { return m_bWireframe; }
	bool GetShowLightmapMode() { return m_bShowLightmap; }

	virtual void OptimizeBoundingBox() override;	// ������ ��Ÿ�ӿ����� �����ٿ���ڽ��� Ÿ��Ʈ�ϰ� ����ش�.
	virtual void DrawObjects() override;
	virtual void DrawLight(D3DLIGHT9 *pLight) override;			// ���� ó����.. ��Ƽ �н��� ���׸���.
	virtual void SetWireframeMode(bool bWireframe) override { m_bWireframe = bWireframe; }
	virtual void OnInvalidate() override;
	virtual void OnRestore() override;
	virtual void LightMapOnOff(bool b) override;

	void SetObjectLight(rvector pos);
	void SetCharactorLight(rvector pos);
	void DrawBoundingBox();
	void DrawOcclusions();
	void DrawNormal(int nIndex, float fSize = 1.f);	// index : convex polygon index

	void DrawCollision_Polygon();
	void DrawCollision_Solid();

	void DrawSolid();					// ��� solid ������ �׸���
	void DrawSolidNode();				// ������ �浹�� ��带 �׸���
	void DrawColNodePolygon(rvector &pos);

	void DrawNavi_Polygon();
	void DrawNavi_Links();
	void GetNormal(int nConvexPolygon, rvector &position, rvector *normal);
	void test_MakePortals();
	virtual void SetMapObjectOcclusion(bool b) override { m_bNotOcclusion = b; }
	void SetShowLightmapMode(bool bShowLightmap) { m_bShowLightmap = bShowLightmap; }

	//bool GeneratePathData(const char *filename,float fAngle, float fToler);
	//void GeneratePathNodeTable();

	static void SetDrawLightMap(bool b);
	static void DestroyShadeMap();



	// ���� ��ǥ pos ���� dir ������ �������� ���� pick !
	// PickTo() ���� ������ ��ŷ�̹Ƿ� �Լ��� �������� ����� true�� ������ �� �Ÿ� �˻縦 �߰��� ���־�� ���ϴ� ����� ���� �� �ִ�


	// pathnode �� ����..
	/*
	// ȭ�� x,y ��ǥ�� �ִ� pathnode �� �����Ѵ�..
	bool PickPathNode(int x,int y,RPathNode **pOut,rvector *ColPos);
	// ���� ��ǥ from ���� to �� ���� �������� ���� pick pathnode !
	bool PickPathNode(rvector &from,rvector &to,RPathNode **pOut,rvector *ColPos);

	RPathList *GetPathList() { return &m_PathNodes; }
	RPathNode *GetPathNode(RSBspNode *pNode,int nIndex);
*/

	// �ش� ��ġ�� lightmap �� ����.
	DWORD GetLightmap(rvector &Pos,RSBspNode *pNode,int nIndex);

	// �ش� �������� Material�� ����.
	virtual RBSPMATERIAL *GetMaterial(RSBspNode *pNode,int nIndex) override		{ return GetMaterial(pNode->pInfo[nIndex].nMaterial); }
	virtual RBSPMATERIAL *GetMaterial(int nIndex) override;

	// material �� ����.
	int	GetMaterialCount()	{ return m_nMaterial; }

	virtual RMapObjectList	*GetMapObjectList() override { return &m_ObjectList; }
	void SetMapObjectList(RMapObjectList* objectList) { m_ObjectList =  *objectList; }
	virtual RDummyList		*GetDummyList()	override	 { return &m_DummyList; }
	RBaseTexture *GetBaseTexture(int n) { if(n>=0 && n<m_nMaterial) return m_pMaterials[n].texture; return NULL; }

	RLightList *GetMapLightList() { return &m_StaticMapLightList; }
	virtual RLightList *GetObjectLightList() override { return &m_StaticObjectLightList; }
	virtual RLightList *GetSunLightList() override { return &m_StaticSunLigthtList; }

	RSBspNode *GetOcRootNode() { return m_pOcRoot; }
	virtual RSBspNode *GetRootNode() override { return m_pBspRoot; }

	rvector GetDimension();

	int	GetVertexCount()		{ return m_nVertices; }
	int	GetPolygonCount()		{ return m_nPolygon; }
	int GetNodeCount()			{ return m_nNodeCount; }
	int	GetBspPolygonCount()	{ return m_nBspPolygon; }
	int GetBspNodeCount()		{ return m_nBspNodeCount; }
	int GetConvexPolygonCount() { return m_nConvexPolygon; }
	int GetLightmapCount()		{ return m_nLightmap; }
	float GetUnusedLightmapSize(int index) { return m_LightmapList[index]->m_fUnused; }


	
	// ��ġ���� �ٴڿ� ��� ���� ���Ѵ�.
	virtual rvector GetFloor(rvector &origin,float fRadius,float fHeight,rplane *pimpactplane=NULL) override;
	


	// �ʿ� ��ϵ� ������Ʈ �̿��� ������Ʈ ó�� ( ĳ���� ����ȭ��� )



	virtual RMeshMgr*	GetMeshManager() override {
		return &m_MeshList;
	}


	// debug �� ���� �׷������Ѱ͵�.
	//void DrawPathNode();


	RSolidBspNode *GetColRoot() { return m_pColRoot; }


	virtual FogInfo GetFogInfo() override { return m_FogInfo;}
	virtual list<AmbSndInfo*> GetAmbSndList() override { return m_AmbSndInfoList;	}


	static bool CreateShadeMap(const char *szShadeMap);

	RDEBUGINFO *GetDebugInfo() { return &m_DebugInfo; }
	virtual RNavigationMesh* GetNavigationMesh() override { return &m_NavigationMesh; }

	string m_filename;
private:

	string m_descfilename;
	
	// �����͹� ����׸� ���� ��� 
	bool m_bWireframe;
	bool m_bShowLightmap;
// ����ȣ������� ����..
	bool DrawTNT(RSBspNode *bspNode,int nMaterial);	// no hardware T&L
	bool Draw(RSBspNode *bspNode,int nMaterial);

	void SetDiffuseMap(int nMaterial);

	bool Pick(RSBspNode *pNode, const rvector &v0, const rvector &v1);
//	bool PickCol(RSolidBspNode *pNode,rvector v0,rvector v1);
//	bool PickPathNode(RSBspNode *pNode);
	bool PickShadow(rvector &pos,rvector &to,RBSPPICKINFO *pOut);
	bool PickShadow(RSBspNode *pNode,rvector &v0,rvector &v1);

	void ChooseNodes(RSBspNode *bspNode);
	int ChooseNodes(RSBspNode *bspNode,rvector &center,float fRadius);			// ���ϰ��� ���õ� ����� ����
//	void TraverseTreeAndRender(RSBspNode *bspNode);
//	void DrawNodeFaces(RSBspNode *bspNode);

	inline RSBspNode *GetLeafNode(rvector &pos) { return m_pBspRoot->GetLeafNode(pos); }

	//void GetFloor(rvector *ret,RSBspNode *pNode,rvector &origin,const rvector &diff);

// for loading
	bool ReadString(MZFile *pfile,char *buffer,int nBufferSize);
	bool Open_Nodes(RSBspNode *pNode,MZFile *pfile);
	bool Open_ColNodes(RSolidBspNode *pNode,MZFile *pfile);
	bool Open_MaterialList(MXmlElement *pElement);
	bool Open_LightList(MXmlElement *pElement);
	bool Open_ObjectList(MXmlElement *pElement);
	bool Open_DummyList(MXmlElement *pElement);
//	bool Open_LightList(MZFile *pfile);
	bool Open_ConvexPolygons(MZFile *pfile);
	bool Open_OcclusionList(MXmlElement *pElement);
public:
	bool Make_LenzFalreList();
	///Custom: update to make objects move in game
	void OnUpdate(float fElapsed);
protected:
	bool Set_Fog(MXmlElement *pElement);
	bool Set_AmbSound(MXmlElement *pElement);

	void CreateRenderInfo();
	void CreatePolygonTableAndIndexBuffer();
	void CreatePolygonTableAndIndexBuffer(RSBspNode *pNode);
	void Sort_Nodes(RSBspNode *pNode);

	bool CreateVertexBuffer();
	bool UpdateVertexBuffer();

	bool CreateIndexBuffer();
	bool UpdateIndexBuffer();

	bool CreateDynamicLightVertexBuffer();
	void InvalidateDynamicLightVertexBuffer();
	bool FlushLightVB();
	bool LockLightVB();
	LPDIRECT3DVERTEXBUFFER9 m_pDynLightVertexBuffer;

	static RBaseTexture *m_pShadeMap;

// ���� Ʈ��
	BSPVERTEX *m_pBspVertices,*m_pOcVertices;
	WORD	*m_pBspIndices,*m_pOcIndices;
	RSBspNode *m_pBspRoot,*m_pOcRoot;
	RPOLYGONINFO *m_pBspInfo,*m_pOcInfo;
	int m_nPolygon,m_nNodeCount,m_nVertices,m_nIndices;
	int m_nBspPolygon,m_nBspNodeCount,m_nBspVertices,m_nBspIndices;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	
// Materials & texture map
	int m_nMaterial;
	RBSPMATERIAL *m_pMaterials;

	rplane m_localViewFrustum[6];

// occlusions
	ROcclusionList m_OcclusionList;

	/*
	int m_nOcclusion;
	ROcclusion	*m_pOcclusion;
	*/


// ������ �ؽ��� �޸𸮿� �ö󰡴� ����Ʈ��
	int							m_nLightmap;
	LPDIRECT3DTEXTURE9			*m_ppLightmapTextures;
	vector<RBspLightmapManager*> m_LightmapList;

// lightmap �ؽ�ó�� ������ �ʿ��� ��..
	void CalcLightmapUV(RSBspNode *pNode,int *pLightmapInfo,vector<RLIGHTMAPTEXTURE*> *pLightmaps);

// interpolated normal
	void GetNormal(RCONVEXPOLYGONINFO *poly,rvector &position,rvector *normal,int au,int av);
// interpolated uv
	void GetUV(rvector &Pos,RSBspNode *pNode,int nIndex,float *uv);

// ���� ������ ����
	int					m_nConvexPolygon,m_nConvexVertices;
	rvector				*m_pConvexVertices;
	rvector				*m_pConvexNormals;
	RCONVEXPOLYGONINFO	*m_pConvexPolygons;

// ����������..
	rvector		m_AmbientLight;
	RLightList	m_StaticMapLightList;
	RLightList	m_StaticObjectLightList;
	RLightList	m_StaticSunLigthtList;

// pathfinding �� �ʿ��� �ڷ�
//	RPathList m_PathNodes;

// �ʿ� �⺻������ �ִ� object ��..
	RMeshMgr			m_MeshList;
	RAnimationMgr		m_AniList;
	RMapObjectList		m_ObjectList;
	bool				m_bNotOcclusion;

// �浹üũ�� ��
	RSolidBspNode		*m_pColRoot;
	rvector				*m_pColVertices;

// �׺���̼ǿ� ��
	RNavigationMesh		m_NavigationMesh;


// ���� ����Ʈ
	RDummyList	m_DummyList;

// Fog����
	FogInfo m_FogInfo;

// ���� ����
	list<AmbSndInfo*>	m_AmbSndInfoList;

// ����� ����
	RDEBUGINFO			m_DebugInfo;
};

_NAMESPACE_REALSPACE2_END


#endif