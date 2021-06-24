// DBQuestItemEditorDlg.h : ��� ����
//

#pragma once



#include "QuestItemList.h"
#include "afxwin.h"



// CDBQuestItemEditorDlg ��ȭ ����
class CDBQuestItemEditorDlg : public CDialog
{
// ����
public:
	CDBQuestItemEditorDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_DBQUESTITEMEDITOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


	void InitProcess();

public :
	void SetChoiceQIID( const string strQIID );
	void SetFocusToChoiceQIID();
	void SetFocusToCount();
	void Clear();

private :
	CQuestItemList m_QItemList;


// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnBnClickedOk();
	CEdit m_szCharName;
	CEdit m_szCID;
	CEdit m_szChoiceQIID;
	CEdit m_szSetCount;
	afx_msg void OnBnClickedFinduser();
	afx_msg void OnBnClickedEditqitem();
	afx_msg void OnBnClickedCancel();
	CButton m_EditBtn;
public:
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedRefresh();
};
