// GunzItemToolDoc.cpp : CGunzItemToolDoc Ŭ������ ����
//

#include "stdafx.h"
#include "GunzItemTool.h"

#include "GunzItemToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGunzItemToolDoc

IMPLEMENT_DYNCREATE(CGunzItemToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CGunzItemToolDoc, CDocument)
END_MESSAGE_MAP()


// CGunzItemToolDoc ����/�Ҹ�

CGunzItemToolDoc::CGunzItemToolDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CGunzItemToolDoc::~CGunzItemToolDoc()
{
}

BOOL CGunzItemToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ �ٽ� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CGunzItemToolDoc serialization

void CGunzItemToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CGunzItemToolDoc ����

#ifdef _DEBUG
void CGunzItemToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGunzItemToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGunzItemToolDoc ���
