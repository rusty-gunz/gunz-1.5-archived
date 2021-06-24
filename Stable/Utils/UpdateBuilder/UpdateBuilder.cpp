// UpdateBuilder.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "UpdateBuilder.h"
#include "UpdateBuilderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUpdateBuilderApp

BEGIN_MESSAGE_MAP(CUpdateBuilderApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUpdateBuilderApp ����

CUpdateBuilderApp::CUpdateBuilderApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CUpdateBuilderApp ��ü�Դϴ�.

CUpdateBuilderApp theApp;

#define REG_COMPANY_NAME	"MAIET entertainment"
#define REG_KEY_OLD			"old"
#define REG_KEY_NEW			"new"
#define REG_KEY_OUTPUT		"output"

// CUpdateBuilderApp �ʱ�ȭ
BOOL CUpdateBuilderApp::InitInstance()
{

	BOOL bCreated=CreateDirectory("test/test2/test3",NULL);

	HANDLE hFile;
	hFile = CreateFile("test", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
//	WriteFile(hFile,&hFile,sizeof(HANDLE),NULL,NULL);
	CloseHandle(hFile);


	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControls()�� �ʿ��մϴ�. 
	// InitCommonControls()�� ������� ������ â�� ���� �� �����ϴ�.
	InitCommonControls();
	AfxInitRichEdit2();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.

	SetRegistryKey(_T(REG_COMPANY_NAME));

	CUpdateBuilderDlg dlg;

	dlg.m_strOld=GetProfileString("",REG_KEY_OLD);
	dlg.m_strNew=GetProfileString("",REG_KEY_NEW);
	dlg.m_strOutput=GetProfileString("",REG_KEY_OUTPUT);

	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		WriteProfileString("",REG_KEY_OLD,dlg.m_strOld);
		WriteProfileString("",REG_KEY_NEW,dlg.m_strNew);
		WriteProfileString("",REG_KEY_OUTPUT,dlg.m_strOutput);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ ��ȭ ���ڰ� ��Ҹ� ���� �������� ��� ó����
		// �ڵ带 ��ġ�մϴ�.
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�
	// ���� ���α׷��� ���� �� �ֵ��� FALSE�� ��ȯ�մϴ�.
	return FALSE;
}
