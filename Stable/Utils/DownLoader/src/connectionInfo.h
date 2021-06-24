#pragma once

#include "listctrl.h"
#include "afxcmn.h"

/**		����� Ŭ���̾�Ʈ���� ip/����/�ٿ�ӵ�/���ӵ�/������/������ �� ǥ���Ѵ�.
*
*		@author soyokaze
*		@date   2005-11-02
*/

class ConnectionInfo : public CDialog
{
	DECLARE_DYNAMIC(ConnectionInfo)

public:
	ConnectionInfo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ConnectionInfo();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CONNECTION_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	ListCtrl m_cClientList;

protected:
	virtual void OnCancel();

public:
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
