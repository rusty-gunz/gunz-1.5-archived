#include "StdAfx.h"
#include ".\updater.h"
#include "MProcessController.h"
#include "MDebug.h"
#include "mcrc32.h"

CUpdater::CUpdater(void) : m_IsEnableServerPatch( false ), m_IsEnableAgentPatch( false )
{
}

CUpdater::~CUpdater(void)
{
}


bool CUpdater::ConnectPatchFileServer()
{
	if( 0 != m_pInetSession )
	{
		m_pInetSession->Close();
		delete m_pInetSession;
		m_pInetSession = 0;
	}

	m_pInetSession = new CInternetSession();
	if( 0 == m_pInetSession )
		return false;

	try
	{
		m_pFtpConnection = m_pInetSession->GetFtpConnection( m_strServerName, m_strUserName, m_strPassword );
	}
	catch( CInternetException* pEx )
	{
		TCHAR szErr[ 1024 ];

		pEx->GetErrorMessage( szErr, 1024 );
		
		mlog( "CUpdater::ConnectPatchFileServer - %s\n", szErr );

		return false;
	}

	if( 0 == m_pFtpConnection )
		return false;

	return true;
}


bool CUpdater::DownloadPatchInfoFile()
{
	// ���� �ӽ� ������ ������ ���� ����� �־� ��.
	if( !FindFolder("", "Temp") )
		CreateDirectory( m_strLocalTempDir, NULL );
	
	if( 0 == m_pFtpConnection )
		return false;

	if( !m_pFtpConnection->SetCurrentDirectory(m_strFtpRootDir) )
		return false;
	
	CString strFileName;
	BOOL	bContinue;

	CFtpFileFind ftpFind( m_pFtpConnection );
	bContinue = ftpFind.FindFile( m_strFtpRootDir );
	if( !bContinue )
		return false;

	while( bContinue )
	{
		bContinue = ftpFind.FindNextFile();
		strFileName = ftpFind.GetFileName();
		
		if( ftpFind.IsDirectory() )
		{
			continue;
		}

		if( !m_pFtpConnection->GetFile(strFileName, MakeTempDirFilePath(strFileName), TRUE) )
		{
			mlog( "CUpdater::DownloadPatchInfoFile - %s���� �ٿ�ε� ����.\n", strFileName );
			ftpFind.Close();
			return false;
		}
	}

	ftpFind.Close();

	return true;
}


bool CUpdater::Init()
{
	if( !LoadConfigureFile() )
		return false;
	
	return true;
}


bool CUpdater::DownloadServer()
{
	if( (0 == m_pInetSession) || (0 == m_pFtpConnection) )
		return false;

	RemakeTempDirectory( m_strLocalTempDir.GetBuffer() );

	if( !DownloadPatchInfoFile() )
		return false;
	
	if( !LoadListFile() )	
		return false;
	    
	if( !DownloadServerPatchFile() )
		return false;
	
	return true;
}

bool CUpdater::ServerPatching()
{
	// �ӽ� �������� ���� ������ ����.
	if( !CopyServerPatchFile(m_strLocalTempDir) )
		return false;
	
	// �ӽ� ���� ���� ����.
	RemakeTempDirectory( m_strLocalTempDir );

	return true;
}


void CUpdater::DisconnectPatchFileServer()
{
	if( 0 != m_pFtpConnection )
	{
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
		m_pFtpConnection = 0;
	}

	if( 0 != m_pInetSession )
	{
		m_pInetSession->Close();
		delete m_pInetSession;
		m_pInetSession = 0;
	}
}


bool CUpdater::DownloadServerPatchFile()
{
	// ������ ���� ������ �ٿ� ������ CRC32�� �˻���.
	if( m_IsEnableServerPatch )
	{
		DownloadPatchFile( m_strMatchServerDir.GetBuffer() );
		if( m_dwServerCRC32 == MakeFileCRC32("server.zip") )
			return true;
	}

	return false;
}


bool CUpdater::LoadListFile()
{
	CString strFullName = MakeDownloadedPatchInfoFilePath();

	FILE* fp = fopen( strFullName.GetBuffer(), "r" );
	if( 0 == fp )
		return false;

	DWORD dwCRC32;
	char buf[ 512 ];
	char szDir[ 512 ] = {0};

	while( true )
	{
		memset( buf, 0, 512 );
		if( 0 == fgets(buf, 512, fp) )
		{
			break;
		}

		// ���� ������ �ش� ������ �ִ� ���� ������ checksum�� �о� ��.
		sscanf( buf, "%s %u", szDir, &dwCRC32 );

		if( 0 == strcmp(szDir, m_strMatchServerDir.GetBuffer()) )
		{
			m_IsEnableServerPatch = true;
			m_dwServerCRC32 = dwCRC32;
		}

		if( 0 == strcmp(szDir, m_strMatchAgentDir.GetBuffer()) )
		{
			m_IsEnableAgentPatch = true;		
			m_dwAgentCRC32 = dwCRC32;
		}
	}

	fclose( fp );

	return true; // (bIsCheckMatchServerDir && bIsCheckMatchAgentDir);
}


bool CUpdater::CopyServerPatchFile( const char* pszDstName )
{
	if( 0 == pszDstName )
		return false; 

	BOOL bContinue;
	CString strDirName = pszDstName;
	CString strPathName;
	CString strFullName;
	CString strPartName;
	CString strDstFullPath;

	// �ӽ� ���� �˻�.

	CFileFind fileFind;	

	bContinue = fileFind.FindFile( strDirName + ".\\*" );
	if( !bContinue )
		return false;

	while( bContinue )
	{
		bContinue = fileFind.FindNextFile();
		if( fileFind.IsDirectory() )
		{
			if( !IsValidDir(fileFind.GetFileName()) )
				continue;

			strPathName = fileFind.GetFilePath();
			strPathName.Remove( '.' );

			CString strRealDir = MakeRealServerDirFilePath( TokenizeFromBack(m_strTok, strDirName) );

			// �������� ������ �����ϱ����� �ش� ������ �����ϴ��� �˻��ؾ� ��.
			// ���� ���� �������� ������ ���� �������� ���� ���縦 ��.
			// ������������ ���� ���縦 �Ұ�� ���������� ���������� �������� ����.
			if( !FindFolder(strRealDir, fileFind.GetFileName()) )
			{
				// craete new folder
				
				if( !MakeSubDirToServerRealDir(fileFind.GetFilePath()) )
					return false;
			}

 			CopyServerPatchFile( strPathName.GetBuffer() );
		}
		else
		{
			// copy file

			strPartName = TokenizeFromBack( m_strTok, fileFind.GetFilePath() );
			
			// ������ ����� ��θ� ����.
			strDstFullPath = MakeRealServerDirFilePath( strPartName );

			// ���� ������ �Ӽ��� �б� �����̸� �ٲ���� ��.
			CFile		File;
			CFileStatus FileStatus;

			if( File.GetStatus(fileFind.GetFilePath(), FileStatus) )
			{
				if( FileStatus.m_attribute & CFile::readOnly )
				{
					// ���� �б� �����̸� �Ӽ��� ������.
					FileStatus.m_attribute &= ~CFile::readOnly;
					File.SetStatus( fileFind.GetFilePath(), FileStatus );
				} 

				if( !CopyFile( fileFind.GetFilePath(), strDstFullPath, FALSE ) )
					return false;
			}
			else
				return false;
		}
	}

	fileFind.Close();

	return true;
}

// ���� �����κ��� ������� ��ο� �ش��ϴ� strDst�� ���� �˻�.
bool CUpdater::FindFolder( const CString& strCur, const CString& strDst )
{
	CFileFind fileFind;	

	BOOL bContinue = fileFind.FindFile( strCur + ".\\*" );
	if( !bContinue )
		return false;

	while( bContinue )
	{
		bContinue = fileFind.FindNextFile();
		CString tepName = fileFind.GetFileName();
		if( fileFind.IsDirectory() )
		{
			if( !IsValidDir(fileFind.GetFileName()) )
				continue;

			if( strDst == tepName )
			{
				fileFind.Close();
				return true;
			}
		}
	}

	fileFind.Close();

	return false;
}


bool CUpdater::LoadConfigureFile()
{
	char szVal[ 512 ];

	/// FTP Server����.
	GetPrivateProfileString( "FTP_SERVER_INFO", "ServerName", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strServerName = szVal;

	GetPrivateProfileString( "FTP_SERVER_INFO", "UserName", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strUserName = szVal;

	GetPrivateProfileString( "FTP_SERVER_INFO", "Password", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strPassword = szVal;

 	GetPrivateProfileString( "FTP_SERVER_INFO", "FtpRootDir", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strFtpRootDir = szVal;

	GetPrivateProfileString( "FTP_SERVER_INFO", "FtpListFile", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strFtpListFile = szVal;

	GetPrivateProfileString( "FTP_SERVER_INFO", "MatchServerDir", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
    m_strMatchServerDir = szVal;

	GetPrivateProfileString( "FTP_SERVER_INFO", "MatchAgentDir", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strMatchAgentDir = szVal;


	// GENERAL_INFO
	GetPrivateProfileString( "GENERAL_INFO", "LocalTempDir", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strLocalTempDir = szVal;

	GetPrivateProfileString( "GENERAL_INFO", "Tok", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strTok = szVal;

	GetPrivateProfileString( "GENERAL_INFO", "SERVERIP", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strServerIP = szVal;	
	mlog( "Server IP:%s\n", szVal );

	GetPrivateProfileString( "GENERAL_INFO", "PORT", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_nPort = atoi( szVal );


	/// MatchServer����.
	GetPrivateProfileString( "MATCH_SERVER_INFO", "LocalDestServerRootDir", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strLocalDestServerRootDir = szVal;

	GetPrivateProfileString( "MATCH_SERVER_INFO", "GameServerPath", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strGameServerPath = szVal;

	GetPrivateProfileString( "MATCH_SERVER_INFO", "GameServerName", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strGameServerName = szVal;

	
	/// MATCH_AGENT_INFO����.
	GetPrivateProfileString( "MATCH_AGENT_INFO", "LocalDestAgentRootDir", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strLocalDestAgentRootDir = szVal;

	GetPrivateProfileString( "MATCH_AGENT_INFO", "AgentPath", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strAgentServerPath = szVal;

	GetPrivateProfileString( "MATCH_AGENT_INFO", "AgentName", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	m_strAgentServerName = szVal;

	GetPrivateProfileString( "QUALIFICATION", "IP", "", szVal, 512, CONFINGURE_FILE );
	if( 0 == strlen(szVal) ) { return false; }
	ParseIP( szVal );
	

	m_bSuccess = true;

	return true;
}


void CUpdater::RemakeTempDirectory( const char* pszDirName )
{
	if( 0 == pszDirName )
		return;

	CString strFileName = pszDirName;
	CString strFilePath;
	CString strFullName;
	CFileFind fileFind;
	bool bDelete = false;
	BOOL bContinue = fileFind.FindFile( strFileName + "\\*" );
	if( !bContinue )
		return;
	
	while( bContinue )
	{
		bContinue = fileFind.FindNextFile();

		if( fileFind.IsDirectory() )
		{
			strFileName = fileFind.GetFileName();
			if( !IsValidDir(strFileName) )
				continue;

			strFilePath = fileFind.GetFilePath();
			strFilePath.Remove( '.' );
            
			// Directory�� ������ ����� ���ؼ� ����ȣ���� ��.
			RemakeTempDirectory( strFilePath.GetBuffer() );

			strFullName = strFilePath + '\\';
			RemoveDirectory( strFullName );
		}
		else
		{
			strFilePath = fileFind.GetFilePath();
			DeleteFile( strFilePath );
		}
	}

	fileFind.Close();
}


bool CUpdater::StopServerProcess()
{
	if( FindServerProcess() )
	{
		// ���� ���μ����� �������̸� ������Ŵ.
		return StopProcess( m_strGameServerPath );
	}
	
	return true;
}


bool CUpdater::FindServerProcess()
{
	return FindProcess( m_strGameServerName );
}


///
// First : 2005.06.02 �߱���.
// Last  : 2005.06.02 �߱���.
// FTP�����κ��� �ٿ���� Patch������ �ӽ� ������ Ǯ����� �غ� �۾��� ��.
///
bool CUpdater::PrepareServerPatching()
{
	return ( 0 == system(".\\PrepareServerPatch.bat") );
}

bool CUpdater::StartServerProcess()
{
	// ���� �ٽ� ����.
	if( !FindServerProcess() )
	{
		char temp_log[256] = {0, };
		SYSTEMTIME st;
		memset(&st, 0, sizeof(SYSTEMTIME));
		GetLocalTime(&st);
		wsprintf(temp_log, " - Start Server Process [%4d/%2d/%2d %2d:%2d:%2d]\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		mlog(temp_log);
		return StartProcess( m_strGameServerPath.c_str() );
	}
	return true;
}


const CString CUpdater::TokenizeFromBack( const CString& strTok, CString& strSrc )
{
	int index = strSrc.Find( m_strTok );
	while( true )
	{
		index += 5;
		int tmpIndex = strSrc.Find( strTok, index );
		if( -1 == tmpIndex )
			break;
		index = tmpIndex;
	}

	CString strValidPath;
	if( index < strSrc.GetLength() )
		strValidPath.Insert( 0, strSrc.GetBuffer() + index );

	return strValidPath;
}



BOOL CUpdater::MakeSubDirToServerRealDir( const CString& strSubDirPath )
{
	CString strTemp	  = strSubDirPath;
	CString strNewDir = strSubDirPath;
	
	int index = strNewDir.ReverseFind( '\\' );
	if( -1 == index )
	{
		// error
		return false;
	}

	strNewDir.Delete( index, strNewDir.GetLength() - index );
	CString strDestFullDir = MakeRealServerDirFilePath( TokenizeFromBack(m_strTok, strTemp) );
	
	return CreateDirectory( strDestFullDir, NULL );
}

/*
bool CUpdater::FindAgentServerProcess()
{
	return FindProcess( m_strAgentServerName );
}
*/

bool CUpdater::StopAgent()
{
	if( AgentPatching() )
		return StopProcess( m_strAgentServerPath );
	return true;
}


bool CUpdater::StartAgent()
{
	// if( !AgentPatching() )
	if( !FindAgentProcess() )
		return StartProcess( m_strAgentServerPath );
	return true;
}


bool CUpdater::FindProcess( const string strProcess )
{
	PROCESSENTRY32 pe32;
	return MProcessController::FindProcessByName( strProcess.c_str(), &pe32 );
}


bool CUpdater::StopProcess( const string strProcessPath )
{
	HANDLE hProcess = MProcessController::OpenProcessHandleByFilePath( strProcessPath.c_str() );
	if( 0 != hProcess && MProcessController::StopProcess(hProcess) )
		return true;
	return false;
}


bool CUpdater::StartProcess( const string strProcessPath )
{
	return MProcessController::StartProcess( strProcessPath.c_str(), FALSE );
}

bool CUpdater::DownloadAgent()
{
	if( (0 == m_pInetSession) || (0 == m_pFtpConnection) )
		return false;
	
	RemakeTempDirectory( m_strLocalTempDir.GetBuffer() );

	if( !DownloadPatchInfoFile() )
		return false;
	
	if( !LoadListFile() )	
		return false;

	if( !DownloadAgentPatchFile() )
		return false;
	    
	return true;
}


bool CUpdater::DownloadAgentPatchFile()
{
	if( m_IsEnableAgentPatch )
	{
		DownloadPatchFile( m_strMatchAgentDir.GetBuffer() );
		if(m_dwAgentCRC32 == MakeFileCRC32("agent.zip") )
			return true;
	}

	return false;
}


bool CUpdater::FindAgentProcess()
{
	return FindProcess( m_strAgentServerName );
}


bool CUpdater::DownloadPatchFile( const string& strSrcDir )
{
	if( 0 == m_pFtpConnection )
		return false;

	BOOL	bContinue;
	CString strCurDir;
	CString strFileName;
	
	if( !m_pFtpConnection->SetCurrentDirectory(strSrcDir.c_str()) )
		return false;

	if( !m_pFtpConnection->GetCurrentDirectory(strCurDir) )
		return false;

	strCurDir += "/*";

	CFtpFileFind ftpFind( m_pFtpConnection );

	if( !(bContinue = ftpFind.FindFile(strCurDir)) )
	{
		// ������ ����.
		return false;
	}

	CString strLocalFileName;

	while( bContinue )
	{
		bContinue			= ftpFind.FindNextFile();
		strFileName			= ftpFind.GetFileName();
		strLocalFileName	= MakeTempDirFilePath( strFileName );

		if( !m_pFtpConnection->GetFile(strFileName,  strLocalFileName, TRUE) )
		{
			mlog( "CUpdater::DownloadPatchFile - %s���� �ٿ�ε� ����.\n", strFileName );
			return false;
		}
	}

	ftpFind.Close();

	return true;
}


bool CUpdater::PrepareAgentPatching()
{
	return ( 0 == system(".\\PrepareAgentPatch.bat") );
}


bool CUpdater::AgentPatching()
{
	// �ӽ� �������� ���� ������ ����.
	if( !CopyAgentPatchFile(m_strLocalTempDir) )
		return false;
	
	// �ӽ� ���� ���� ����.
	RemakeTempDirectory( m_strLocalTempDir );

	return true;
}


bool CUpdater::CopyAgentPatchFile( const char* pszDstName )
{
	if( 0 == pszDstName )
		return false; 

	BOOL bContinue;
	CString strDirName = pszDstName;
	CString strPathName;
	CString strFullName;
	CString strPartName;
	CString strDstFullPath;

	// �ӽ� ���� �˻�.

	CFileFind fileFind;	

	bContinue = fileFind.FindFile( strDirName + ".\\*" );
	if( !bContinue )
		return false;

	while( bContinue )
	{
		bContinue = fileFind.FindNextFile();
		if( fileFind.IsDirectory() )
		{
			if( !IsValidDir(fileFind.GetFileName()) )
				continue;

			strPathName = fileFind.GetFilePath();
			strPathName.Remove( '.' );

			CString strRealDir = MakeRealAgentDirFilePath( TokenizeFromBack(m_strTok, strDirName) );

			// �������� ������ �����ϱ����� �ش� ������ �����ϴ��� �˻��ؾ� ��.
			// ���� ���� �������� ������ ���� �������� ���� ���縦 ��.
			// ������������ ���� ���縦 �Ұ�� ���������� ���������� �������� ����.
			if( !FindFolder(strRealDir, fileFind.GetFileName()) )
			{
				// craete new folder
				
				if( !MaekSubDirToAgentRealDir(fileFind.GetFilePath()) )
					return false;
			}

 			CopyServerPatchFile( strPathName.GetBuffer() );
		}
		else
		{
			// copy file

			strPartName = TokenizeFromBack( m_strTok, fileFind.GetFilePath() );
			
			// ������ ����� ��θ� ����.
			strDstFullPath = MakeRealAgentDirFilePath( strPartName );

			if( !CopyFile( fileFind.GetFilePath(), strDstFullPath, FALSE ) )
				return false;
		}
	}

	fileFind.Close();

	return true;
}


BOOL CUpdater::MaekSubDirToAgentRealDir( const CString& strSubDirPath )
{
	CString strTemp	  = strSubDirPath;
	CString strNewDir = strSubDirPath;
	
	int index = strNewDir.ReverseFind( '\\' );
	if( -1 == index )
	{
		// error
		return false;
	}

	strNewDir.Delete( index, strNewDir.GetLength() - index );
	CString strDestFullDir = MakeRealAgentDirFilePath( TokenizeFromBack(m_strTok, strTemp) );
	
	return CreateDirectory( strDestFullDir, NULL );
}


void CUpdater::ParseIP( const string& strIPs )
{
	if( strIPs.empty() )
		return;

	string strTok( "," );
	string strSub;
	size_t idxStart;
	size_t idxPos;

	idxStart = idxPos = 0;

	while( true )
	{
		idxPos = strIPs.find_first_of( strTok, idxStart );
		if( string::npos != idxPos )
		{
			strSub	 = strIPs.substr( idxStart, idxPos - idxStart );	
			idxStart = idxPos + 1;

			m_vConnectableIP.push_back( strSub );
		}
		else
		{
			strSub = strIPs.substr( idxStart );

			m_vConnectableIP.push_back( strSub );
			break;
		}
	}
}


bool CUpdater::IsConnectableIP( const string& strIP )
{
	if( strIP.empty() )
		return false;

	vector< string >::iterator it  = m_vConnectableIP.begin();
	vector< string >::iterator end = m_vConnectableIP.end();

	for( ; it != end; ++it )
	{
		if( 0 == it->compare(strIP) )
			return true;
	}

	return false;
}


const DWORD CUpdater::MakeFileCRC32( const string& strFileName )
{
	if( strFileName.empty() )
		return 0;

	CString strReadFileName = MakeTempDirFilePath( strFileName.c_str() );

	// ���̳ʸ��� ��� �����͸� ����.
	CFile file;
	CFileException e;
	if( !file.Open(strReadFileName, CFile::modeRead | CFile::typeBinary, &e) )
	{
		char szErr[ 1024 ] = {0,};
		e.GetErrorMessage( szErr, 1024 );

#ifdef _DEBUG
		mlog( "CUpdater::MakeFileCRC32 - %s\n", szErr );
#endif
		return 0;
	}

	const unsigned int nFileLen = file.GetLength();
	char* szFileData = new char[ nFileLen + 1 ];
	file.Read( szFileData, nFileLen );
	file.Close();

	// ���� �����ͷ� CRC32����.
	return MCRC32::BuildCRC32( reinterpret_cast<BYTE*>(szFileData), nFileLen );
}