// GunzItemTool.h : GunzItemTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"       // �� ��ȣ


// CGunzItemToolApp:
// �� Ŭ������ ������ ���ؼ��� GunzItemTool.cpp�� �����Ͻʽÿ�.
//

class CGunzItemToolApp : public CWinApp
{
public:
	CGunzItemToolApp();


// ������
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGunzItemToolApp theApp;
