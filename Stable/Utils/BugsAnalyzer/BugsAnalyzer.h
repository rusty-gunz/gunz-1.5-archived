// BugsAnalyzer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CBugsAnalyzerApp:
// �� Ŭ������ ������ ���ؼ��� BugsAnalyzer.cpp�� �����Ͻʽÿ�.
//

class CBugsAnalyzerApp : public CWinApp
{
public:
	CBugsAnalyzerApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CBugsAnalyzerApp theApp;
