// ItemConverter.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once


#include "resource.h"		// �� ��ȣ


// CItemConverterApp:
// �� Ŭ������ ������ ���ؼ��� ItemConverter.cpp�� �����Ͻʽÿ�.
//

class CItemConverterApp : public CWinApp
{
public:
	CItemConverterApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CItemConverterApp theApp;
