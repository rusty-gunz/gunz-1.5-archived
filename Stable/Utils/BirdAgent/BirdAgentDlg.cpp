// BirdAgentDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "BirdAgent.h"
#include "BirdAgentDlg.h"
#include "MALConverter.h"
#include ".\birdagentdlg.h"
#include "MDebug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MConverter	g_DBConverter;

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


// CBirdAgentDlg ��ȭ ����



CBirdAgentDlg::CBirdAgentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBirdAgentDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CBirdAgentDlg::~CBirdAgentDlg()
{
	m_TrayIcon.RemoveIcon();
}

void CBirdAgentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBirdAgentDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_COMMAND(ID__32774, OnMenuQuit)
	ON_WM_TIMER()
	ON_COMMAND(ID__, OnMenuShow)
	ON_COMMAND(ID__32772, OnMenuHide)
END_MESSAGE_MAP()


// CBirdAgentDlg �޽��� ó����

BOOL CBirdAgentDlg::OnInitDialog()
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
	

	
	
	// Ʈ���� ������ ���
    if (!m_TrayIcon.Create(this, WM_ICON_NOTIFY, _T("Ʈ���� ������ �׽�Ʈ"), NULL, IDR_TRAY_MENU))
         return -1;

	// ������ ����
    // ������ ���̵� �ڽ��� �������� ��������...
    m_TrayIcon.SetIcon(IDR_MAINFRAME);

	SetTimer(1, 10000, NULL);


	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CBirdAgentDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBirdAgentDlg::OnPaint() 
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

LONG CBirdAgentDlg::OnTrayNotification(UINT wParam, LONG lParam)
{
	if (LOWORD(lParam) == WM_LBUTTONDBLCLK)
	{
		if (IsWindowVisible()) ShowWindow(SW_HIDE);
		else ShowWindow(SW_SHOW);
		return 1;
	}

	return m_TrayIcon.OnTrayNotification(wParam, lParam);
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CBirdAgentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBirdAgentDlg::OnBnClickedButton3()
{
	g_DBConverter.ConvertActionLeague();	
}


void CBirdAgentDlg::OnMenuQuit()
{
	SendMessage(WM_CLOSE, 0, 0);
	
}

void CBirdAgentDlg::OnTimer(UINT nIDEvent)
{
/*
	CTime theTime = CTime::GetCurrentTime();

	static bool st_bDiffDay = false;
	//static int st_nLastDay = theTime.GetDay();
	static int st_nLastDay = 28;
	if (theTime.GetDay() != st_nLastDay) st_bDiffDay = true;
	st_nLastDay = theTime.GetDay();

	if ((st_bDiffDay) && (theTime.GetHour() == 5))
	{
		st_bDiffDay = false;


		g_DBConverter.ConvertActionLeague();
	}


	//blog("Day: %d, Hour: %d, Min: %d, Sec:%d\n", theTime.GetDay(), theTime.GetHour(), theTime.GetMinute(), theTime.GetSecond());

	CDialog::OnTimer(nIDEvent);
*/
}

void CBirdAgentDlg::OnMenuShow()
{
	ShowWindow(SW_SHOW);
}
void CBirdAgentDlg::OnMenuHide()
{
	ShowWindow(SW_HIDE);
}
