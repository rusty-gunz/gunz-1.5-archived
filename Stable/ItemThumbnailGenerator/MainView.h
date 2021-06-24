// MainView.h : iCMainView Ŭ������ �������̽�
//


#pragma once
#include "ZItemList.h"

namespace RealSpace2 {
	class RMesh;
}


class CMainView : public CView, public IUpdateListener
{
protected: // serialization������ ��������ϴ�.
	CMainView();
	DECLARE_DYNCREATE(CMainView)

public:
	CMainDoc* GetDocument() const;

	bool Init();
	void Finish();

	void Update();
	void Render();

	void OnReturnKey();

	void NextZItem(bool bForward);

	RMesh* FindWeaponMesh(ZItem* pItem);
	RMesh* FindCharMesh(ZItem* pItem);
	bool MakeWeaponVisualMesh(RMesh* pMesh);
	bool MakeCharVisualMesh(RMesh* pBaseMesh, const char* szSlot, const char* szMeshName, const char* szAvatarHeadMeshName, const char* szAvatarChestMeshName);

	void DrawTargetRect();
	void ApplyMouseMovement();
	void SaveThumbnail(const char* szPath);

	virtual void UpdateSelection(int id);


// ������
	public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����
public:
	virtual ~CMainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	
};

#ifndef _DEBUG  // MainView.cpp�� ����� ����
inline CMainDoc* CMainView::GetDocument() const
   { return reinterpret_cast<CMainDoc*>(m_pDocument); }
#endif



extern CMainView* g_pView;