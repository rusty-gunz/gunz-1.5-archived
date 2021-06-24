// BugsAnalyzerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "CBugsAnalyzer.h"
#include "afxcmn.h"

// CBugsAnalyzerDlg ��ȭ ����
class CBugsAnalyzerDlg : public CDialog
{
// ����
public:
	CBugsAnalyzerDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_BUGSANALYZER_DIALOG };

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
	afx_msg void OnBnClickedBtnOpenfolder();
protected:
public:
	CString m_strFolderName;
	afx_msg void OnBnClickedBtnGo();
protected:
	CListBox m_lbOutput;
	CListBox m_lbFileList;
	CBugsAnalyzer	analyzer;
public:
	afx_msg void OnLbnSelchangeOutput();
	afx_msg void OnLbnDblclkFileList();
	CProgressCtrl m_pcProgress;
};
