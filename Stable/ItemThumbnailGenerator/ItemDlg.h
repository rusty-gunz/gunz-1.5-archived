#pragma once
#include "afxwin.h"
#include "ZItemList.h"

// CItemDlg ��ȭ �����Դϴ�.

class CItemDlg : public CDialog, public IUpdateListener
{
	DECLARE_DYNAMIC(CItemDlg)

public:
	CItemDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CItemDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TOOL };

	LPDIRECT3DSWAPCHAIN9 m_pSwapChain;
	LPDIRECT3DTEXTURE9 m_pTexThumbnail;

	// � �����ۿ��� ī�޶� pos rot scale ������ �ٸ� ���������� �����ϰ� ���� ���� ���ؼ� �����صδ� ������
	rvector m_vPos[2];
	rvector m_vRot[2];
	rvector m_vScale[2];
	CameraSetting m_cameraSetting;

	void UpdateItemList();

	virtual void UpdateSelection(int id);
	void MakeItemString(ZItem* pItem, CString& out_str);
	void ShowPreview(int id);
	bool EditBoxToVector(CEdit& ed, rvector& out);
	void VectorToEditBox(CEdit& ed, rvector& out);

	void InitSwapChain();
	void RenderPreview();
	void ReleaseSwapChain();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	CListBox m_listbox;
	CStatic m_preview;
public:
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnBnClickedBtnResetcam();
	afx_msg void OnEnKillfocusPosRotScaleEdit();
	afx_msg void OnEnKillfocusPosRotScale2Edit();
	
	CEdit m_edPos;
	CEdit m_edRot;
	CEdit m_edScale;

	CEdit m_edPos2;
	CEdit m_edRot2;
	CEdit m_edScale2;

	afx_msg void OnBnClickedBtnCopy();
	afx_msg void OnBnClickedBtnPaste();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
