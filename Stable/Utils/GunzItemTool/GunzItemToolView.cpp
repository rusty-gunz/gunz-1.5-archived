// GunzItemToolView.cpp : CGunzItemToolView Ŭ������ ����
//

#include "stdafx.h"
#include "GunzItemTool.h"

#include "GunzItemToolDoc.h"
#include "GunzItemToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGunzItemToolView

IMPLEMENT_DYNCREATE(CGunzItemToolView, CView)

BEGIN_MESSAGE_MAP(CGunzItemToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGunzItemToolView ����/�Ҹ�

CGunzItemToolView::CGunzItemToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CGunzItemToolView::~CGunzItemToolView()
{
}

BOOL CGunzItemToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	// Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CGunzItemToolView �׸���

void CGunzItemToolView::OnDraw(CDC* /*pDC*/)
{
	CGunzItemToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CGunzItemToolView �μ�

BOOL CGunzItemToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CGunzItemToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CGunzItemToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CGunzItemToolView ����

#ifdef _DEBUG
void CGunzItemToolView::AssertValid() const
{
	CView::AssertValid();
}

void CGunzItemToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGunzItemToolDoc* CGunzItemToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGunzItemToolDoc)));
	return (CGunzItemToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CGunzItemToolView �޽��� ó����
