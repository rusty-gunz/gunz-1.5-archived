// BirdAgent.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CBirdAgentApp:
// �� Ŭ������ ������ ���ؼ��� BirdAgent.cpp�� �����Ͻʽÿ�.
//

class CBirdAgentApp : public CWinApp
{
protected:
	
public:
	CBirdAgentApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CBirdAgentApp theApp;
