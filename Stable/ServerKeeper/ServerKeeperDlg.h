// ServerKeeperDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "ReportCtrl.h"
#include "MServerKeeper.h"


// CServerKeeperDlg ��ȭ ����
class CServerKeeperDlg : public CDialog
{
// ����
public:
	CServerKeeperDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_SERVERKEEPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON			m_hIcon;
	UINT_PTR		m_nTimerIDCheckProcess;

	MServerKeeper	m_ServerKeeper;

	CImageList		m_ImageList;
	CReportCtrl		m_ReportCtrl;

protected:
	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	void UpdateServerListUI();
	void AddItemUI(MServerItem* pItem);
	void UpdateItemUI(MServerItem* pItem);
	void UpdateItem(MServerItem* pItem);
	void CheckServerProcessStatus();

public:
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg LRESULT OnCheckBox(WPARAM wParam, LPARAM lParam);
};
