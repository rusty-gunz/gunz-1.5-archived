#include "stdafx.h"

#include "ItemThumbnailGenerator.h"

#include "MainDoc.h"
#include "MainView.h"

#include <MMSystem.h>

#include "MDebug.h"
#include "RealSpace2.h"

#include "RMtrl.h"

#include "RMeshMgr.h"
#include "RAnimationMgr.h"
#undef pi
#include "RVisualMeshMgr.h"

#include "RBspObject.h"
#include "RMaterialList.h"

#include "ZItemList.h"
#include "Thumbnail.h"
#include "ItemDlg.h"
extern CItemDlg* g_pItemDlg;

#include ".\mainview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

_USING_NAMESPACE_REALSPACE2

#include "Camera.h"

CMainView* g_pView = NULL;

#define VIEW_WIDTH 640
#define VIEW_HEIGHT 480

// �� �������� ������ ������ ����� �̹����� �� �簢������ ����صд�
// (��� ���͸��� ���� �̹����� �ε巴�� �ϱ� ���ؼ� ����� ������� ũ�� ��´�)
static int rx1 = int((VIEW_WIDTH * 0.5f) - ((THUMBNAILSIZE*2) * 0.5f));
static int ry1 = int((VIEW_HEIGHT* 0.5f) - ((THUMBNAILSIZE*2) * 0.5f));
static int rx2 = rx1 + (THUMBNAILSIZE*2);
static int ry2 = ry1 + (THUMBNAILSIZE*2);


// CMainView

IMPLEMENT_DYNCREATE(CMainView, CView)

BEGIN_MESSAGE_MAP(CMainView, CView)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CMainView ����/�Ҹ�

CMainView::CMainView()
{
	g_pView = this;
	GetUpdateNotifier()->Register(this);
}

CMainView::~CMainView()
{
}

BOOL CMainView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	// Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMainView �׸���

void CMainView::OnDraw(CDC* /*pDC*/)
{
	CMainDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	static bool bFirst = true;

	if (bFirst)
	{
		bFirst = false;

		// OnInitialUpdate������ ���ٰ� ���� ��������� ���� �������� �ùٷ� ������� �ȵǾ ���⼭ ��

		// Ŭ���̾�Ʈ ���� �������� ���������� ũ�� ����
		RECT rcWindow, rcClient;
		AfxGetMainWnd()->GetWindowRect(&rcWindow); // ��ü ������ ũ��
		GetClientRect(&rcClient);         // Ŭ���̾�Ʈ ũ��
		int nWidth  = rcClient.right - rcClient.left;
		int nHeight = rcClient.bottom - rcClient.top;
		// ���� Ŭ���̾�Ʈ ũ��� ���ϴ� Ŭ���̾�Ʈ ũ�⸦ ��
		int nOffWidth  = nWidth  - VIEW_WIDTH;
		int nOffHeight = nHeight - VIEW_HEIGHT;
		// ���̳��¸�ŭ�� ���ؼ� ��ü ����� �����Ѵ�
		AfxGetMainWnd()->MoveWindow(rcWindow.left, rcWindow.top,
			rcWindow.right - rcWindow.left - nOffWidth,
			rcWindow.bottom - rcWindow.top - nOffHeight, TRUE);

		// �� ���̾�α� ��ġ ����
		CRect rcMainWnd;
		AfxGetMainWnd()->GetWindowRect(&rcMainWnd);
		g_pItemDlg->SetWindowPos(NULL, rcMainWnd.right+5, rcMainWnd.top, 0, 0, SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);


		Init();
	}
}


// CMainView ����

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainDoc* CMainView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDoc)));
	return (CMainDoc*)m_pDocument;
}
#endif //_DEBUG



//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

RMODEPARAMS mparams = { VIEW_WIDTH,VIEW_HEIGHT,false,D3DFMT_A1R5G5B5 };

LPDIRECT3DDEVICE9 g_dev = NULL;
CTCamera g_camera;

float g_Wheel;

D3DXVECTOR3	g_light_pos;

CD3DArcBall	g_ArcBall;

D3DXMATRIX	g_matWorld;
D3DXMATRIX	g_matView;

ZItemList	g_itemlist;

RMeshMgr		g_mesh_mgr;
RVisualMeshMgr	g_vmesh_mgr;
RAnimationMgr	g_ani_mgr;

RMeshMgr	g_weaponmesh_mgr;
RMeshMgr	g_charmesh_mgr;


void SetLight(RVisualMesh* pVMesh,int mode,rvector& pos)
{
	D3DLIGHT9 light;

	ZeroMemory( &light, sizeof(D3DLIGHT9) );

	light.Type        = D3DLIGHT_POINT;

	light.Diffuse.r   = 1.0f;
	light.Diffuse.g   = 1.0f;
	light.Diffuse.b   = 1.0f;

	light.Specular.r	= 1.f;
	light.Specular.g	= 1.f;
	light.Specular.b	= 1.f;

	{	// ��⸦ �ִ�� ���ֱ� ���ؼ� �����Ʈ�� ��� �ְ����� �������ش�.
		light.Ambient.r		= 1.f;
		light.Ambient.g		= 1.f;
		light.Ambient.b		= 1.f;
	}

	light.Position.x   = pos.x;
	light.Position.y   = pos.y;
	light.Position.z   = pos.z;

	light.Range        = 1000.0f;

	light.Attenuation0 = 0.9f;
	light.Attenuation1 = 0.0f;

	pVMesh->SetLight(mode,&light,false);
}

void ResetCamera()
{
	g_camera.Reset();
}

bool CMainView::Init()
{
	InitLog( MLOGSTYLE_DEBUGSTRING | MLOGSTYLE_FILE );

	CWnd* _hWnd = this;
	if (!_hWnd) return false;

	RECT rect,rect2;

	_hWnd->GetClientRect(&rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	mparams.nWidth	= w;
	mparams.nHeight = h;

	RInitDisplay(_hWnd->m_hWnd,&mparams);
	
	// ������� DC�� �����ϱ� ���� �� ���� �ɼ��� �ְ� ����
	g_d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	RResetDevice(&mparams);

	_hWnd->GetWindowRect(&rect);//��������ġ

	GetWindowRect(&rect2);

	g_dev = RGetDevice();

	g_pItemDlg->InitSwapChain();

	//////////////////////////////////////////////////////////
	// ĳ���� �ε��� ũ�⿡ �°� ��ġ����

	g_camera.Create(w,h);

	//////////////////////////////////////////////////////////
	// ĳ���� �ε��� ũ�⿡ �°� ��ġ����

	g_light_pos = D3DXVECTOR3(0.f,150.f,-480.f);//ĳ���� �ٿ�� �ڽ��� �߰� ����..


	g_dev->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_COLORVALUE( 0.8f, 0.8f, 0.8f, 1.0f ) );

	//////////////////////////////////////////////////////////

	g_ArcBall.SetWindow( w,h, 0.85f );
	g_ArcBall.SetRadius( 2.5f );

	D3DXMatrixIdentity(&g_matWorld);
	D3DXMatrixIdentity(&g_matView);


	SetClearColor(0xfff00ff);

	g_camera.Reset();

	RMesh::SetToolMesh(true);//������ ���� ���̶�°� �˸���~

	// zitem.xml �ε�
	g_itemlist.Load();

	// weapon.xml �ε�
	g_weaponmesh_mgr.LoadXmlList("Model/weapon.xml");

	// character.xml �ε�
	g_charmesh_mgr.LoadXmlList("Model/character.xml");

	// �չ� ���� �ִϸ��̼� �ε�
	g_ani_mgr.Add("handsfeet", "itemThumbnailGenerator/thumbnail_handsfeet.elu.ani", 0);
	g_ani_mgr.Add("standard", "itemThumbnailGenerator/thumbnail_std.elu.ani", 0);

	g_pItemDlg->UpdateItemList();
	NextZItem(true);

	return true;
}

void CMainView::Finish()
{
	g_pItemDlg->ReleaseSwapChain();

	g_weaponmesh_mgr.DelAll();
	g_charmesh_mgr.DelAll();
	g_ani_mgr.DelAll();

	RCloseDisplay();
}

void CMainView::OnReturnKey()
{
	ZItem* pItem = g_itemlist.GetCurrZItem();
	if (!pItem) return;

	CString strPath;
	MakeThumbnailFilename(pItem->m_nID, strPath);
	SaveThumbnail((LPCTSTR)strPath);
	g_camera.GetCameraSetting(pItem->m_cameraSetting);

	GetUpdateNotifier()->NotifyListeners(pItem->m_nID);

	// �۾��ϴ� ���õ��� xml�� ��������
	g_itemlist.SaveConfigureXml();
}

void CMainView::Update()
{
	RRESULT isOK=RIsReadyToRender();
	if(isOK==R_NOTREADY)
		return;

	ApplyMouseMovement();

	g_camera.Update();
	g_vmesh_mgr.Frame();

	ZItem* pItem = g_itemlist.GetCurrZItem();

	// ����Ű�� ����� ����
	if (GetActiveWindow() == AfxGetMainWnd() &&
		GetAsyncKeyState(VK_RETURN) & 0x8001 && pItem)
	{
		OnReturnKey();
	}

	// ���κ� ������
	// �ٸ� ���� ����ü�� �������� �־��� ������ ���� ����ü������ ���� Ÿ�� ����
	LPDIRECT3DSURFACE9 pBackBuffer=NULL;
	g_dev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	g_dev->SetRenderTarget(0, pBackBuffer);
	SAFE_RELEASE(pBackBuffer);

	Render();

	DrawTargetRect();

	RFlip();

	// ��ȭ������ ����� ������ ������
	g_pItemDlg->RenderPreview();
}

void CMainView::Render()
{
	g_dev->SetRenderState( D3DRS_ZENABLE ,TRUE );
	g_dev->SetRenderState( D3DRS_LIGHTING, TRUE );

	ZItem* pItem = g_itemlist.GetCurrZItem();
	if (pItem && !g_vmesh_mgr.m_node_table.empty())
	{
		RVisualMesh* pvmesh = g_vmesh_mgr.GetFast(0);
		SetLight(pvmesh, 0, g_light_pos);

		D3DXMATRIX matWorld;

		D3DXMATRIX matPos, matRot, matScale;
		D3DXMatrixTranslation(&matPos, pItem->m_vPos.x, pItem->m_vPos.y, pItem->m_vPos.z);
		D3DXMatrixRotationYawPitchRoll(&matRot, pItem->m_vRot.y, pItem->m_vRot.x, pItem->m_vRot.z);
		D3DXMatrixScaling(&matScale, pItem->m_vScale.x, pItem->m_vScale.y, pItem->m_vScale.z);

		matWorld = matScale * matRot * matPos;

		pvmesh->SetWorldMatrix( matWorld );
		pvmesh->Render();

		// �� �ڷ��� ����� �ι�° pos rot scale ������ ����ؼ� �ѹ� �� �׷��ش�
		if (pItem->m_strWeaponType == "pistolx2" ||
			pItem->m_strWeaponType == "revolverx2" ||
			pItem->m_strWeaponType == "smgx2" ||
			pItem->m_strWeaponType == "doublekatana")
		{
			D3DXMatrixTranslation(&matPos, pItem->m_vPos2.x, pItem->m_vPos2.y, pItem->m_vPos2.z);
			D3DXMatrixRotationYawPitchRoll(&matRot, pItem->m_vRot2.y, pItem->m_vRot2.x, pItem->m_vRot2.z);
			D3DXMatrixScaling(&matScale, pItem->m_vScale2.x, pItem->m_vScale2.y, pItem->m_vScale2.z);

			matWorld = matScale * matRot * matPos;

			pvmesh->SetWorldMatrix( matWorld );
			pvmesh->Render();
		}
	}
}

void CMainView::DrawTargetRect()
{
	// ���� ������ ����Ϸ� crop�Ǿ� ���� �κ��� ���� ǥ�����ش�

	IDirect3DSurface9* pBackBuffer = NULL;
	if (SUCCEEDED(g_dev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer)))
	{
		HDC hdc;
		if (SUCCEEDED(pBackBuffer->GetDC(&hdc)))
		{
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Rectangle(hdc, rx1-1, ry1-1, rx2+1, ry2+1);
			SelectObject(hdc, oldBrush);
			pBackBuffer->ReleaseDC(hdc);
		}
		pBackBuffer->Release();
	}
}

void CMainView::UpdateSelection(int id)
{
	ZItem* pItem = g_itemlist.GetZItem(id);
	if (!pItem) return;
	if (pItem->m_strMeshName.empty() && 
		pItem->m_strAvatarHeadMeshName.empty() && 
		pItem->m_strAvatarChestMeshName.empty())
	{
		g_vmesh_mgr.DelAll();
		return;
	}

	// �� �������� �޽ø� ã�Ƽ� visualmesh�� �����
	// ���� �޽ÿ��� ã�ƺ���
	RMesh* pMesh = NULL;
	if (pMesh = FindWeaponMesh(pItem))
	{
		MakeWeaponVisualMesh(pMesh);
	}
	else if (pMesh = FindCharMesh(pItem))
	{
		MakeCharVisualMesh(pMesh, pItem->m_strSlot.c_str(), 
			pItem->m_strMeshName.c_str(), 
			pItem->m_strAvatarHeadMeshName.c_str(), 
			pItem->m_strAvatarChestMeshName.c_str());
	}
	else
	{
		mlog("mesh_name[%s]�� �ش��ϴ� �޽ø� ã�� �� �����ϴ�.\n", pItem->m_strMeshName.c_str());
		g_vmesh_mgr.DelAll();
		return;
	}

	// �� �����ۿ� ������ ���� ī�޶� ������ ����
	if (true == pItem->m_cameraSetting.bInitialized)
		g_camera.SetCameraSetting(pItem->m_cameraSetting);
}

void CMainView::NextZItem(bool bForward)
{
	if (bForward)
		g_itemlist.NextZItem();
	else
		g_itemlist.PrevZItem();

	ZItem* pItem = g_itemlist.GetCurrZItem();
	if (!pItem) return;
	GetUpdateNotifier()->NotifyListeners(pItem->m_nID);

	if (pItem->m_strMeshName.empty()) {
		g_vmesh_mgr.DelAll();
		return;
	}
}

RMesh* CMainView::FindWeaponMesh(ZItem* pItem)
{
	char* szMeshName = (char*)pItem->m_strMeshName.c_str();
	RMesh* pMesh = NULL;

	pMesh = g_weaponmesh_mgr.Get(szMeshName);
	if (pMesh)
		return pMesh;

	return NULL;
}

RMesh* CMainView::FindCharMesh(ZItem* pItem)
{
	RMesh* pMesh = NULL;

	char* szCharMeshName = NULL;
	if (pItem->m_nSex == SEX_MALE)			szCharMeshName = "heroman1";
	else if (pItem->m_nSex == SEX_FEMALE)	szCharMeshName = "herowoman1";

	if (szCharMeshName)
	{
		RMesh* pBaseMesh = g_charmesh_mgr.Get(szCharMeshName);
		RMeshNode* pMeshNode = pBaseMesh->GetPartsNode((char*)pItem->m_strMeshName.c_str());
		if (pMeshNode)
			return pBaseMesh;

		// �Ϲ� �� �޽��� ��ã�Ҵٸ� �ƹ�Ÿ �޽��� ã�ƺ���
		pMeshNode = pBaseMesh->GetPartsNode((char*)pItem->m_strAvatarHeadMeshName.c_str());
		if (pMeshNode)
			return pBaseMesh;
	}

	// �׷��� ������ �̰� ĳ���� �޽��� �ƴѰ�����
	return NULL;
}

bool CMainView::MakeWeaponVisualMesh(RMesh* pMesh)
{
	if (!pMesh) return false;

	if (pMesh->m_isPhysiqueMesh)
		pMesh->m_isCharacterMesh = true;

	g_vmesh_mgr.DelAll();
	int vid = g_vmesh_mgr.Add(pMesh);

	RVisualMesh* pvmesh = g_vmesh_mgr.GetFast(vid);
	if (!pvmesh) return false;

	pvmesh->SetCheckViewFrustum(false);

	RMesh::m_OnlyRenderPartsType = eq_parts_end;

	return true;
}

bool CMainView::MakeCharVisualMesh(RMesh* pBaseMesh, const char* szSlot, const char* szMeshName, const char* szAvatarHeadMeshName, const char* szAvatarChestMeshName)
{
	if (!pBaseMesh) return false;

	if (pBaseMesh->m_isPhysiqueMesh)
		pBaseMesh->m_isCharacterMesh = true;

	g_vmesh_mgr.DelAll();
	int vid = g_vmesh_mgr.Add(pBaseMesh);

	RVisualMesh* pvmesh = g_vmesh_mgr.GetFast(vid);
	if (!pvmesh) return false;

	RMeshPartsType partsType = eq_parts_end;

	if (0==stricmp(szSlot, "avatar"))
	{
		pvmesh->SetParts(eq_parts_head,  pBaseMesh->GetPartsNode((char*)szAvatarHeadMeshName));
		pvmesh->SetParts(eq_parts_chest, pBaseMesh->GetPartsNode((char*)szAvatarChestMeshName));

		pvmesh->m_bSkipRenderFaceParts = true;
	}
	else
	{
		if (0==stricmp(szSlot, "head"))		partsType=eq_parts_head;
		if (0==stricmp(szSlot, "chest"))	partsType=eq_parts_chest;
		if (0==stricmp(szSlot, "hands"))	partsType=eq_parts_hands;
		if (0==stricmp(szSlot, "legs"))		partsType=eq_parts_legs;
		if (0==stricmp(szSlot, "feet"))		partsType=eq_parts_feet;

		_ASSERT(partsType!=eq_parts_end);
		pvmesh->SetParts(partsType, pBaseMesh->GetPartsNode((char*)szMeshName));

		pvmesh->m_bSkipRenderFaceParts = false;
	}

	pvmesh->SetCheckViewFrustum(false);

	// �ǻ� elu���� �� ��Ʈ�� ���� �޽ð� ���� ����ִ�.
	// ���� �̰� �ǻ�������̶�� �� item�� ����Ű�� ���� ������ �������ϵ��� �����ϱ�
	RMesh::m_OnlyRenderPartsType = eq_parts_end;
	//if (0==stricmp(szSlot, "head"))		RMesh::m_OnlyRenderPartsType=eq_parts_head; // �Ӹ��� �󱼵� ���;� �ϹǷ� �׳� �� �׸���
	if (0==stricmp(szSlot, "chest"))	RMesh::m_OnlyRenderPartsType=eq_parts_chest;
	if (0==stricmp(szSlot, "hands"))	RMesh::m_OnlyRenderPartsType=eq_parts_hands;
	if (0==stricmp(szSlot, "legs"))		RMesh::m_OnlyRenderPartsType=eq_parts_legs;
	if (0==stricmp(szSlot, "feet"))		RMesh::m_OnlyRenderPartsType=eq_parts_feet;
	//if (0==stricmp(szSlot, "avatar"))	RMesh::m_OnlyRenderPartsType=eq_parts_avatar;

	// ��/���� ��Ƽ� ���� �ϴϱ� �չ��� ����� �ִ� �ִϸ��̼��� �̿�����
	RAnimation* pAni = NULL;
	if (0==stricmp(szSlot, "hands") ||
		0==stricmp(szSlot, "feet"))
		pAni = g_ani_mgr.GetAnimation("handsfeet");
	else
		pAni = g_ani_mgr.GetAnimation("standard");

	_ASSERT(pAni);
	pvmesh->SetAnimation(pAni);
	pvmesh->Stop();	// �ִ��� ù�����Ӹ� ���� ������..

	return true;
}

void CMainView::SaveThumbnail(const char* szPath)
{
	LPDIRECT3DTEXTURE9 pTex1(0), pTex2(0);
	LPDIRECT3DSURFACE9 pSurf1(0), pSurf2(0), pSurfOrig(0);
	RECT rcSrc = { rx1, ry1, rx2, ry2 };

	g_dev->GetRenderTarget( 0, &pSurfOrig );

	// ����ۿ� ���� ũ���� ����Ÿ�� �ؽ�ó
	HRESULT hr = D3DXCreateTexture(g_dev, VIEW_WIDTH, VIEW_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &pTex1);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;

	hr = pTex1->GetSurfaceLevel(0, &pSurf1);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;

	g_dev->SetRenderTarget(0, pSurf1);

	// �������� clear
	g_dev->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,0xFF000000,1.0f,0.0f);

	// ����ۿ� �ϵ��� �޽� ������
	Render();

	// ���� ������� ũ��� ���� �ؽ�ó
	hr = D3DXCreateTexture(g_dev, THUMBNAILSIZE, THUMBNAILSIZE, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTex2);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;

	hr = pTex2->GetSurfaceLevel(0, &pSurf2);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;

	// surface to surface ���� (�̶� ��� ���͸��� �Կ��� �ε巴�� ���̴� ���� ��ǥ)
	D3DXLoadSurfaceFromSurface(pSurf2, NULL, NULL, pSurf1, NULL, &rcSrc, D3DX_FILTER_TRIANGLE, 0xFF000000);

	// �ؽ�ó ���Ϸ� ����
	hr = D3DXSaveTextureToFile(szPath, D3DXIFF_DDS, pTex2, NULL);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;

	/*
	D3DXSaveTextureToFile("d:\\test1.bmp", D3DXIFF_BMP, pTex1, NULL);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;
	D3DXSaveTextureToFile("d:\\test2.bmp", D3DXIFF_BMP, pTex2, NULL);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;
	D3DXSaveTextureToFile("d:\\test1.dds", D3DXIFF_DDS, pTex1, NULL);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;
	D3DXSaveTextureToFile("d:\\test2.dds", D3DXIFF_DDS, pTex2, NULL);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;//*/

SAVETHUMBNAIL_ERROR:
	// ������
	g_dev->SetRenderTarget( 0, pSurfOrig );

	SAFE_RELEASE(pSurfOrig);
	SAFE_RELEASE(pSurf2);
	SAFE_RELEASE(pTex2);
	SAFE_RELEASE(pSurf1);
	SAFE_RELEASE(pTex1);

	if (hr != D3D_OK)
		mlog("����� ���� ��� ����!(%s)\n", szPath);

/*
	// ����� ���ɾ ���� ������ ���Ϸ� �����ϴ� ��� (�ػ󵵰� �ʹ� ���� �ֺ� ����ó���� ������� ����)
	RECT rc = {rx1, ry1, rx2, ry2};

	LPDIRECT3DSURFACE9 pBackBuffer = NULL;
	HRESULT hr = g_dev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;

	hr = D3DXSaveSurfaceToFile(szPath, D3DXIFF_BMP, pBackBuffer, NULL, &rc);
	if (hr != D3D_OK) goto SAVETHUMBNAIL_ERROR;

	pBackBuffer->Release();
	return;

SAVETHUMBNAIL_ERROR:
	mlog("����� ���� ��� ����!(%s)\n", szPath);*/
}

// CMainView �޽��� ó����

BOOL CMainView::PreTranslateMessage(MSG* pMsg)
{
	g_ArcBall.HandleMouseMessages( pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam );

	if( pMsg->message == WM_MOUSEWHEEL ) {

		short zDelta = (short)HIWORD(pMsg->wParam);
		g_Wheel += zDelta;

		if(g_Wheel != 0) {

			g_camera.m_dist = (-g_Wheel * 0.1f) + g_camera.m_dist;
			g_Wheel = 0;
		}
	}

	return CView::PreTranslateMessage(pMsg);
}

void CMainView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}

void CMainView::OnDestroy()
{
	CView::OnDestroy();

	Finish();
}

void CMainView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_SPACE)
		NextZItem(true);
	if (nChar == VK_BACK)
		NextZItem(false);

	// ���⼭ �˻��غôµ� ����� clear ���Ŀ� ����� ������ �ߴ� ���� �Ǵ� ��
	//if (nChar == VK_RETURN)
	//	SaveThumbnail();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////////////////////////
// mouse event

float GetTimer()//���Ҷ�
{
	static DWORD time_back = timeGetTime();

	DWORD this_time = timeGetTime();

	float s = (float)(this_time - time_back)/1000.f;

	time_back = this_time;

	return s;
}

static bool l_drag = false;
static bool r_drag = false;
static CPoint mouse_delta(0, 0);

void CMainView::OnMouseMove(UINT nFlags, CPoint point)
{
	// �̰� ������ �ִ�.. ���⼭ OnMouseMove �̺�Ʈ���� ī�޶� ������ �ϴϱ� �巡�� ������ �̻��ϴ�.
	// ������ �巡�� �߿� ��� ����ٸ� �� �Ŀ� 1px�������� �ð��� ���� �귶�� ������ �������� ũ�� Ƥ��.
	// �̷��� ���콺 ������ �̺�Ʈ���� ���ٰ� �ƴ϶� �� �����Ӹ��� ����� �Ѵ�.

	/*static CPoint old_pos;

	CPoint pos = point - old_pos;

	float t = GetTimer() * g_camera.m_dist * 0.05f;

	if(l_drag) {// pan

	if(pos.x > 0)
	g_camera.Left((float)pos.x * t);
	else 
	g_camera.Right((float)-pos.x * t);

	if(pos.y > 0)
	g_camera.Up((float)pos.y * t);
	else 
	g_camera.Down((float)-pos.y * t);
	}
	else if(r_drag) {//rot

	if(pos.x > 0)
	g_camera.CenterRotationLeft((float)pos.x * t);
	else 
	g_camera.CenterRotationRight((float)-pos.x * t);

	if(pos.y > 0)
	g_camera.CenterRotationUp((float)pos.y * t);
	else 
	g_camera.CenterRotationDown((float)-pos.y * t);

	}

	old_pos = point;

	*/
	CView::OnMouseMove(nFlags, point);
}

void CMainView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	l_drag = true;

	CView::OnLButtonDown(nFlags, point);
}

void CMainView::OnLButtonUp(UINT nFlags, CPoint point)
{
	l_drag = false;

	RVisualMesh* pVMesh = g_vmesh_mgr.GetFast(0);

	rvector v;
	bool g_bPick = false;

	RPickInfo info;

	if(pVMesh&&pVMesh->m_pMesh) {
		/*
		pVMesh->m_pMesh->SetPickingType(pick_real_mesh);

		if(pVMesh->Pick ( point.x - g_win_pos_x, point.y - g_win_pos_y, &info ) ) {

		//			if(info.pMNode) {
		//				m_SelMeshNodeName = info.pMNode->m_Name;
		//				UpdateData(FALSE);
		//			}

		g_bPick = true;
		}
		else {
		m_SelMeshNodeName = "";
		UpdateData(FALSE);
		g_bPick = false;
		}
		*/
	}

	CView::OnLButtonUp(nFlags, point);

	ReleaseCapture();
}

void CMainView::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();

	r_drag = true;
	CView::OnRButtonDown(nFlags, point);
}

void CMainView::OnRButtonUp(UINT nFlags, CPoint point)
{
	r_drag = false;
	CView::OnRButtonUp(nFlags, point);
	ReleaseCapture();
}

BOOL CMainView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMainView::ApplyMouseMovement()
{
	// �������ӿ� �ѹ����� ȣ��
	static DWORD old_time;
	DWORD time = timeGetTime();// ���ػ� Ÿ�̸Ӹ� ��߰�����...
	DWORD dwTimeElapsed = time - old_time;
	old_time = time;

	static CPoint old_pos;
	CPoint pos;
	GetCursorPos(&pos);
	CPoint posDelta = pos - old_pos;
	old_pos = pos;

	float t = dwTimeElapsed/1000.f * g_camera.m_dist * 0.05f;

	if(l_drag) {// pan

		if(posDelta.x > 0)
			g_camera.Left((float)posDelta.x * t);
		else 
			g_camera.Right((float)-posDelta.x * t);

		if(pos.y > 0)
			g_camera.Up((float)posDelta.y * t);
		else 
			g_camera.Down((float)-posDelta.y * t);
	}
	else if(r_drag) {//rot

		if (!(GetAsyncKeyState(VK_CONTROL) & 0x8000))
		{
			// yaw, pitch
			if(posDelta.x > 0)
				g_camera.CenterRotationLeft((float)posDelta.x * t);
			else 
				g_camera.CenterRotationRight((float)-posDelta.x * t);

			if(posDelta.y > 0)
				g_camera.CenterRotationUp((float)posDelta.y * t);
			else 
				g_camera.CenterRotationDown((float)-posDelta.y * t);
		}
	}
}
