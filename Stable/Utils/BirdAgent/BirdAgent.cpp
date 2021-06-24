// BirdAgent.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "MALConverter.h"
#include "stdafx.h"
#include "BirdAgent.h"
#include "BirdAgentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MDebug.h"
extern MConverter	g_DBConverter;


// CBirdAgentApp

BEGIN_MESSAGE_MAP(CBirdAgentApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBirdAgentApp ����

CBirdAgentApp::CBirdAgentApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CBirdAgentApp ��ü�Դϴ�.

CBirdAgentApp theApp;


// CBirdAgentApp �ʱ�ȭ

BOOL CBirdAgentApp::InitInstance()
{
	InitLog(MLOGSTYLE_DEBUGSTRING|MLOGSTYLE_FILE, "log.txt");

	// Ŀ�ǵ�ó��
	CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);
    CString param = cmdInfo.m_strFileName;
	param = m_lpCmdLine;
//	if (!stricmp(m_lpCmdLine, "/convert"))
	{
		// �ٷ� ����
//		g_DBConverter.ConvertActionLeague();
		g_DBConverter.ExportRiddickEventUserid();
		return FALSE;
	}

	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControls()�� �ʿ��մϴ�. 
	// InitCommonControls()�� ������� ������ â�� ���� �� �����ϴ�.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CBirdAgentDlg dlg;
	m_pMainWnd = &dlg;

    
	

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ ��ȭ ���ڰ� Ȯ���� ���� �������� ��� ó����
		// �ڵ带 ��ġ�մϴ�.
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

