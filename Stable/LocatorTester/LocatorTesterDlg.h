// LocatorTesterDlg.h : ��� ����
//

#pragma once


#include "Tester.h"
#include "afxwin.h"


// CLocatorTesterDlg ��ȭ ����
class CLocatorTesterDlg : public CDialog
{
// ����
public:
	CLocatorTesterDlg(CWnd* pParent = NULL);	// ǥ�� ������

private :
	Tester m_Tester;

// ��ȭ ���� ������
	enum { IDD = IDD_LOCATORTESTER_DIALOG };

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
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Elapsed;
	afx_msg void OnBnClickedOk();
	CEdit m_Out;
};
