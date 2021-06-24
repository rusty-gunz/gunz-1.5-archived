// AbuseWordDlg.h : ��� ����
//

#pragma once
#include "reportctrl.h"
#include "AbuseWordDB.h"
#include "SearchAbuseWord.h"
#include "InsertAbuseWordDlg.h"


#define CONFIG_FILE ".\\config.ini"


// CAbuseWordDlg ��ȭ ����
class CAbuseWordDlg : public CDialog
{

public :
	void InitReportColumn();
	void MakeAbuseWordReportCtrlList();

	CAbuseWordDB& GetAbuseWordDB() { return m_AbuseWordDB; }
	CReportCtrl&  GetReportCtrl()  { return m_ReportCtrl; }

private :
	bool LoadConfig();
	void InsertReportColumns();

	void DeleteAbuseWord();
	void SaveEnvironInfo();
	
private :
	CAbuseWordDB		m_AbuseWordDB;
	CSearchAbuseWord	m_SearchAbuseWord;
	CInsertAbuseWordDlg	m_InsertAbuseWordDlg;

// ����
public:
	CAbuseWordDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_ABUSEWORD_DIALOG };

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
	CReportCtrl m_ReportCtrl;
	afx_msg void OnUpdateDB();
	afx_msg void OnSaveLocalFile();
	afx_msg void OnDBGetAbuseList();
	afx_msg void OnBnClickedDbUpdate();
	afx_msg void OnBnClickedClose();
	afx_msg void OnExit();
	afx_msg void OnSearchAbuseWord();
	afx_msg void OnInsertAbuseWord();
	afx_msg void OnDeleteUnchecked();
protected:
	virtual void OnCancel();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDeleteAbuseWord();
};
