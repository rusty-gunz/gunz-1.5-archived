// MatchServerTools.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CMatchServerToolsApp:
// �� Ŭ������ ������ ���ؼ��� MatchServerTools.cpp�� �����Ͻʽÿ�.
//

class CMatchServerToolsApp : public CWinApp
{
public:
	CMatchServerToolsApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CMatchServerToolsApp theApp;
