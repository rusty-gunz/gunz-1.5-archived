#pragma once
#include "afxwin.h"


// CSearchAbuseWord ��ȭ �����Դϴ�.

class CSearchAbuseWord : public CDialog
{
	DECLARE_DYNAMIC(CSearchAbuseWord)

public:
	CSearchAbuseWord(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchAbuseWord();

	void Reset();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	CEdit	m_edtName;
	int		m_nLastSearchItemID;

public:
	afx_msg void OnBnClickedSearch();
	afx_msg void OnEnSetfocusEdit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
