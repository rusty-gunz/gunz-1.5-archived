#pragma once
#include "afxwin.h"


// CInsertAbuseWordDlg ��ȭ �����Դϴ�.

class CInsertAbuseWordDlg : public CDialog
{
	DECLARE_DYNAMIC(CInsertAbuseWordDlg)

public:
	CInsertAbuseWordDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInsertAbuseWordDlg();

	void Reset();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INSERT_ABUSE_WORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_edtName;
public:
	afx_msg void OnBnClickedInsert();
	afx_msg void OnEnSetfocusEdit();
};
