// UpdateBuilderDlg.cpp : ���� ����
//
#include "stdafx.h"
#include "UpdateBuilder.h"
#include "UpdateBuilderDlg.h"
#include "FolderDlg.h"

#include "MZFileSystem.h"
#include ".\updatebuilderdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUpdateBuilderDlg ��ȭ ����



CUpdateBuilderDlg::CUpdateBuilderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateBuilderDlg::IDD, pParent)
	, m_strOld(_T(""))
	, m_strNew(_T(""))
	, m_strOutput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpdateBuilderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OLD, m_strOld);
	DDX_Text(pDX, IDC_EDIT_NEW, m_strNew);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_strOutput);
	DDX_Control(pDX, IDC_RICHEDIT_LOG, m_EditLog);
}

BEGIN_MESSAGE_MAP(CUpdateBuilderDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_OLD, OnBnClickedButtonBrowseOld)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_NEW, OnBnClickedButtonBrowseNew)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_OUTPUT, OnBnClickedButtonBrowseOutput)
	ON_BN_CLICKED(ID_BUILD, OnBnClickedBuild)
	ON_EN_CHANGE(IDC_EDIT_OLD, OnEnChangeEditOld)
	ON_EN_CHANGE(IDC_EDIT_NEW, OnEnChangeEditNew)
	ON_EN_CHANGE(IDC_EDIT_OUTPUT, OnEnChangeEditOutput)
END_MESSAGE_MAP()


// CUpdateBuilderDlg �޽��� ó����

BOOL CUpdateBuilderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CUpdateBuilderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CUpdateBuilderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUpdateBuilderDlg::OnBnClickedButtonBrowseOld()
{
	CFolderDlg dlg("���� ������ ������ �����Ͻʽÿ�.", m_strOld, NULL, NULL, this);
	if(dlg.DoModal() != IDOK) return;

	m_strOld=dlg.GetFolderPath();
	UpdateData(FALSE);
}

void CUpdateBuilderDlg::OnBnClickedButtonBrowseNew()
{
	CFolderDlg dlg("�� ������ ������ �����Ͻʽÿ�.", m_strNew, NULL, NULL, this);
	if(dlg.DoModal() != IDOK) return;

	m_strNew=dlg.GetFolderPath();
	UpdateData(FALSE);
}

void CUpdateBuilderDlg::OnBnClickedButtonBrowseOutput()
{
	CFolderDlg dlg("��Ű�� ������ ����� ������ �����Ͻʽÿ�.", m_strOutput, NULL, NULL, this);
	if(dlg.DoModal() != IDOK) return;

	m_strOutput=dlg.GetFolderPath();
	UpdateData(FALSE);
}

BOOL Copy(const char *szFileName,MZFileSystem *pfs,const char *szBasePath)
{
	char *buffer=NULL;
	const char *szCurr=szFileName;
	const char *szNextSlash;
	while((szNextSlash=strchr(szCurr,'/'))!=NULL){
		
		int nLength=(int)(szNextSlash-szFileName);
		char dirname[_MAX_PATH];
		strncpy(dirname,szFileName,nLength);
		dirname[nLength]=0;

		char buffer[_MAX_PATH];
		sprintf(buffer,"%s%s",szBasePath,dirname);

		CreateDirectory(buffer,NULL);

		szCurr=szNextSlash+1;
	}


	MZFile mzf;
	if(!mzf.Open(szFileName,pfs)) return FALSE;

	size_t nFileLength=mzf.GetLength();
	buffer=new char[nFileLength];
	mzf.Read(buffer,(int)nFileLength);
	mzf.Close();

	char fullfilename[_MAX_PATH];
	sprintf(fullfilename,"%s%s",szBasePath,szFileName);

	FILE *file;
	file=fopen(fullfilename,"wb+");
	if(!file) goto error;

	if(fwrite(buffer,1,nFileLength,file)<nFileLength)
		goto error;

	fclose(file);

	delete buffer;

	return TRUE;

error:

	if(file)
		fclose(file);
	if(buffer)
		delete buffer;
	return FALSE;
}

BOOL CUpdateBuilderDlg::Build()
{
	MZFileSystem oldfs,newfs;

//	newfs.Create("./","update");
	newfs.Create(m_strNew,"update");
	oldfs.Create(m_strOld,"update");

	int nCount=0;
	ClearLog();
	for(int i=0;i<newfs.GetFileCount();i++)
	{
		const char *filename=newfs.GetFileName(i);
		const MZFILEDESC *desc=newfs.GetFileDesc(i);
		if(strlen(filename)==0) continue;

		const MZFILEDESC *olddesc=oldfs.GetFileDesc(filename);
		
		// ������ ���ų�, ����� Ʋ���ų�, ��ġ�� �ٸ��ų�, ��¥�� �ٸ���
		if(!olddesc || desc->m_iSize != olddesc->m_iSize ||
			stricmp(desc->m_szZFileName,olddesc->m_szZFileName) ||
			oldfs.GetCRC32(filename)!=newfs.GetCRC32(filename))
		{
			if(!Copy(filename,&newfs,m_strOutput))
			{
				Log("file copy error : %s\r\n",filename);
				return FALSE;
			}

			char buffer[256];
			sprintf(buffer,"%s",filename);

			if(strlen(desc->m_szZFileName))
			{
				strcat(buffer," in ");
				strcat(buffer,desc->m_szZFileName);
			}
			strcat(buffer,"\r\n");
			Log(buffer);

			nCount++;
		}
	}

	Log("\r\n %d file copy completed\r\n",nCount);

	return true;
}

void CUpdateBuilderDlg::OnBnClickedBuild()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Build();
}

void CUpdateBuilderDlg::ClearLog()
{
	m_EditLog.SetWindowText("");
}

void __cdecl CUpdateBuilderDlg::Log(const char *pFormat,...)
{
	char temp[256];

	va_list args;

	va_start(args,pFormat);
	vsprintf(temp,pFormat,args);
	va_end(args);

	int nBegin, nEnd;
	nBegin=m_EditLog.LineIndex(m_EditLog.GetLineCount());
	nEnd=nBegin + m_EditLog.LineLength(nBegin);
	m_EditLog.SetSel(nEnd,nEnd);

	m_EditLog.SetFocus();
	m_EditLog.ReplaceSel(temp);
}

void CUpdateBuilderDlg::OnEnChangeEditOld()
{
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CDialog::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
}

void CUpdateBuilderDlg::OnEnChangeEditNew()
{
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CDialog::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
}

void CUpdateBuilderDlg::OnEnChangeEditOutput()
{
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CDialog::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
}
