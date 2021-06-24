// AbuseWordDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "AbuseWord.h"
#include "AbuseWordDlg.h"
#include ".\abuseworddlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAbuseWordDlg ��ȭ ����



CAbuseWordDlg::CAbuseWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAbuseWordDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAbuseWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ReportCtrl);
}


void CAbuseWordDlg::MakeAbuseWordReportCtrlList()
{
	m_ReportCtrl.DeleteAllItems();

	// Unchecked�� ���� ���� ������ ����Ʈ�� ������.
	const int nAbuseWordNum = m_AbuseWordDB.GetAbuseListSize();
	for( int i = 0; i < nAbuseWordNum; ++i )
	{
		const ABUSE_WORD_INFO* pAbuseWord = m_AbuseWordDB.GetAbuseWordByPos( i );
		if( 0 != pAbuseWord )
		{
			m_ReportCtrl.InsertItem( i, pAbuseWord->m_strKeyAbuseWord.c_str() );

			m_ReportCtrl.SetItemText( i, 1, pAbuseWord->m_strReplaceWord.c_str() );

			if( AW_USED == pAbuseWord->m_nCheckState )
				m_ReportCtrl.SetCheck( i, true );
		}
	}
}


bool CAbuseWordDlg::LoadConfig()
{
	char szVal[ 512 ];

	GetPrivateProfileString( "DB", "HOST", "", szVal, 511, CONFIG_FILE );
	if( 0 == strlen(szVal) ) return false;
	m_AbuseWordDB.SetHost( szVal );

	GetPrivateProfileString( "DB", "USER", "", szVal, 511, CONFIG_FILE );
	if( 0 == strlen(szVal) ) return false;
	m_AbuseWordDB.SetUser( szVal );

	GetPrivateProfileString( "DB", "PASSWORD", "", szVal, 511, CONFIG_FILE );
	if( 0 == strlen(szVal) ) return false;
	m_AbuseWordDB.SetPassword( szVal );

	GetPrivateProfileString( "DB", "DB", "", szVal, 511, CONFIG_FILE );
	if( 0 == strlen(szVal) ) return false;
	m_AbuseWordDB.SetDB( szVal);

	GetPrivateProfileString( "LOCAL_FILE", "LAST_SAVE_DIR", "", szVal, 511, CONFIG_FILE );
	if( 0 == strlen(szVal) ) return false;
	m_AbuseWordDB.SetLastSaveDir( szVal );

	return true;
}


void CAbuseWordDlg::SaveEnvironInfo()
{
}


void CAbuseWordDlg::DeleteAbuseWord()
{
	if( IDYES == AfxMessageBox("���� ����ڽ��ϱ�?", MB_YESNO, 0) )
	{
		if( m_AbuseWordDB.ConnectDB() )
		{
			m_AbuseWordDB.DeleteAbuseWord( m_ReportCtrl.GetSelectedItemText() );
			m_AbuseWordDB.DisconnectDB();

			OnDBGetAbuseList();		
		}
		else
			AfxMessageBox( "�ܾ� ���Ž���." );
	}
}


BEGIN_MESSAGE_MAP(CAbuseWordDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_DB_UPDATE_DB, OnUpdateDB)
	ON_COMMAND(ID_SAVE_LOCAL_FILE, OnSaveLocalFile)
	ON_COMMAND(ID_DB_GET_ABUSE_LIST, OnDBGetAbuseList)
	ON_BN_CLICKED(ID_DB_UPDATE, OnBnClickedDbUpdate)
	ON_BN_CLICKED(IDCLOSE, OnBnClickedClose)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_SEARCH, OnSearchAbuseWord)
	ON_COMMAND(ID_INSERT, OnInsertAbuseWord)
	ON_COMMAND(ID_DELETE_UNCHECKED, OnDeleteUnchecked)
	ON_COMMAND(ID_DELETE_ABUSE_WORD, OnDeleteAbuseWord)
END_MESSAGE_MAP()


// CAbuseWordDlg �޽��� ó����

BOOL CAbuseWordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	InitReportColumn();

	if( !m_SearchAbuseWord.Create(IDD_SEARCH, this) )
	{
		AfxMessageBox( "Ž�������� ���� ����." );
		return FALSE;
	}

	if( !m_InsertAbuseWordDlg.Create(IDD_INSERT_ABUSE_WORD, this) )
	{
		AfxMessageBox( "�ܾ� �߰������� ���� ����." );
		return FALSE;
	}

	if( !LoadConfig() )
	{
		AfxMessageBox( "Config.ini���� �ε� ����." );
		return FALSE;
	}
	
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}


void CAbuseWordDlg::InitReportColumn()
{
	m_ReportCtrl.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	InsertReportColumns();
}


void CAbuseWordDlg::InsertReportColumns()
{
	char* pszColumns[] = {"AbuseWord", "ReplaceWord" };

	for( int i = 0; i < 2; ++i )
		m_ReportCtrl.InsertColumn( i, pszColumns[i], LVCFMT_LEFT, 150 );
}


void CAbuseWordDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAbuseWordDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CAbuseWordDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAbuseWordDlg::OnUpdateDB()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if( m_AbuseWordDB.ConnectDB() )
	{
		if( m_AbuseWordDB.UpdateDB() )
		{
			AfxMessageBox( "DB������Ʈ �Ϸ�.\n����Ʈ�� ������Ʈ�� DB�� �������� �����մϴ�.", MB_OK, 0 );
			OnDBGetAbuseList();
		}
		else
			AfxMessageBox( "DB������Ʈ ����." );

		m_AbuseWordDB.DisconnectDB();
	}
}

void CAbuseWordDlg::OnSaveLocalFile()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	OPENFILENAME ofn;
	char szFileName[ MAX_PATH ] = {0,};
	char szFileTitle[ MAX_PATH ] = {0,};

	memset( &ofn, 0, sizeof(OPENFILENAME) );
	
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter="�ܾ��Ʈ(*.txt)\0*.txt";
	ofn.lpstrFile = szFileName;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = m_AbuseWordDB.GetLastSaveDir().c_str();

	GetSaveFileName( &ofn );

	if( m_AbuseWordDB.SaveLocalFile(string(szFileName)) )
	{
		AfxMessageBox( "���� �Ϸ�." );

		m_AbuseWordDB.SetLastSaveDir( szFileName );
	}
	else
		AfxMessageBox( "���� ����" );
}

void CAbuseWordDlg::OnDBGetAbuseList()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if( m_AbuseWordDB.ConnectDB() )
	{
		m_AbuseWordDB.ClearList();

		m_AbuseWordDB.GetDBAbuseList();
		m_AbuseWordDB.DisconnectDB();

		MakeAbuseWordReportCtrlList();		
	}
}


void CAbuseWordDlg::OnBnClickedDbUpdate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	OnUpdateDB();
}


void CAbuseWordDlg::OnBnClickedClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if( IDYES == AfxMessageBox("������ ������Ʈ ���� �۾��� DB�� ������� �ʽ��ϴ�.\n�����Ͻðڽ��ϱ�?", MB_YESNO, 0) )
	{
		OnCancel();
	}
}


void CAbuseWordDlg::OnExit()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	OnBnClickedClose();
}


void CAbuseWordDlg::OnSearchAbuseWord()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	m_SearchAbuseWord.Reset();
	m_SearchAbuseWord.ShowWindow( SW_SHOW );
}

void CAbuseWordDlg::OnInsertAbuseWord()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	m_InsertAbuseWordDlg.Reset();
	m_InsertAbuseWordDlg.ShowWindow( SW_SHOW );
}


void CAbuseWordDlg::OnDeleteUnchecked()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	if( m_AbuseWordDB.DeleteUnchecked() )
	{
		AfxMessageBox( "ǥ�õ��� ���� �ܾ����� �Ϸ�.\n����Ʈ�� ������Ʈ�� DB�� �������� �����մϴ�." );
		OnDBGetAbuseList();
	}
	else
		AfxMessageBox( "ǥ�õ��� ���� �ܾ����� ����." );
}

void CAbuseWordDlg::OnCancel()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	SaveEnvironInfo();

	CDialog::OnCancel();
}
LRESULT CAbuseWordDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CAbuseWordDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	switch( pMsg->message)    {
	case WM_KEYDOWN:
		{
			const int nKey = (int)pMsg->wParam;
			switch( nKey )
			{
			case 46 : // Delete key.
				{
					DeleteAbuseWord();
				}
				break;
			};
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CAbuseWordDlg::OnDeleteAbuseWord()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	DeleteAbuseWord();
}
