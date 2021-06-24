// BirdAgentDlg.h : ��� ����
//

#pragma once

#include "TrayIcon.h"

#define	WM_ICON_NOTIFY      WM_USER+10       // ����� ���� �޼���

// CBirdAgentDlg ��ȭ ����
class CBirdAgentDlg : public CDialog
{
// ����
public:
	CBirdAgentDlg(CWnd* pParent = NULL);	// ǥ�� ������
	virtual ~CBirdAgentDlg();

	CTrayIcon m_TrayIcon;

// ��ȭ ���� ������
	enum { IDD = IDD_BIRDAGENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����



// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LONG OnTrayNotification(UINT wParam, LONG lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnMenuQuit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuShow();
	afx_msg void OnMenuHide();
};
