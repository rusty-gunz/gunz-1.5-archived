// AbuseWord.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CAbuseWordApp:
// �� Ŭ������ ������ ���ؼ��� AbuseWord.cpp�� �����Ͻʽÿ�.
//

class CAbuseWordApp : public CWinApp
{
public:
	CAbuseWordApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
	afx_msg void OnExit();
};

extern CAbuseWordApp theApp;
