// DBQuestItemEditor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CDBQuestItemEditorApp:
// �� Ŭ������ ������ ���ؼ��� DBQuestItemEditor.cpp�� �����Ͻʽÿ�.
//

class CDBQuestItemEditorApp : public CWinApp
{
public:
	CDBQuestItemEditorApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CDBQuestItemEditorApp theApp;
