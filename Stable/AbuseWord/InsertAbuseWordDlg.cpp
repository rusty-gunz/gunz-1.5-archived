// InsertAbuseWordDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AbuseWord.h"
#include "InsertAbuseWordDlg.h"
#include "AbuseWordDlg.h"
#include "AbuseWordDB.h"
#include ".\insertabuseworddlg.h"


// CInsertAbuseWordDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CInsertAbuseWordDlg, CDialog)
CInsertAbuseWordDlg::CInsertAbuseWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertAbuseWordDlg::IDD, pParent)
{
	// m_edtName.SetWindowText( "" );
}

CInsertAbuseWordDlg::~CInsertAbuseWordDlg()
{
}

void CInsertAbuseWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtName);
}


void CInsertAbuseWordDlg::Reset()
{
	m_edtName.SetWindowText( "" );
	m_edtName.SetFocus();
}


BEGIN_MESSAGE_MAP(CInsertAbuseWordDlg, CDialog)
	ON_BN_CLICKED(ID_INSERT, OnBnClickedInsert)
	ON_EN_SETFOCUS(IDC_EDIT1, OnEnSetfocusEdit)
END_MESSAGE_MAP()


// CInsertAbuseWordDlg �޽��� ó�����Դϴ�.

void CInsertAbuseWordDlg::OnBnClickedInsert()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CWnd* pWnd = theApp.GetMainWnd();
	if( 0 != pWnd )
	{
		CString strAbuseWordName;
		m_edtName.GetWindowText( strAbuseWordName );
		if( 0 != strAbuseWordName.GetLength() )
		{
			CAbuseWordDlg* pAbuseWordDlg = reinterpret_cast< CAbuseWordDlg* >( pWnd );
			CAbuseWordDB& AbuseWordDB	 = pAbuseWordDlg->GetAbuseWordDB();

			if( 0 == AbuseWordDB.GetAbuseListSize() )
			{
				// DB���� ����Ʈ�� ������ ���� ���������� �����ϰ�, �߰� �ܾ �ߺ��ɼ� ������ �˸�.
				if( IDYES != AfxMessageBox("����Ʈ�� ����ֽ��ϴ�.\n���� DB���� ����Ʈ ������ �������� �ʾ��� ��쿡�� ������ ���ϼ��� ������ �� �����ϴ�.\n��� �����Ͻðڽ��ϱ�?",
					MB_YESNO, 0) )
				{
					return;
				}
			}

			if( AbuseWordDB.ConnectDB() )
			{
				if( AbuseWordDB.InsertAbuseWordDirectDB(string(strAbuseWordName.GetBuffer()), string("NULL"), AW_NEW) )
				{
					AfxMessageBox( "�߰� ����. \n����Ʈ�� �ٽ� �����մϴ�." );
					pAbuseWordDlg->MakeAbuseWordReportCtrlList();
				}
				else
					AfxMessageBox( "�߰� ����. \n�ߺ��Ǵ� �ܾ ����." );
			}
			AbuseWordDB.DisconnectDB();
		}
	}
}

void CInsertAbuseWordDlg::OnEnSetfocusEdit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_edtName.SetWindowText( "" );
}
