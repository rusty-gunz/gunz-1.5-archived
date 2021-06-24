// BugsAnalyzerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "BugsAnalyzer.h"
#include "BugsAnalyzerDlg.h"
#include ".\bugsanalyzerdlg.h"
#include "CBugsAnalyzer.h"

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


// CBugsAnalyzerDlg ��ȭ ����



CBugsAnalyzerDlg::CBugsAnalyzerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBugsAnalyzerDlg::IDD, pParent)
	, m_strFolderName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBugsAnalyzerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TARGET, m_strFolderName);
	DDX_Control(pDX, IDC_LIST1, m_lbOutput);
	DDX_Control(pDX, IDC_LIST2, m_lbFileList);
	DDX_Control(pDX, IDC_PROGRESS1, m_pcProgress);
}

BEGIN_MESSAGE_MAP(CBugsAnalyzerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPENFOLDER, OnBnClickedBtnOpenfolder)
	ON_BN_CLICKED(IDC_BTN_GO, OnBnClickedBtnGo)
	ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeOutput)
	ON_LBN_DBLCLK(IDC_LIST2, OnLbnDblclkFileList)
END_MESSAGE_MAP()


// CBugsAnalyzerDlg �޽��� ó����

BOOL CBugsAnalyzerDlg::OnInitDialog()
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
	
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CBugsAnalyzerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBugsAnalyzerDlg::OnPaint() 
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
HCURSOR CBugsAnalyzerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "FolderDlg.h"
void CBugsAnalyzerDlg::OnBnClickedBtnOpenfolder()
{
	CFolderDlg dlg("������ �����Ͻʽÿ�.", NULL, NULL, NULL, this);
	if(dlg.DoModal() != IDOK) return;
	m_strFolderName = dlg.GetFolderPath();

	UpdateData(FALSE);
}

void CBugsAnalyzerDlg::OnBnClickedBtnGo()
{
	int nCount = m_lbOutput.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		m_lbOutput.DeleteString(0);
	}


	analyzer.Create(m_strFolderName);
	analyzer.Execute();

	
	BugAnalysisList* pAnalysisList = analyzer.GetAnalysisList();

	for (BugAnalysisList::iterator itor = pAnalysisList->begin();
		itor != pAnalysisList->end(); ++itor)
	{
		BugAnalysisItem* pItem = (*itor);
		char szStr[1024];

		sprintf(szStr, "%4d : %s", pItem->nCount, pItem->szFuncName);
		m_lbOutput.AddString(szStr);
	}
	
}

void CBugsAnalyzerDlg::OnLbnSelchangeOutput()
{
	int nCount = m_lbFileList.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		m_lbFileList.DeleteString(0);
	}
	
	BugInfoList* pBugInfoList = analyzer.GetBugInfoList();
	char szFuncName[256];
	CString strCurFunc;
	int nCurIndex = m_lbOutput.GetCurSel();
	m_lbOutput.GetText(nCurIndex, strCurFunc);
	strcpy(szFuncName, strCurFunc);


	for (BugInfoList::iterator itor = pBugInfoList->begin();
		itor != pBugInfoList->end(); ++itor)
	{
		BugInfo* pBugInfo = (*itor);
		if (!stricmp(&szFuncName[7], pBugInfo->szFuncName))
		{
			m_lbFileList.AddString(pBugInfo->szLogFileName);
		}
	}

}

void CBugsAnalyzerDlg::OnLbnDblclkFileList()
{
	char szFileName[256];
	int nCurIndex = m_lbFileList.GetCurSel();
	m_lbFileList.GetText(nCurIndex, szFileName);

	char szExeName[256];
	sprintf(szExeName, "NotePad %s", szFileName);

	WinExec(szExeName, SW_SHOW);	// Launch again

}
