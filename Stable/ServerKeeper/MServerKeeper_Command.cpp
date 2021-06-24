#include "stdafx.h"
#include "MServerKeeper.h"
#include "MSharedCommandTable.h"
#include "MErrorTable.h"
#include "MDebug.h"
#include "Updater.h"
#include "MCommandBuilder.h"
#include "MMatchSchedule.h"



bool MServerKeeper::OnCommand(MCommand* pCommand)
{
	if( MServer::OnCommand(pCommand) )
		return true;

	switch(pCommand->GetID()){
		// Keeper Manager�� ����.
		case MC_KEEPER_MANAGER_CONNECT :
			{
				onKeeperManagerConnect( pCommand->GetSenderUID() );
				return true;
			}

		case MC_REQUEST_KEEPER_CONNECT_MATCHSERVER :
			{
				OnRequestKeeperConnectMatchServer( pCommand->GetSenderUID() );
			}
			break;

		case  MC_RESPONSE_KEEPER_CONNECT_MATCHSERVER :
			{
				MUID uidAlloc;

				pCommand->GetParameter( &uidAlloc, 0, MPT_UID );

				OnResponseKeeperConnectMatchServer( pCommand->GetSenderUID(), uidAlloc );
			}
			break;

		case MC_REQUEST_DOWNLOAD_SERVER_PATCH_FILE :
			{
				OnRequestDownloadServerPatchFile( pCommand->GetSenderUID() );
			}
			break;

		case MC_REQUEST_START_SERVER :
			{
				OnRequestStartServer( pCommand->GetSenderUID() );
			}
			break;

		case MC_REQUEST_STOP_SERVER :
			{
				OnRequestStopServer( pCommand->GetSenderUID() );
			}
			break;

		case MC_RESPONSE_SERVER_HEARHEAT :
			{
				OnResponseServerHeartbeat( pCommand->GetSenderUID() );
			}
			break;

		case MC_CHECK_KEEPER_MANAGER_PING :
			{
				OnCheckPing( pCommand );
				return true;
			}

		//PostSafeQueue(pCmd);
		case MC_DEBUG_TEST:
			{
//				DebugTest();
				return true;
			}

		case MC_RESPONSE_MATCHSERVER_STATUS :
			{
				SERVER_ERR_STATE OpenDB;
				char szServerResVer[ 128 ] = {0,};
				unsigned char nAgentCount = 0;

				pCommand->GetParameter( &OpenDB, 0, MPT_INT );
				pCommand->GetParameter( szServerResVer, 1, MPT_STR, 128 );
				pCommand->GetParameter( &nAgentCount, 2, MPT_UCHAR );

				OnResponseMatchServerStatus( OpenDB, szServerResVer, nAgentCount );
			}
			return true;

		case MC_REQUEST_REFRESH_SERVER :
			{
				OnRequestRefreshServer( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_PREPARE_SERVER_PATCH :
			{
				OnRequestPrepareServerPatch( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_SERVER_PATCH :
			{
				OnRequestServerPatch( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_STOP_AGENT_SERVER :
			{
				OnRequestStopAgent( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_START_AGENT_SERVER :
			{
				OnRequestStartAgent( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_CONFIG_STATE :
			{
				OnRequestConfigState( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_SET_ONE_CONFIG :
			{
				COLUMN_ID		nColumnID;
				CONFIG_STATE	nConfigState;

				pCommand->GetParameter( &nColumnID, 0, MPT_INT );
				pCommand->GetParameter( &nConfigState, 1, MPT_INT );

				OnRequestSetOneConfig( nColumnID, nConfigState );
			}
			return true;

		case MC_REQUEST_KEEPERMGR_ANNOUNCE :
			{
				char szAnnounce[ 256 ];

				pCommand->GetParameter( szAnnounce, 0, MPT_STR, 256 );

				OnRequestKeeperMgrAnnounce( szAnnounce );
			}
			return true;

		case MC_MATCH_ANNOUNCE :
			{
				// �׳� ����.
			}
			return true;

		case MC_REQUEST_DOWNLOAD_AGENT_PATCH_FILE :
			{
				OnRequestDownloadAgentPatchFile( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_PREPARE_AGENT_PATCH :
			{
				OnRequestPrepareAgentPatch( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_AGENT_PATCH :
			{
				OnRequestAgentPatch( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_RESET_PATCH :
			{
				OnRequestResetPatch( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_DISCONNECT_SERVER :
			{
				OnRequestDisconnectServer( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_REBOOT_WINDOWS :
			{
				OnRequestRebootWindows( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_ANNOUNCE_STOP_SERVER :
			{
				OnRequestStopServerWithAnnounce( pCommand->GetSenderUID() );
			}
			return true;

		case MC_RESPONSE_ANNOUNCE_STOP_SERVER :
			{
				OnResponseStopServerWithAnnounce( pCommand->GetSenderUID() );
			}
			return true;

		case MC_ADMIN_ANNOUNCE :
			{
				// MC_RESPONSE_ANNOUNCE_STOP_SERVER���� ������ ������ Keeper���� �׳� ����.
			}
			return true;

		case MC_REQUEST_KEEPER_MANAGER_SCHEDULE :
			{
				int nType;
				int nYear;
				int nMonth;
				int nDay;
				int nHour;
				int nMin;
				int nCount;
				int nCommand;
				char szAnnounce[ 256 ] = {0,};

				pCommand->GetParameter( &nType, 0, MPT_INT );
				pCommand->GetParameter( &nYear, 1, MPT_INT );
				pCommand->GetParameter( &nMonth, 2, MPT_INT );
				pCommand->GetParameter( &nDay, 3, MPT_INT );
				pCommand->GetParameter( &nHour, 4, MPT_INT );
				pCommand->GetParameter( &nMin, 5, MPT_INT );
				pCommand->GetParameter( &nCount, 6, MPT_INT );
				pCommand->GetParameter( &nCommand, 7, MPT_INT );
				pCommand->GetParameter( szAnnounce, 8, MPT_STR, 255 );

				OnRequestKeeperManagerSchedule( pCommand->GetSenderUID(), 
												nType, 
												nYear, 
												nMonth, 
												nDay, 
												nHour, 
												nMin, 
												nCount, 
												nCommand, 
												szAnnounce );
			}
			return true;

		case MC_RESPONSE_KEEPER_MANAGER_SCHEDULE :
			{
				int nCommandType;
				bool bResult;

				pCommand->GetParameter( &nCommandType, 0, MPT_INT );
				pCommand->GetParameter( &bResult, 1, MPT_CHAR );

				OnResponseKeeperManagerSchedule( pCommand->GetSenderUID(), nCommandType, bResult );
			}
			return true;

		case MC_MATCH_SCHEDULE_ANNOUNCE_SEND :
			{
				// ServerKeeper������ ������� �ʴ� Ŀ�ǵ�. �׳� ����.
			}
			return true;

		case MC_REQUEST_CONNECTION_STATE :
			{
				OnResponseConnectionState();
			}
			return true;

		case MC_REQUEST_SERVER_AGENT_STATE :
			{
				OnRequestServerAndAgentState( pCommand->GetSenderUID() );
			}
			return true;

		case MC_REQUEST_START_SERVER_SCHEDULE :
			{
				OnRequestStartServerSchedule();
			}
			return true;

		case MC_REQUEST_WRITE_CLIENT_CRC :
			{
				// ������ ���� ���������� Ȯ��. ���� �������̸� �������� ����.
				// server.ini���Ͽ� �ش� ������ ����.
			}
			return true;

		case MC_REQUEST_KEEPER_RELOAD_SERVER_CONFIG :
			{
				char szFileList[ 1024 ] = {0};

				// get file list.
				pCommand->GetParameter( szFileList, 0, MPT_STR, 1024 );

				OnRequestReloadServerConfig( pCommand->GetSenderUID(), szFileList );
			}
			return true;

		case MC_REQUEST_KEEPER_ADD_HASHMAP :
			{
				char szNewHashValue[ 128 ] = {0,};

				pCommand->GetParameter( szNewHashValue, 0, MPT_STR, 128 );

				OnRequestAddHashMap( pCommand->GetSenderUID(), szNewHashValue );
			}
			return true;

		case MC_RESPONSE_ADD_HASHMAP :
			{
				bool bRes;

				pCommand->GetParameter( &bRes, 0, MPT_BOOL );

				OnResponseAddHashMap( pCommand->GetSenderUID(), bRes );

			}
			return true;

		default:
			_ASSERT(0);	// ���� �ڵ鷯�� ����.
			return false;
	};
	return false;
}



void MServerKeeper::onKeeperManagerConnect( MUID& CommUID )
{
	m_KeeperMgrObj.SetConnection( true );
	m_KeeperMgrObj.SetUID( CommUID );

	m_dwRecvPingTime = timeGetTime();
	SetKeeperMgrPingState( false );

	MCommand* pCmd = CreateCommand( MC_RESPONSE_KEEPER_MANAGER_CONNECT, CommUID );
	if( 0 == pCmd )
		return;

	pCmd->AddParameter( new MCmdParamUID(CommUID) );
	
	PostSafeQueue( pCmd );

	OnResponseConnectionState();
	OnRequestConfigState( m_KeeperMgrObj.GetUID() );
	OnRequestLastJobState( m_KeeperMgrObj.GetUID() );
	OnRequestServerAndAgentState( m_KeeperMgrObj.GetUID() );

	if( IsConnectMatchServer() )
		OnRequestMatchServerStatus();
	else
		OnResponseMatchServerStatus( SES_NO, "NO", 0 );
}	



void MServerKeeper::OnRequestMatchServerStatus()
{
	if( IsConnectMatchServer() )
	{	
		MCommand* pCmd = CreateCommand( MC_REQUEST_MATCHSERVER_STATUS, m_uidMatchServer );
		if( 0 != pCmd )
			PostSafeQueue( pCmd );
	}
}



bool MServerKeeper::RequestConnectServer()
{
	MCommand* pCmd = CreateCommand( MC_REQUEST_KEEPER_CONNECT_MATCHSERVER, m_uidMatchServer );
	if( 0 == pCmd )
		return false;

	PostSafeQueue( pCmd );
	
	return true;
}



void MServerKeeper::OnResponseMatchServerStatus( const SERVER_ERR_STATE OpenDB, const string& strServerResVer, const unsigned char nAgentCount )
{
	if( (0 <= OpenDB) && (m_ServerState.size() > OpenDB) )
	{
		SERVER_ERR_STATE nErrState = SES_NO;

		m_ServerState[ SSK_OPENDB ] = OpenDB;
		if( SES_ERR_DB == OpenDB )
			nErrState = OpenDB;

		if( IsKeeperMgrConnectionValid(m_KeeperMgrObj.GetUID()) )
		{
			MCommand* pCmd = CreateCommand( MC_RESPONSE_SERVER_STATUS, GetKeeperMgrObj().GetUID() );
			if( 0 != pCmd )
			{
				pCmd->AddParameter( new MCmdParamInt(OpenDB) );
				pCmd->AddParameter( new MCmdParamStr(strServerResVer.c_str()) );
				pCmd->AddParameter( new MCmdParamStr(GetServerLastMod().c_str()) );
				pCmd->AddParameter( new MCmdParamStr(GetAgentLastMod().c_str()) );
				pCmd->AddParameter( new MCmdParamStr(GetKeeperLastMod().c_str()) );
				pCmd->AddParameter( new MCmdParamUInt64(GetServerFileSize()) );
				pCmd->AddParameter( new MCmdParamUInt64(GetAgentFileSize()) );
				pCmd->AddParameter( new MCmdParamUInt64(GetKeeperFileSize()) );
				pCmd->AddParameter( new MCmdParamUChar(nAgentCount) );
				
				Post( pCmd );
			}
		}
	}
	else 
	{
		ASSERT ( 0 && "��ϵǾ��ִ� ������ �Ѿ" );
	}
}


void MServerKeeper::OnResponseConnectMacthServer( const MUID& uidMy )
{
	m_This = uidMy;
	m_bIsConnectMatchServer = true;
}


void MServerKeeper::OnRequestDownloadServerPatchFile( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		if( CONFIG_OK_DOWNLOAD == GetConfigState(COLUMN_DOWNLOAD) )
			OnResponseDownloadServerPatchFile();
	}
}


void MServerKeeper::OnResponseDownloadServerPatchFile()
{
	if( GetPatchCheckMap().IsPossibleServerPatchDownload() )
	{
		GetPatchCheckMap().Check( JOB_SUCCESS_DOWNLOAD_SERVER_PATCH_FILE, JOB_DOWNLOADING_SERVER_PATCH );
		OnResponseLastJobState();

		if( !CreateServerDownloadWorkThread() )
		{
			GetPatchCheckMap().Check( JOB_SUCCESS_DOWNLOAD_SERVER_PATCH_FILE, JOB_FAIL_CREATE_SERVER_DOWNLOAD_THREAD );
			OnResponseLastJobState();
		}
	}
}	


void MServerKeeper::OnRequestStopServer( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		if( FindServer() )
			OnResponseStopServer();
	}
}

void MServerKeeper::OnResponseStopServer()
{
	StopServer();
}


void MServerKeeper::OnRequestServerState( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		// PatchInterface�κ��� �������� ���� ��û�� ������, Keeper�� MatchServer�� 
		//  ���� ���� ��û�� ��.
		// MatchServer�κ��� ���� ������ ���� �׶� Keeper�� PatchInterface�� �ش� ������ ������.
		// RequestServerHearbeat();
	}
}


// OnResponseServerHeartbeat������ �Ҹ�����.
void MServerKeeper::OnResponseConnectionState()
{
	if( IsKeeperMgrConnectionValid(m_KeeperMgrObj.GetUID()) )
	{
		MCommand* pCmd = CreateCommand( MC_RESPONSE_CONNECTION_STATE, m_KeeperMgrObj.GetUID() );
		if( 0 == pCmd )
			return;

		pCmd->AddParameter( new MCmdParamInt(GetConnectionState()) );

		PostSafeQueue( pCmd );
	}
}


void MServerKeeper::OnResponseServerHeartbeat( const MUID& uidSender )
{
	if( uidSender != m_uidMatchServer )
		return;

	SetConnectionState( CNN_CONNECTED_SERVER );

	// MatchServer�κ��� ���� ������ ���� ������ ���¸� ���������� ������ �ְ�,
	//  �ش� ������ PatchInterface�� �����ش�.
}


void MServerKeeper::OnRequestStartServer( const MUID& uidKeeperMgr )
{
	mlog("3. OnCommand");
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
		OnResponseStartServer();
}



void MServerKeeper::OnResponseStartServer()
{
	StartServer();
}


void MServerKeeper::OnRequestKeeperConnectMatchServer( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
// 		SetConnectionState( CNN_CONNECTING_TO_SERVER );

		if( !ConnectMatchServer() )
		{
		}
	}
}


void MServerKeeper::OnResponseKeeperConnectMatchServer( const MUID& uidMatchServer, const MUID& uidAlloc )
{
	m_bIsConnectMatchServer	= true;

	UpdateServerHeartbeatTime();

	MCommObject* pObj = GetObject( m_KeeperMgrObj.GetUID() );
	if( 0 != pObj )
	{
		// ���� �Ҵ���� UID�� �缺����.
		pObj->GetCommandBuilder()->SetUID( uidAlloc, m_KeeperMgrObj.GetUID() );

		MCommand* pCmd = CreateCommand( MC_RESPONSE_KEEPER_CONNECT_MATCHSERVER, m_KeeperMgrObj.GetUID() );
		if( 0 != pCmd )
		{
			pCmd->AddParameter( new MCmdParamUID(uidAlloc) );

			PostSafeQueue( pCmd );
		}
	}

	SetConnectionState( CNN_CONNECTED_SERVER );
}


void MServerKeeper::OnRequestPrepareServerPatch( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		if( CONFIG_OK_PREPARE == GetConfigState(COLUMN_PREPARE) )
			OnResponsePrepareServerPatch();
	}
}


void MServerKeeper::OnResponsePrepareServerPatch()
{
	if( GetPatchCheckMap().IsServerPatchDownloadComplete() )
	{
		GetPatchCheckMap().Check( JOB_SUCCESS_PREPARE_SERVER_PATCH, JOB_PREPARING_SERVER_PATCH );
		OnResponseLastJobState();

		if( !CreateServerPreparePatchWorkThread() )
		{
			GetPatchCheckMap().Check( JOB_SUCCESS_PREPARE_SERVER_PATCH, JOB_FAIL_CREATE_SERVER_PREPARE_THREAD );
			OnResponseLastJobState();
		}
	}
}


void MServerKeeper::OnRequestServerPatch( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		// ������ ���� �������̸� ����.
		// if( !FindServer() ) // ������ ����� ������� ��ġ�� ���ؼ�.
		{
			// Keeper�� �ڵ� ���� �ɼ��� ������ ������ �����ؾ� ��.

			if( CONFIG_OK_PATCH == GetConfigState(COLUMN_PATCH) )
				OnResponseServerPatch();
		}
	}
}


void MServerKeeper::OnResponseServerPatch()
{
	if( GetPatchCheckMap().IsServerPrepareComplete() )
	{
		GetPatchCheckMap().Check( JOB_SUCCESS_PATCH_SERVER, JOB_PATCHING_SERVER );
		OnResponseLastJobState();

		if( !CreateServerPatchWorkThread() )
		{
			GetPatchCheckMap().Check( JOB_SUCCESS_PATCH_SERVER, JOB_FAIL_CREATE_SERVER_PATCH_THREAD );
			OnResponseLastJobState();
		}
	}
}


void MServerKeeper::OnRequestRefreshServer( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		OnRequestServerState( uidKeeperMgr );
		OnResponseRefreshServer();
	}
}


void MServerKeeper::OnResponseRefreshServer()
{
	RequestServerHearbeat();
	OnResponseLastJobState();
	OnResponseConfigState();
	OnResponseServerAndAgentState();
	OnRequestMatchServerStatus();
	
	if( IsConnectMatchServer() )
		OnRequestMatchServerStatus();
	else
		OnResponseMatchServerStatus( SES_NO, "NO", 0 );

#ifdef _DEBUG
	mlog( "MServerKeeper::OnResponseRefreshServer\n" );
#endif
}


void MServerKeeper::OnRequestLastJobState( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		OnResponseLastJobState();
	}
}


void MServerKeeper::OnResponseLastJobState()
{
	MCommand* pCmd = CreateCommand( MC_RESPONSE_LAST_JOB_STATE, m_KeeperMgrObj.GetUID() );
	if( 0 == pCmd )
		return;

	pCmd->AddParameter( new MCmdParamInt(m_PatchChkMap.GetLastJob()) );
	pCmd->AddParameter( new MCmdParamInt(m_PatchChkMap.GetLastResult()) );

	PostSafeQueue( pCmd );
}


void MServerKeeper::OnRequestStopAgent( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		if( FindAgent() )
			OnResponseStopAgent();
	}
}


void MServerKeeper::OnResponseStopAgent()
{
	StopAgent();
}


void MServerKeeper::OnRequestStartAgent( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		if( !FindAgent() )
			OnResponseStartAgent();
	}
}


void MServerKeeper::OnResponseStartAgent()
{
	StartAgent();
}


void MServerKeeper::OnRequestConfigState( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		OnResponseConfigState();
	}
}


void MServerKeeper::OnResponseConfigState()
{
	MCommand* pCmd = CreateCommand( MC_RESPONSE_CONFIG_STATE, m_KeeperMgrObj.GetUID() );
	if( 0 == pCmd )
		return;

	pCmd->AddParameter( new MCmdParamInt(GetConfigState(COLUMN_SERVER_START)) );
	pCmd->AddParameter( new MCmdParamInt(GetConfigState(COLUMN_AGENT_START)) );
	pCmd->AddParameter( new MCmdParamInt(GetConfigState(COLUMN_DOWNLOAD)) );
	pCmd->AddParameter( new MCmdParamInt(GetConfigState(COLUMN_PREPARE)) );
	pCmd->AddParameter( new MCmdParamInt(GetConfigState(COLUMN_PATCH)) );

	PostSafeQueue( pCmd );
}


void MServerKeeper::OnRequestSetOneConfig( const COLUMN_ID nColumnID, const CONFIG_STATE nConfigState )
{
	// Ű�ۿ���� ������� ����Ǵ� �κ�.
	AddtionalCheckConfigState( nColumnID, nConfigState );
	SetConfig( nColumnID, nConfigState );

	if( IsKeeperMgrConnectionValid(GetKeeperMgrObj().GetUID()) )
	{
		if( (nColumnID < COLUMN_END) && (nConfigState < CONFIG_END) )
			OnResponseSetOneConfig( nColumnID, nConfigState );
	}
}


void MServerKeeper::OnResponseSetOneConfig( const COLUMN_ID nColumnID, const CONFIG_STATE nConfigState )
{
	MCommand* pCmd = CreateCommand( MC_RESPONSE_SET_ONE_CONFIG, m_KeeperMgrObj.GetUID() );
	if( 0 == pCmd )
		return;

	pCmd->AddParameter( new MCmdParamInt(nColumnID) );
	pCmd->AddParameter( new MCmdParamInt(GetConfigState(nColumnID)) );
	
	PostSafeQueue( pCmd );
}


void MServerKeeper::OnRequestKeeperMgrAnnounce( const char* pszAnnounce )
{
	if( (0 != pszAnnounce) || (256 > strlen(pszAnnounce)) )
	{
		if( IsConnectMatchServer() )
		{
			MCommand* pCmd = CreateCommand( MC_REQUEST_KEEPER_ANNOUNCE, GetMatchServerUID() );
			if( 0 == pCmd )
				return;

			pCmd->AddParameter( new MCmdParamStr(pszAnnounce) );

			Post( pCmd );
		}
	}
}


void MServerKeeper::OnRequestDownloadAgentPatchFile( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		OnResponseDownloadAgentPatchFile();
	}
}


void MServerKeeper::OnResponseDownloadAgentPatchFile()
{
	if( GetPatchCheckMap().IsPossibleAgentPatchDownload() )
	{
		GetPatchCheckMap().Check( JOB_SUCCESS_DOWNLOAD_AGENT_PATCH_FILE, JOB_DOWNLOADING_AGENT_PATCH );
		OnResponseLastJobState();

		if( !CreateAgentDownloadWorkThread() )
		{
			GetPatchCheckMap().Check( JOB_SUCCESS_DOWNLOAD_AGENT_PATCH_FILE, JOB_FAIL_CREATE_AGENT_DOWNLOAD_THREAD );
			OnResponseLastJobState();
		}
	}
}


void MServerKeeper::OnRequestPrepareAgentPatch( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		OnResponsePrepareAgentPatch();
	}
}


void MServerKeeper::OnResponsePrepareAgentPatch()
{
	if( GetPatchCheckMap().IsAgentPatchDownloadComplete() )
	{
		GetPatchCheckMap().Check( JOB_SUCCESS_PREPARE_AGENT_PATCH, JOB_PREPARING_AGENT_PATCH );
		OnResponseLastJobState();

		if( !CreateAgentPreparePatchWorkThread() )
		{
			GetPatchCheckMap().Check( JOB_SUCCESS_PREPARE_AGENT_PATCH, JOB_FAIL_CREATE_AGENT_PREPARE_THREAD );
			OnResponseLastJobState();
		}
	}
}


void MServerKeeper::OnRequestAgentPatch( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		OnResponseAgentPatch();
	}
}


void MServerKeeper::OnResponseAgentPatch()
{
	if( GetPatchCheckMap().IsAgentPrepareComplete() )
	{
		GetPatchCheckMap().Check( JOB_SUCCESS_PATCH_AGENT, JOB_PATCHING_AGENT );
		OnResponseLastJobState();

		if( !CreateAgentPatchWorkThread() )
		{
			GetPatchCheckMap().Check( JOB_SUCCESS_PATCH_AGENT, JOB_FAIL_CREATE_AGENT_PATCH_THREAD );
			OnResponseLastJobState();
		}
	}
}


void MServerKeeper::OnRequestResetPatch( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		OnResponseResetPatch();
	}
}


void MServerKeeper::OnResponseResetPatch()
{
	if( GetPatchCheckMap().IsPossibleReset() )
	{
		GetPatchCheckMap().Reset();

		OnResponseLastJobState();
	}
}


void MServerKeeper::OnRequestDisconnectServer( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		OnResponseDisconnectServer();
	}
}


void MServerKeeper::OnResponseDisconnectServer()
{
	Disconnect( GetMatchServerUID() );

	m_bIsConnectMatchServer = false;

	SetConnectionState( CNN_NOT_CONNECTED_SERVER );

	OnResponseConnectionState();
}


void MServerKeeper::OnRequestRebootWindows( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		OnResponseRebootWindows();
	}
}


void MServerKeeper::OnResponseRebootWindows()
{
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 

	// Get a token for this process. 

	if (!OpenProcessToken(GetCurrentProcess(), 
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		GetPatchCheckMap().Check( JOB_FAIL_REBOOT, JOB_FAIL_REBOOT);
		// OnResponseLastJobState();
		OnRequestLastJobState( m_KeeperMgrObj.GetUID() );
		return;
	}

	// Get the LUID for the shutdown privilege. 

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
		&tkp.Privileges[0].Luid); 

	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

	// Get the shutdown privilege for this process. 

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
		(PTOKEN_PRIVILEGES)NULL, 0); 

	if (GetLastError() != ERROR_SUCCESS) 
	{
		GetPatchCheckMap().Check( JOB_FAIL_REBOOT, JOB_FAIL_REBOOT);
		// OnResponseLastJobState();
		OnRequestLastJobState( m_KeeperMgrObj.GetUID() );
		return; 
	}

	// Shut down the system and force all applications to close. 

	if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0)) 
	{
		GetPatchCheckMap().Check( JOB_FAIL_REBOOT, JOB_FAIL_REBOOT);
		// OnResponseLastJobState();
		OnRequestLastJobState( m_KeeperMgrObj.GetUID() );
		return; 
	}
}


void MServerKeeper::OnRequestStopServerWithAnnounce( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		if( IsConnectMatchServer() )
		{
			MCommand* pCmd = CreateCommand( MC_REQUEST_ANNOUNCE_STOP_SERVER, GetMatchServerUID() );
			if( 0 != pCmd )
				Post( pCmd );
		}
	}
}


void MServerKeeper::OnResponseStopServerWithAnnounce( const MUID& uidMatchServer )
{
	if( uidMatchServer == GetMatchServerUID() )
	{
		GetPatchCheckMap().Check( JOB_ANNOUNCE_STOP_SERVER, JOB_ANNOUNCE_STOP_SERVER );
		
		MCommand* pCmd = CreateCommand( MC_RESPONSE_ANNOUNCE_STOP_SERVER, GetKeeperMgrObj().GetUID() );
		if( 0 != pCmd )
			Post( pCmd );
	}
}


void MServerKeeper::OnRequestKeeperManagerSchedule( const MUID& uidKeeperMgr, 
													const int nType, 
													const int nYear, 
													const int nMonth, 
													const int nDay, 
													const int nHour, 
													const int nMin,
													const int nCount,
													const int nCommand,
													const char* pszAnnounce )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) && IsConnectMatchServer() )
	{
#ifdef _DEBUG
		mlog( "MServerKeeper::OnRequestKeeperManagerSchedule - Schedule info\n => Type:%d, Year:%d, Month:%d, Day:%d, Hour:%d Min:%d, Count:%d, Command:%d, Announce:%s\n",
			nType, nYear, nMonth, nDay, nHour, nMin, nCount, nCommand, pszAnnounce );
#endif

		if( KMSC_RESTART_SERVER == nCommand )
		{
			// ���� ������� Keeper�� ����.

			// �켱 Stop�������� ����� 1�� �������� Start�������� ���� ��.
			MCommand* pCmdStop = CreateCommand( MC_REQUEST_ANNOUNCE_STOP_SERVER, GetMatchServerUID() );
			if( 0 != pCmdStop )
			{
				if( AddDynamicSchedule(m_pScheduler, nType - 1, pCmdStop, nYear, nMonth, nDay, nHour, nMin, nCount) )
				{
					// 1���� ���� ���� ������ ����.
					MCommand* pCmdStart = CreateCommand( MC_REQUEST_START_SERVER_SCHEDULE, GetUID() );
					if( 0 != pCmdStart )
					{
						// 1�������� �Ѿ���� ���� 2�� ����� 1�� ���ҽ� �ð� ����(ex. 59�� + 1)�� �ʿ� ���ٴ� �����Ͽ��� ��. - by �߱���.
						if( AddDynamicSchedule( m_pScheduler, nType - 1, pCmdStart, nYear, nMonth, nDay, nHour, nMin + 1, nCount) )
						{
							// �̹� ��ϵ� �ִ� ���� ���� �������� ������ ����� ����...

							GetPatchCheckMap().Check( JOB_SUCCESS_ADD_RESTART_SERVER_SCHEDULE, JOB_SUCCESS_ADD_RESTART_SERVER_SCHEDULE );
							OnRequestLastJobState( m_KeeperMgrObj.GetUID() );

#ifdef _DEBUG
							mlog( "MServerKeeper::OnRequestKeeperManagerSchedule - Restart schedule is added\n" );
#endif
							return;
						}
						else
						{
							delete pCmdStart;
						}
					}
				}

				delete pCmdStop;
				GetPatchCheckMap().Check( JOB_SUCCESS_ADD_RESTART_SERVER_SCHEDULE, JOB_FAIL_ADD_RESTART_SERVER_SCHEDULE );
				OnRequestLastJobState( m_KeeperMgrObj.GetUID() );

#ifdef _DEBUG
				mlog( "MServerKeeper::OnRequestKeeperManagerSchedule - Restart schedule is failed\n" );
#endif
			}
		}
		else
		{
			MCommand* pCmd = CreateCommand( MC_REQUEST_KEEPER_MANAGER_SCHEDULE, GetMatchServerUID() );
			if( 0 != pCmd )
			{
				pCmd->AddParameter( new MCmdParamInt(nType) );
				pCmd->AddParameter( new MCmdParamInt(nYear) );
				pCmd->AddParameter( new MCmdParamInt(nMonth) );
				pCmd->AddParameter( new MCmdParamInt(nDay) );
				pCmd->AddParameter( new MCmdParamInt(nHour) );
				pCmd->AddParameter( new MCmdParamInt(nMin) );
				pCmd->AddParameter( new MCmdParamInt(nCount) );
				pCmd->AddParameter( new MCmdParamInt(nCommand) );
				pCmd->AddParameter( new MCmdParamStr(pszAnnounce) );

				Post( pCmd );
			}
		}
	}
}


void MServerKeeper::OnResponseKeeperManagerSchedule( const MUID& uidServer, const int nCommandType, const bool bResult )
{
	if( GetMatchServerUID() == uidServer )
	{
		if( KMSC_ANNOUNCE == nCommandType )
		{
			if( bResult )
				GetPatchCheckMap().Check( JOB_SUCCESS_ADD_ANNOUNCE_SCHEDULE, JOB_SUCCESS_ADD_ANNOUNCE_SCHEDULE );
			else
				GetPatchCheckMap().Check( JOB_SUCCESS_ADD_ANNOUNCE_SCHEDULE, JOB_FAIL_ADD_ANNOUNCE_SCHEDULE );

		}
		else if( KMSC_STOP_SERVER == nCommandType )
		{
			if( bResult )
				GetPatchCheckMap().Check( JOB_SUCCESS_ADD_SERVER_STOP_SCHEDULE, JOB_SUCCESS_ADD_SERVER_STOP_SCHEDULE );
			else
				GetPatchCheckMap().Check( JOB_SUCCESS_ADD_SERVER_STOP_SCHEDULE, JOB_FAIL_ADD_SERVER_STOP_SCHEDULE );
		}

		OnRequestLastJobState( m_KeeperMgrObj.GetUID() );
	}
}


void MServerKeeper::OnRequestServerAndAgentState( const MUID& uidKeeperMgr )
{
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) )
	{
		OnResponseServerAndAgentState();
	}
}


void MServerKeeper::OnResponseServerAndAgentState()
{
	MCommand* pCmd = CreateCommand( MC_RESPONSE_SERVER_AGENT_STATE, GetKeeperMgrObj().GetUID() );
	if( 0 != pCmd )
	{
		pCmd->AddParameter( new MCmdParamInt(FindServer() ? RS_RUN : RS_STOP) );
		pCmd->AddParameter( new MCmdParamInt(FindAgent() ? RS_RUN : RS_STOP) );

		Post( pCmd );
	}
}


void MServerKeeper::OnRequestStartServerSchedule()
{
	// �ٽý��۽� ������ �׾����� �˻��Ͽ� ��������� ������ �ð��� ��� ������Ŵ.
	if( !FindServer() )
	{
		// �ڵ����� ������ �Ǿ������� Keeper�� �ڵ����� ����� ���.
		if( CONFIG_AUTO_START_SERVER != GetConfigState(COLUMN_SERVER_START) )
		{
			mlog("4. Keeper Restart");
			StartServer();
		}
	}
	else
	{
		// ���� �ð����� 5�� �����Ͽ� �ٽ� �õ�.
		SYSTEMTIME stTime;
		GetSystemTime( &stTime );

		stTime.wMinute += 5;
		if( 60 <= stTime.wMinute )
		{
			stTime.wMinute -= 60;
			++stTime.wHour;
		}
		stTime.wHour += 9;
		if( 24 <= stTime.wHour )
		{
			stTime.wHour -= 24;
			++stTime.wDay;
		}
		if( GetMaxDay() <= stTime.wDay )
		{
			stTime.wDay -= GetMaxDay();
			++stTime.wMonth;
		}
		if( 12 < stTime.wMonth )
		{
			stTime.wMonth -= 12;
			++stTime.wYear;
		}

		MCommand* pCmd = CreateCommand( MC_REQUEST_START_SERVER_SCHEDULE, GetUID() );
		if( 0 != pCmd )
		{
			if( !AddDynamicSchedule(m_pScheduler, MMatchScheduleData::ONCE, pCmd, stTime.wYear % 100, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, 0) )
				delete pCmd;
		}
	}
}

void MServerKeeper::OnRequestWriteClientCRC( const MUID& uidKeeperMgr, const DWORD dwClientCRC )
{
	/* ����.
	if( IsKeeperMgrConnectionValid(uidKeeperMgr) && !FindServer() && (0 < dwClientCRC) )
	{
		const CString strServerIniPath( GetUpdater.GetServerRootDir() + "\\server.ini" );

		char szVal[ 256 ] = {0,};
		GetPrivateProfileString( "CRC", "GunzClient", "", szVal, 255, strServerIniPath );
		if( 0 != strlen(szVal) )
		{
			if( WritePrivateProfileString( "CRC", "GunzClient", "1", strServerIniPath ) )
			{
				OnResponseWriteClientCRC( uidKeeperMgr, true );
				return;
			}
		}
	}

	OnResponseWriteClientCRC( uidKeeperMgr, false );
	*/
}


void MServerKeeper::OnResponseWriteClientCRC( const MUID& uidKeeperMgr, const bool bResult )
{
}

void MServerKeeper::OnRequestReloadServerConfig( const MUID& uidKeeperMgr, const string& strFileList )
{
	MCommand* pCmd = CreateCommand( MC_REQUEST_RELOAD_CONFIG, GetMatchServerUID() );
	if( 0 != pCmd )
	{
		if( !pCmd->AddParameter(new MCmdParamStr(strFileList.c_str())) )
		{
			mlog( "MServerKeeper::OnRequestReloadServerConfig - Ŀ�ǵ� ���� ����.\n" );
			delete pCmd;
			return;
		}

		Post( pCmd );
	}
}


void MServerKeeper::OnRequestAddHashMap( const MUID& uidKeeperMgr, const string& strNewHashValue )
{
	MCommand* pCmd = CreateCommand( MC_REQUEST_ADD_HASHMAP, GetMatchServerUID() );
	if( 0 != pCmd )
	{
		if( !pCmd->AddParameter(new MCmdParamStr(strNewHashValue.c_str())) )
		{
			mlog( "MServerKeeper::OnRequestAddHashMap - add hashvalue ����." );
			delete pCmd;
			return;
		}

		Post( pCmd );
	}
}


void MServerKeeper::OnResponseAddHashMap( const MUID& uidServerMgr, const bool bRes )
{
	if( GetMatchServerUID() == uidServerMgr )
	{
		MCommand* pCmd = CreateCommand( MC_RESPONSE_KEEPER_ADD_HASHMAP, GetKeeperMgrObj().GetUID() );
		if( 0 != pCmd )
		{
			if( !pCmd->AddParameter(new MCmdParamBool(bRes)) )
			{
				mlog( "MServerKeeper::OnResponseAddHashMap - ���� Ŀ�ǵ� ����." );
				delete pCmd;
				return;
			}

			Post( pCmd );
		}
	}
}