// GunzItemToolView.h : iCGunzItemToolView Ŭ������ �������̽�
//


#pragma once


class CGunzItemToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CGunzItemToolView();
	DECLARE_DYNCREATE(CGunzItemToolView)

// Ư��
public:
	CGunzItemToolDoc* GetDocument() const;

// �۾�
public:

// ������
	public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ����
public:
	virtual ~CGunzItemToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GunzItemToolView.cpp�� ����� ����
inline CGunzItemToolDoc* CGunzItemToolView::GetDocument() const
   { return reinterpret_cast<CGunzItemToolDoc*>(m_pDocument); }
#endif

