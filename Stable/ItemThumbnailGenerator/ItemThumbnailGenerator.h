// ItemThumbnailGenerator.h : ItemThumbnailGenerator ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"       // �� ��ȣ


// CItemThumbnailGeneratorApp:
// �� Ŭ������ ������ ���ؼ��� ItemThumbnailGenerator.cpp�� �����Ͻʽÿ�.
//

class CItemThumbnailGeneratorApp : public CWinApp
{
public:
	CItemThumbnailGeneratorApp();


// ������
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CItemThumbnailGeneratorApp theApp;
