// LocatorTester.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ




// CLocatorTesterApp:
// �� Ŭ������ ������ ���ؼ��� LocatorTester.cpp�� �����Ͻʽÿ�.
//

class CLocatorTesterApp : public CWinApp
{
public:
	CLocatorTesterApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()


};

extern CLocatorTesterApp theApp;
