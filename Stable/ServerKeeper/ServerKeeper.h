// ServerKeeper.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CServerKeeperApp:
// �� Ŭ������ ������ ���ؼ��� ServerKeeper.cpp�� �����Ͻʽÿ�.
//

class CServerKeeperApp : public CWinApp
{
public:
	CServerKeeperApp();

// ������
	public:
	virtual BOOL InitInstance();

	bool UpdaterTest();

	int Run();

// ����

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CServerKeeperApp theApp;
