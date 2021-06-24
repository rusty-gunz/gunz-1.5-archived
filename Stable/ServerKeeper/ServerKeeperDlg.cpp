// ServerKeeperDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ServerKeeper.h"
#include "ServerKeeperDlg.h"
#include "MProcessController.h"
#include ".\serverkeeperdlg.h"
#include "MSharedCommandTable.h"
#include "Updater.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif


#define FILENAME_SERVERKEEPER	"ServerKeeperConfig.xml"

#define COLOR_ALIVE	RGB(150,150,255)
#define COLOR_DEAD	RGB(255,150,150)

#define TIMERID_CHECK_PROCESS		101
#define TIMER_ELAPSE_CHECK_PROCESS	1000


// CServerKeeperDlg ��ȭ ����
CServerKeeperDlg::CServerKeeperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerKeeperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nTimerIDCheckProcess = 0;
}

void CServerKeeperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SERVER, m_ReportCtrl);
}

BEGIN_MESSAGE_MAP(CServerKeeperDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_START, OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBnClickedBtnStop)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_MESSAGE(WM_ON_CHKBOX, OnCheckBox)
END_MESSAGE_MAP()


// CServerKeeperDlg �޽��� ó����

BOOL CServerKeeperDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	/*
	if( !m_ServerKeeper.Create(7500) )
	{
		mlog( "Fail to m_ServerKeeper.Create\n" );
		return FALSE;
	}
	*/
	
	if( !m_ServerKeeper.LoadFromXml(FILENAME_SERVERKEEPER) )
	{
		mlog( "Fail m_ServerKeeper.LoadFromXml\n" );
		return FALSE;
	}

	if( !m_ServerKeeper.Create() )
	{
		return FALSE;
	}

	m_ImageList.Create(16, 16, ILC_COLORDDB, 0, 4);
	CBitmap bmAlive; bmAlive.LoadBitmap(IDB_ALIVE);
	m_ImageList.Add(&bmAlive, (COLORREF)-1);
	CBitmap bmDead; bmDead.LoadBitmap(IDB_DEAD);		
	m_ImageList.Add(&bmDead, (COLORREF)-1);

	m_ServerKeeper.InitConfigState();
	m_ServerKeeper.InitServerState();

//	m_ReportCtrl.SetColumnHeader(_T("Check,50; Alive,50; Server,50,1; Path, 200 "));
//	m_ReportCtrl.SetImageList(&m_ImageList);
	m_ReportCtrl.SetGridLines(TRUE); // SHow grid lines
	m_ReportCtrl.SetCheckboxeStyle(RC_CHKBOX_NORMAL); // Enable checkboxes

	m_ReportCtrl.InsertColumn(0, _T("Vital"), LVCFMT_LEFT);
	m_ReportCtrl.InsertColumn(1, _T("Status"), LVCFMT_LEFT);
	m_ReportCtrl.InsertColumn(2, _T("ServerType"), LVCFMT_LEFT);
	m_ReportCtrl.InsertColumn(3, _T("Name"), LVCFMT_LEFT);
	m_ReportCtrl.InsertColumn(4, _T("Path"), LVCFMT_LEFT);

	m_ReportCtrl.SetColumnWidth(0, 60);
	m_ReportCtrl.SetColumnWidth(1, 60);
	m_ReportCtrl.SetColumnWidth(2, 80);
	m_ReportCtrl.SetColumnWidth(3, 100);
	m_ReportCtrl.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);

	UpdateServerListUI();
	CheckServerProcessStatus();
/*
    m_ReportCtrl.InsertItem(0, "");
	m_ReportCtrl.SetItemText(0, 0, "Alive");
	m_ReportCtrl.SetItemBkColor(0,0,RGB(180,180,255));
	m_ReportCtrl.SetItemText(0, 1, "Stop");
	m_ReportCtrl.SetItemText(0, 2, "MatchServer");
	m_ReportCtrl.SetItemText(0, 3, "C:\\GunzServer\\MatchServer");
*/
	m_nTimerIDCheckProcess = SetTimer(TIMERID_CHECK_PROCESS, TIMER_ELAPSE_CHECK_PROCESS, NULL);
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}


void CServerKeeperDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	if (m_nTimerIDCheckProcess)
		KillTimer(m_nTimerIDCheckProcess);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CServerKeeperDlg::OnPaint() 
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

void CServerKeeperDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CheckServerProcessStatus();

	m_ServerKeeper.Run();
	m_ServerKeeper.SendPingToPatchInterface();
		
	CDialog::OnTimer(nIDEvent);
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CServerKeeperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerKeeperDlg::UpdateServerListUI()
{
	MServerItemList* pList = m_ServerKeeper.GetServerItemList();
	for (MServerItemList::iterator i = pList->begin(); i!=pList->end(); i++) {
		MServerItem* pItem = *i;
		AddItemUI(pItem);
	}
}

void CServerKeeperDlg::UpdateItemUI(MServerItem* pItem)
{
	int nRow = m_ReportCtrl.GetNextItem(-1, LVNI_ALL);
	while(nRow != -1) {
		int nSlotID = m_ReportCtrl.GetItemData(nRow);
		if (pItem->GetSlotID() == nSlotID) {
			m_ReportCtrl.SetItemText(nRow, 0, "N/A");
			m_ReportCtrl.SetItemText(nRow, 1, pItem->GetStatusToString().c_str());
			m_ReportCtrl.SetItemText(nRow, 2, pItem->GetServerType());
			m_ReportCtrl.SetItemText(nRow, 3, pItem->GetServerName());
			m_ReportCtrl.SetItemText(nRow, 4, pItem->GetServerPath());

			if (pItem->GetVitalCheck() == true)
				m_ReportCtrl.SetCheck(nRow, TRUE);
			else
				m_ReportCtrl.SetCheck(nRow, FALSE);

			if (pItem->GetStatus() == MServerItem::SERVERSTATUS_START)
				m_ReportCtrl.SetItemBkColor(nRow, 1, COLOR_ALIVE);
			else
				m_ReportCtrl.SetItemBkColor(nRow, 1, COLOR_DEAD);			
			break;
		}
		nRow = m_ReportCtrl.GetNextItem(nRow, LVNI_ALL);
	}
}

void CServerKeeperDlg::UpdateItem(MServerItem* pItem) 
{
	HANDLE hProcess = MProcessController::OpenProcessHandleByFilePath(pItem->GetServerPath());
	if (hProcess) {	// Started
		pItem->SetStatus(MServerItem::SERVERSTATUS_START);
		CloseHandle(hProcess);
		UpdateItemUI(pItem);
	} else {		// Stopped
		pItem->SetStatus(MServerItem::SERVERSTATUS_STOP);
		UpdateItemUI(pItem);

		//
		//if( 0 == pItem->GetSlotID() ) // server
		//{
		//	if( m_ServerKeeper.FindAgent() )
		//		m_ServerKeeper.StopAgent();
		//}

		if (pItem->GetVitalCheck() == true) {
			if (timeGetTime() - pItem->GetTimeLastStatusChanged() > TIME_RELAUNCH)
			{
				char temp_log[256] = {0, };
				wsprintf(temp_log, "2. UpdateItem() [Time Gap = %d]", timeGetTime() - pItem->GetTimeLastStatusChanged());
				mlog(temp_log);

				memset(temp_log, 0, 256);
				SYSTEMTIME st;
				memset(&st, 0, sizeof(SYSTEMTIME));
				GetLocalTime(&st);
				wsprintf(temp_log, " - Start Server Process [%4d/%2d/%2d %2d:%2d:%2d]\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				mlog(temp_log);
				MProcessController::StartProcess( pItem->GetServerPath() );
				
				//if( 1 == pItem->GetSlotID() ) // agent
				//{
				//	pItem->
				//	if( m_ServerKeeper.IsOkServerStart() )
				//	{
				//		// ���⼭�� Agent�� ������.
				//		m_ServerKeeper.StartAgent();
				//		UpdateItemUI(pItem);
				//	}
				//}
				//else
				//{
				//	// m_ServerKeeper.StartServer(pItem);
				//	m_ServerKeeper.StartServer();
				//	UpdateItemUI(pItem);
				//}
			}
		}
	}
}

void CServerKeeperDlg::CheckServerProcessStatus()
{
	MServerItemList* pList = m_ServerKeeper.GetServerItemList();
	for (MServerItemList::iterator i = pList->begin(); i!=pList->end(); i++) {
		MServerItem* pItem = *i;
		UpdateItem(pItem);
	}	
}

void CServerKeeperDlg::AddItemUI(MServerItem* pItem)
{
	int nRow = pItem->GetSlotID();
    nRow = m_ReportCtrl.InsertItem(nRow, "");
	m_ReportCtrl.SetItemText(nRow, 0, "N/A");
	m_ReportCtrl.SetItemText(nRow, 1, "Stop");
	m_ReportCtrl.SetItemText(nRow, 2, pItem->GetServerType());
	m_ReportCtrl.SetItemText(nRow, 3, pItem->GetServerName());
	m_ReportCtrl.SetItemText(nRow, 4, pItem->GetServerPath());
	m_ReportCtrl.SetItemData(nRow, pItem->GetSlotID());
}

void CServerKeeperDlg::OnBnClickedBtnStart()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_ReportCtrl.GetFirstSelectedItemPosition();
	if (pos) {
		int nItem = m_ReportCtrl.GetNextSelectedItem(pos);
		int nSlotID = m_ReportCtrl.GetItemData(nItem);
		MServerItem* pServerItem = m_ServerKeeper.FindServerItemBySlotID(nSlotID);
		if (pServerItem)
		{
			if (pServerItem->GetStatus() == MServerItem::SERVERSTATUS_START)
			{
				AfxMessageBox("Already Started", MB_OK);
				return;
			}
			mlog("1. OnBnClickedBtnStart()");
			m_ServerKeeper.StartServer(pServerItem);
			UpdateItem(pServerItem);
		}
	}	
}

void CServerKeeperDlg::OnBnClickedBtnStop()
{
	POSITION pos = m_ReportCtrl.GetFirstSelectedItemPosition();
	if (pos) {
		int nItem = m_ReportCtrl.GetNextSelectedItem(pos);
		int nSlotID = m_ReportCtrl.GetItemData(nItem);
		MServerItem* pServerItem = m_ServerKeeper.FindServerItemBySlotID(nSlotID);
		if (pServerItem) {
			m_ServerKeeper.StopServer(pServerItem);
			UpdateItem(pServerItem);
		}
	}
}

LRESULT CServerKeeperDlg::OnCheckBox(WPARAM wParam, LPARAM lParam)
{
	// Called when the user clicked on a checkbox in the list control
	int nItem = (int)wParam; // Item index
	UINT nMouseEvent  = (UINT)lParam; // Mouse event, usually being WM_LBUTTONDOWN or WM_RBUTTONDOWN

	// TODO: Add your message handler code here
	POSITION pos = m_ReportCtrl.GetFirstSelectedItemPosition();
	if (pos) {
		int nSlotID = m_ReportCtrl.GetItemData(nItem);
		MServerItem* pServerItem = m_ServerKeeper.FindServerItemBySlotID(nSlotID);
		if (pServerItem) {
			if (m_ReportCtrl.GetCheck(nItem) == TRUE)
			{
				pServerItem->SetVitalCheck(true);
				
				if( 0 == nItem )
					m_ServerKeeper.OnRequestSetOneConfig( COLUMN_SERVER_START, CONFIG_AUTO_START_SERVER );
				else if( 1 == nItem )
					m_ServerKeeper.OnRequestSetOneConfig( COLUMN_AGENT_START, CONFIG_AUTO_START_AGENT );
			}
			else
			{
				pServerItem->SetVitalCheck(false);

				if( 0 == nItem )
					m_ServerKeeper.OnRequestSetOneConfig( COLUMN_SERVER_START, CONFIG_MANUAL_START_SERVER );
				else if( 1 == nItem )
					m_ServerKeeper.OnRequestSetOneConfig( COLUMN_AGENT_START, CONFIG_MANUAL_START_AGENT );
			}
			UpdateItem(pServerItem);
		}
	}

	
	return (LRESULT)0;
}
