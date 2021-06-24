// DBQuestItemEditorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "DBQuestItemEditor.h"
#include "DBQuestItemEditorDlg.h"
#include ".\dbquestitemeditordlg.h"


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


// CDBQuestItemEditorDlg ��ȭ ����



CDBQuestItemEditorDlg::CDBQuestItemEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBQuestItemEditorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBQuestItemEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FindCharName, m_szCharName);
	DDX_Control(pDX, IDC_FindCID, m_szCID);
	DDX_Control(pDX, IDC_ChoiceQIID, m_szChoiceQIID);
	DDX_Control(pDX, IDC_SetCount, m_szSetCount);
	DDX_Control(pDX, IDC_QItemList, m_QItemList );
	DDX_Control(pDX, IDC_EditQItem, m_EditBtn);
}

BEGIN_MESSAGE_MAP(CDBQuestItemEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_FindUser, OnBnClickedFinduser)
	ON_BN_CLICKED(IDC_EditQItem, OnBnClickedEditqitem)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
//	ON_WM_LBUTTONDBLCLK()
ON_BN_CLICKED(ID_CLEAR, OnBnClickedClear)
ON_BN_CLICKED(ID_REFRESH, OnBnClickedRefresh)
END_MESSAGE_MAP()


// CDBQuestItemEditorDlg �޽��� ó����

BOOL CDBQuestItemEditorDlg::OnInitDialog()
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

	InitProcess();
	
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CDBQuestItemEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CDBQuestItemEditorDlg::SetChoiceQIID( const string strQIID )
{
	m_szChoiceQIID.SetWindowText( strQIID.c_str() );
}


void CDBQuestItemEditorDlg::SetFocusToChoiceQIID()
{
	m_szChoiceQIID.SetFocus();
}

void CDBQuestItemEditorDlg::SetFocusToCount()
{
	m_szSetCount.SetFocus();
}

void CDBQuestItemEditorDlg::Clear()
{
	m_QItemList.Clear();
	m_szCharName.SetWindowText("");
	m_szCID.SetWindowText("");
	m_szChoiceQIID.SetWindowText("");
	m_szSetCount.SetWindowText("");
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDBQuestItemEditorDlg::OnPaint() 
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
HCURSOR CDBQuestItemEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDBQuestItemEditorDlg::InitProcess()
{
	MMatchStringResManager::MakeInstance();
	MGetStringResManager()->Init("", 1);	// �������ϰ� ���� ������ xml������ �ִ�.

	m_QItemList.InitListColumn();

	if( !m_QItemList.LoadQuestItemXML() )
	{
		AfxMessageBox( "Quest item xml�ε� ����.\n", 0, 0 );
		return;
	}
}

void CDBQuestItemEditorDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if( IDOK == AfxMessageBox("DB Update�� �Ͻðڽ��ϱ�?", MB_OKCANCEL, 0) )
	{
		m_QItemList.UpdateDB();
	}
	
	// OnOK();
}

void CDBQuestItemEditorDlg::OnBnClickedFinduser()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	char szCID[ 64 ]		= {0};
	char szCharName[ 33 ]	= {0};

	m_szCharName.GetWindowText( szCharName, 33 );
	m_szCID.GetWindowText( szCID, 64 );
	
	if( (0 != m_szCharName.GetWindowTextLength()) && (m_szCID.GetWindowTextLength()) )
	{
		// ĳ���� �̸��� CID�� ���� �Էµ� ���.

		int nCID = atoi( szCID );
		const string strCharName = m_QItemList.FindCharNameByCID( nCID );
		if( strCharName.empty() )
			return;

		if( 0 == strnicmp(szCharName, strCharName.c_str(), strCharName.size()) )
		{
			if( !m_QItemList.GetDBQItemInfo(nCID) )
				return;
		}
		else
			AfxMessageBox( "�Է��� �����Ͱ� ��ġ���� �ʽ��ϴ�.", 0, 0 );
	}
	else
	{
		if( 0 != m_szCharName.GetWindowTextLength() )
		{
			// �̸����� �˻�.
			if( !m_QItemList.GetDBQItemInfo(szCharName) )
				return;
		}
		else
		{
			// CID�� �˻�.
			if( 0 == m_szCID.GetWindowTextLength() )
				return;

			int nCID = atoi( szCID );
			if( !m_QItemList.GetDBQItemInfo(nCID) )
				return;
		}
	}

	m_QItemList.MakeQItemInfoColumns();

	m_szChoiceQIID.SetWindowText( "" );
	m_szSetCount.SetWindowText( "" );
}

void CDBQuestItemEditorDlg::OnBnClickedEditqitem()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	char	szQIID[ 64 ];
	char	szCount[ 64 ];
	long	nQIID;
	int		nCount;

	m_szChoiceQIID.GetWindowText( szQIID, 64 );
	if( 0 == strlen(szQIID) )
	{
		return;
	}

	nQIID = atol( szQIID );

	m_szSetCount.GetWindowText( szCount, 64 );
	if( 0 == strlen(szCount) )
	{
		return;
	}

	nCount = atoi( szCount );

	m_QItemList.EditQItem( nQIID, nCount );
	m_QItemList.MakeQItemInfoColumns();
}

void CDBQuestItemEditorDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if( IDOK == AfxMessageBox("DB Update�� �ϱ����� �۾������� ������� �ʽ��ϴ�.\n�����Ͻðڽ��ϱ�?", MB_OKCANCEL, 0) )
        OnCancel();
}
void CDBQuestItemEditorDlg::OnBnClickedClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if( IDOK == AfxMessageBox("Clear�Ͻð����� DB�� ������Ʈ �Ͻðڽ��ϱ�?",MB_OKCANCEL, 0) )
		m_QItemList.UpdateDB();
	
	Clear();
}

void CDBQuestItemEditorDlg::OnBnClickedRefresh()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
