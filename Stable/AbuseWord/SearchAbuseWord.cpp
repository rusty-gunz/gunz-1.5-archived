// SearchAbuseWord.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AbuseWord.h"
#include "SearchAbuseWord.h"
#include ".\searchabuseword.h"
#include "AbuseWordDlg.h"
#include "AbuseWordDB.h"


// CSearchAbuseWord ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSearchAbuseWord, CDialog)
CSearchAbuseWord::CSearchAbuseWord(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchAbuseWord::IDD, pParent), m_nLastSearchItemID( -1 )
{
}

CSearchAbuseWord::~CSearchAbuseWord()
{
}


void CSearchAbuseWord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtName);
}


void CSearchAbuseWord::Reset()
{
	m_edtName.SetWindowText( "" );
	m_edtName.SetFocus();
}


BEGIN_MESSAGE_MAP(CSearchAbuseWord, CDialog)
	ON_BN_CLICKED(ID_SEARCH, OnBnClickedSearch)
	ON_EN_SETFOCUS(IDC_EDIT1, OnEnSetfocusEdit)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CSearchAbuseWord �޽��� ó�����Դϴ�.

void CSearchAbuseWord::OnBnClickedSearch()
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

			const ABUSE_WORD_INFO* pAbuseWordInfo = AbuseWordDB.GetAbuseWordByKeyAbuseWord( string(strAbuseWordName.GetBuffer()) );
			if( 0 != pAbuseWordInfo )
			{
				CReportCtrl& ReportCtrl = pAbuseWordDlg->GetReportCtrl();
				const int nItemID = ReportCtrl.FindPosition( pAbuseWordInfo->m_strKeyAbuseWord );
				if( -1 != nItemID )
				{
					int nTopIndex;
					int nPgCnt = ReportCtrl.GetCountPerPage() / 2;
					while( true )
					{
						nTopIndex = ReportCtrl.GetTopIndex();

						if( ((nItemID > nTopIndex) && ((nItemID - nPgCnt) < nTopIndex)) ||
							(nItemID == nTopIndex) )
						{
							ReportCtrl.SetItemState( m_nLastSearchItemID, ~LVIS_SELECTED, LVIS_SELECTED );
							ReportCtrl.SetItemState( nItemID, LVIS_SELECTED, LVIS_SELECTED );

							m_nLastSearchItemID = nItemID;

							break;
						}
						else if( nItemID > nTopIndex )
						{
							ReportCtrl.ScrollDown();
						}
						else if( nItemID < nTopIndex )
						{
							ReportCtrl.ScrollUp();
						}
						else
						{
							ASSERT( 0 && "�˻� ������ ������." );
						}
					}
				}
				else
					AfxMessageBox( "Ž�� ����.", MB_OK, 0 );
			}
			else
				AfxMessageBox( "�ش� �ܾ �������� �ʽ��ϴ�. AbuseWordList�� ReportCtrl�� ��ġ���� ����.", MB_OK, 0 );
		}
	}
}

void CSearchAbuseWord::OnEnSetfocusEdit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_edtName.SetWindowText( "" );
}

int CSearchAbuseWord::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}
