// UpdateBuilderDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CUpdateBuilderDlg ��ȭ ����
class CUpdateBuilderDlg : public CDialog
{
// ����
public:
	CUpdateBuilderDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_UPDATEBUILDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����

// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// ȭ�鿡 �α׸� ����� ����
	CRichEditCtrl m_EditLog;
	void Log(const char *pFormat,...);
	void ClearLog();

	// ��¥ ���ϴ°�
	BOOL Build();

public:
	CString m_strOld;
	CString m_strNew;
	CString m_strOutput;

	afx_msg void OnBnClickedButtonBrowseOld();
	afx_msg void OnBnClickedButtonBrowseNew();
	afx_msg void OnBnClickedButtonBrowseOutput();

	afx_msg void OnBnClickedBuild();
	afx_msg void OnEnChangeEditOld();
	afx_msg void OnEnChangeEditNew();
	afx_msg void OnEnChangeEditOutput();
};
