#pragma once


#pragma warning(disable:4786)

#include <MUID.h>
#include <MServer.h>
#include "MKeeperClient.h"
// #include "ServerKeeperConst.h"

#include <list>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

#include "MPatchCheckMap.h"
#include "MMatchGlobal.h"


class MCommand;
class MCommandManager;
class MCommObject;
class MMatchScheduleMgr;

#define KEEPERSERVER_UID	MUID(0, 3)	///< KEEPERSERVER_UID�ǰ��� UID(�Һ�)
// #define KEEPER_PORT			7779 // configure���Ϸ� �̵�.

static const char* CONFIG_SAVE_FILE = "config_save.txt";

typedef void(WORK_CALLBACK)();


#define TIME_RELAUNCH			30000	// 30��


#define SERVERITEM_STRING_LEN	64
class MServerItem {
public:
	enum SERVERSTATUS {
		SERVERSTATUS_STOP,
		SERVERSTATUS_START
	};

protected:
	int				m_nSlotID;
	bool			m_bVitalCheck;
	SERVERSTATUS	m_ServerStatus;
	unsigned long	m_tmLastStatusChanged;
	char			m_szServerType[SERVERITEM_STRING_LEN];
	char			m_szServerName[SERVERITEM_STRING_LEN];
	char			m_szServerPath[_MAX_DIR];

public:
	MServerItem(int nSlotID, bool bVital, const char* pszType, const char* pszName, const char* pszPath) {
		m_nSlotID = nSlotID;
		m_bVitalCheck = bVital;
		m_ServerStatus = SERVERSTATUS_STOP;
		m_tmLastStatusChanged = 0;
		strcpy(m_szServerType, pszType);
		strcpy(m_szServerName, pszName);
		strcpy(m_szServerPath, pszPath);
	}
	virtual ~MServerItem()			{}
	int GetSlotID()					{ return m_nSlotID; }
	bool GetVitalCheck()			{ return m_bVitalCheck; }
	void SetVitalCheck(bool bCheck)	{ m_bVitalCheck = bCheck; }
	SERVERSTATUS GetStatus()		{ return m_ServerStatus; }
	const string GetStatusToString() {
		return(m_ServerStatus==SERVERSTATUS_START ? string("Start") : string("Stop")); 
	}

	void SetStatus(SERVERSTATUS nStatus) { 
		if (m_ServerStatus == nStatus) return;

		m_ServerStatus = nStatus; 
		m_tmLastStatusChanged = timeGetTime();
	}
	unsigned long GetTimeLastStatusChanged()	{ return m_tmLastStatusChanged; }
	const char* GetServerType()	{ return m_szServerType; }
	const char* GetServerName()	{ return m_szServerName; }
	const char* GetServerPath()	{ return m_szServerPath; }
};

class MServerItemList : public list<MServerItem*> {
public:
	MServerItemList()			{}
	virtual ~MServerItemList()	{}

	void Add(MServerItem* pItem) { push_back(pItem); }
	void Remove(MServerItem* pItem, MServerItemList::iterator* itorOut) {
		MServerItemList::iterator i = find(begin(), end(), pItem);
		if (i != end()) {
			MServerItemList::iterator itorTmp = erase(i);
			if (itorOut)
				*itorOut = itorTmp;
		}
	}
};

// Keeper�� ������ �Ǵ� Keeper Manage.
class MKeeperMgrObj// : public MObject
{
public :
	MKeeperMgrObj() : m_bConnect( false ), m_bServerRun( false )
	{
	}

	~MKeeperMgrObj()
	{
	}

	bool isConnected() { return (m_bConnect && m_UID.IsValid()); }
	bool isServerRun() { return m_bServerRun; }

	MUID GetUID() { return m_UID; }

	void SetConnection( bool bState )	{ m_bConnect = bState; }
	void SetUID( const MUID& uid )		{ m_UID = uid; }

private :
	// ���� �׽�Ʈ�� ȯ�溯���� �߰���.
	bool m_bConnect;
	bool m_bServerRun;
	MUID m_UID;
};



typedef map< COLUMN_ID, CONFIG_STATE >	ConfigStateMap;
typedef vector< SERVER_ERR_STATE >		ServerStateVec;

class MServerKeeper : public MServer {
protected:	// MServer related
	MUID				m_uidNextAlloc;
	MKeeperClientMap	m_KeeperClientMap;

protected:
	MServerItemList		m_ServerItemList;

protected :
	// Updater ����.
	MKeeperMgrObj		m_KeeperMgrObj;		// Keeper�� Keeper Manager���ῡ ���.
	DWORD				m_dwRecvPingTime;
	bool				m_bIsSendPing;		// KeeperManager�� ���� ���´��� ���� ����.

	MUID				m_uidMatchServer;
	MUID				m_uidRealKeeperUID;	// MatchServer�� ����� UID�� ���⿡ ����. m_This�� 0, 3�� ���. 
											//  Keeper Maanger�� m_This�� ������ �ֱ⿡ �̷��� ��.

	CONNECTION_STATE	m_ConnectionState;
		
	CRITICAL_SECTION	m_csServerState;

	DWORD				m_dwStartCheckServerHearbeat;

	bool				m_bIsConnectMatchServer;

	MPatchCheckMap		m_PatchChkMap;		// ���� ���� ��Ұ� ��� true�� �Ǿ� Patch�� �����Ҽ� ����. Patch���� Job���� �̸� �����ؾ���.
	ConfigStateMap		m_ConfigStateMap;
	ServerStateVec		m_ServerState;

	MMatchScheduleMgr*	m_pScheduler;

	string m_strServerResVer;
	string m_strServerLastMod;
	string m_strAgentLastMod;
	string m_strKeeperLastMod;
	
	// WORK_CALLBACK*		m_fnWorkThread;

protected:	// MServer related
	/// ���ο� UID ����
	virtual MUID UseUID(void);
	/// Ŭ���̾�Ʈ ����
	int ClientAdd(const MUID& uid);
	/// Ŭ���̾�Ʈ ����
	int ClientRemove(const MUID& uid, MKeeperClientMap::iterator* pNextItor);
	/// UID�� ������Ʈ ����
	MKeeperClient* GetClient(const MUID& uid);
	/// CommUID�� ������Ʈ ����
	MKeeperClient* GetPlayerByCommUID(const MUID& uid);

	/// ����� Ŀ�ǵ� ���
	virtual void OnRegisterCommand(MCommandManager* pCommandManager);
	/// ����� Ŀ�ǵ� ó��
	virtual bool OnCommand(MCommand* pCommand);
	/// ����� ����
	virtual void OnRun(void);
	/// Ŀ�ؼ��� �޾Ƶ��� ���
	//virtual int OnAccept(MCommObject* pCommOBj);
	/// Ŀ�ؼ��� �̷���� ���
	virtual int OnConnected(MUID* pTargetUID, MUID* pAllocUID, unsigned int nTimeStamp, MCommObject* pCommObj);
	virtual void OnLocalLogin(const MUID& uidComm);
	virtual void SendCommand( MCommand* pCommand );

public:		// MServer related
	/// �ʱ�ȭ
	bool Create();
	/// ����
	void Destroy(void);
	/// MatchServer�� �����Ѵ�.
	void ConnectToItem(char* pszAddr, int nPort);
	/// MatchServer�� ������ �����Ѵ�.
	void DisconnectFromItem();

	void	SendPingToPatchInterface();
	DWORD	GetKeeperMgrPingElapseTime();
	
	bool	isKeeperMgrObjLive() { return MAX_ELAPSE_RESPONSE_REQUEST_HEARBEAT > GetKeeperMgrPingElapseTime(); }
	
public:
	MServerKeeper();
	virtual ~MServerKeeper();

	bool LoadFromXml(const char* pszFileName);

	MServerItemList* GetServerItemList()		{ return &m_ServerItemList; }
	void AddItem(MServerItem* pItem)			{ m_ServerItemList.Add(pItem); }
	MServerItem* FindServerItemBySlotID(int nSlotID);
	MUID GetMatchServerUID() { return m_uidMatchServer; }
	void SetMatchServerUID( MUID& uidMatchServer ) { m_uidMatchServer = uidMatchServer; }

	bool StartServer(MServerItem* pServerItem);
	bool StopServer(MServerItem* pServerItem);
	bool UpdateServer(MServerItem* pServerItem);

public :
	const CONNECTION_STATE	GetConnectionState()	{ return m_ConnectionState; }
	MPatchCheckMap&		GetPatchCheckMap()	{ return m_PatchChkMap; }
	MKeeperMgrObj&		GetKeeperMgrObj()	{ return m_KeeperMgrObj; }

	void AddtionalCheckConfigState( const COLUMN_ID nColumnID, const CONFIG_STATE nConfigState );

	void InitConfigState();
	void InitServerState();

	bool IsConnectionState( const CONNECTION_STATE nState ) { return nState == GetConnectionState(); }
	bool IsStopServerHeartbeat() { return MAX_ELAPSE_RESPONSE_REQUEST_HEARBEAT < (timeGetTime() - m_dwStartCheckServerHearbeat); } //1�и���.

	bool IsConnectMatchServer() { return m_bIsConnectMatchServer; }
	bool IsConnectKeeperManager() { return m_KeeperMgrObj.isConnected(); }
	bool IsOkServerStart();

	bool ConnectMatchServer();
	void DisconnectMatchServer();
	bool GetServerStatus();

	/// 
	bool RequestConnectServer();
	void OnRequestMatchServerStatus();
	void RequestServerHearbeat();

	const SERVER_ERR_STATE GetServerErrState();

private :
	MCommObject* GetObject( const MUID& uidObj );

	void SetConnectionState( const CONNECTION_STATE nState );
	void SetKeeperMgrPingState( const bool bIsSent ) { m_bIsSendPing = bIsSent; }

	const bool IsKeeperMgrPingSend() const { return m_bIsSendPing; }

	bool IsKeeperMgrConnectionValid( const MUID& uidKeeperMgr );

	void UpdateServerHeartbeatTime( const DWORD dwTime = timeGetTime() );
	void DisconnectKeeperMgr();

	void OnCheckPing( MCommand* pCommand );
	void onKeeperManagerConnect( MUID& CommUID );

	/// KeeperManager -> Keeper �������� ��û�ߴ� Ŀ�ǵ� ó��.(����)
	void OnRequestServerState( const MUID& uidKeeperMgr );
	void OnResponseConnectionState();
	void OnRequestRefreshServer( const MUID& uidKeeperMgr );
	void OnResponseRefreshServer();
	void OnRequestLastJobState( const MUID& uidKeeperMgr );
	void OnResponseLastJobState();
	void OnResponseConfigState();
	void OnRequestWriteClientCRC( const MUID& uidKeeperMgr, const DWORD dwClientCRC );
	void OnResponseWriteClientCRC( const MUID& uidKeeperMgr, const bool bResult );

	void OnResponseSetOneConfig( const COLUMN_ID nColumnID, const CONFIG_STATE nConfigState );
	void OnRequestKeeperMgrAnnounce( const char* pszAnnounce );
	void OnRequestResetPatch( const MUID& uidKeeperMgr );
	void OnResponseResetPatch();
	void OnRequestDisconnectServer( const MUID& uidKeeperMgr );
	void OnResponseDisconnectServer();
	void OnRequestRebootWindows( const MUID& uidKeeperMgr );
	void OnResponseRebootWindows();
	void OnResponseServerAndAgentState();
	void OnRequestReloadServerConfig( const MUID& uidKeeperMgr, const string& strFileList );
	void OnRequestAddHashMap( const MUID& uidKeeperMgr, const string& strNewHashValue );
	void OnResponseAddHashMap( const MUID& uidServerMgr, const bool bRes );
	
	/// KeeperManager -> Keeper �������� ��û�ߴ� Ŀ�ǵ� ó��.(MatchServer)
	void OnRequestDownloadServerPatchFile( const MUID& uidKeeperMgr );
	void OnResponseDownloadServerPatchFile();
	void OnRequestPrepareServerPatch( const MUID& uidKeeperMgr );
	void OnResponsePrepareServerPatch();
	void OnRequestStartServer( const MUID& uidKeeperMgr );
	void OnResponseStartServer();
	void OnRequestStopServer( const MUID& uidKeeperMgr );
	void OnResponseStopServer();
	void OnRequestServerPatch( const MUID& uidKeeperMgr );
	void OnResponseServerPatch();
	
	/// KeeperManager -> Keeper �������� ��û�ߴ� Ŀ�ǵ� ó��.(AgentServer)
	void OnRequestStopAgent( const MUID& uidKeeperMgr );
	void OnResponseStopAgent();
	void OnRequestStartAgent( const MUID& uidKeeperMgr );
	void OnResponseStartAgent();
	void OnRequestDownloadAgentPatchFile( const MUID& uidKeeperMgr );
	void OnResponseDownloadAgentPatchFile();
	void OnRequestPrepareAgentPatch( const MUID& uidKeeperMgr );
	void OnResponsePrepareAgentPatch();
	void OnRequestAgentPatch( const MUID& uidKeeperMgr );
	void OnResponseAgentPatch();
	
	/// Keeper -> MatchServer �������� ��û�ߴ� Ŀ�ǵ� ó��.
	void OnResponseConnectMacthServer( const MUID& uidMy );
	void OnResponseMatchServerStatus( const SERVER_ERR_STATE bIsOpenDB, const string& strServerResVer, const unsigned char nAgentCount );
	void OnResponseServerHeartbeat( const MUID& uidSender );

	/// Keeper Manager -> Keeper -> MatchServer
	void OnRequestKeeperConnectMatchServer( const MUID& uidKeeperMgr );
	void OnResponseKeeperConnectMatchServer( const MUID& uidMatchServer, const MUID& uidAlloc );
	void OnRequestStopServerWithAnnounce( const MUID& uidKeeperMgr );
	void OnResponseStopServerWithAnnounce( const MUID& uidMatchServer );
	void OnRequestKeeperManagerSchedule( const MUID& uidKeeperMgr, 
										 const int nType, 
										 const int nYear, 
										 const int nMonth, 
										 const int nDay, 
										 const int nHour, 
										 const int nMin,
										 const int nCount,
										 const int nCommand,
										 const char* pszAnnounce );
	void OnResponseKeeperManagerSchedule( const MUID& uidServer, const int nCommandType, const bool bResult );
	void OnRequestStartServerSchedule();

public : // �ܺο����� �ʿ��ؼ� �Ű� ��...
	void OnRequestSetOneConfig( const COLUMN_ID nColumnID, const CONFIG_STATE nConfigState );
	void OnRequestConfigState( const MUID& uidKeeperMgr );
	void OnRequestServerAndAgentState( const MUID& uidKeeperMgr );	

	void RouteToKeeperMgrServerAndAgentState();

	void StartServer();
	void StopServer();
	void StartAgent();
	void StopAgent();
	bool FindServer();
	bool FindAgent();

private :
	void CheckElapseRequestServerHearbeat();
	void AddConfigState( const COLUMN_ID nColumnID, const CONFIG_STATE nConfigState );
	const CONFIG_STATE GetConfigState( const COLUMN_ID nColumnID );
	void SetConfig( const  COLUMN_ID nColumnID, const CONFIG_STATE nConfigState );
	void SaveConfig();
	void LoadConfig();

	const string	GetServerResVer();
	const string	GetServerLastMod();
	const string	GetAgentLastMod();
	const string	GetKeeperLastMod();
	const string	GetFileLastMod( const string& strFile );
	const ULONGLONG GetServerFileSize();
	const ULONGLONG GetAgentFileSize();
	const ULONGLONG GetKeeperFileSize();
	const ULONGLONG GetFileSize( const string& strFile );

	bool CreateServerDownloadWorkThread();
	bool CreateServerPreparePatchWorkThread();
	bool CreateServerPatchWorkThread();
	bool CreateAgentDownloadWorkThread();
	bool CreateAgentPreparePatchWorkThread();
	bool CreateAgentPatchWorkThread();

	static DWORD WINAPI ServerDownloadWorkThread( void* pWorkContext );
	static DWORD WINAPI ServerPreparePatchWorkThread( void* pWorkContext );
	static DWORD WINAPI ServerPatchWorkThread( void* pWorkContext );
	static DWORD WINAPI AgentDownloadWorkThread( void* pWorkContext );
	static DWORD WINAPI AgentPreparePatchWorkThread( void* pWorkContext );
	static DWORD WINAPI AgentPatchWorkThread( void* pWorkContext );

	virtual int OnAccept(MCommObject* pCommObj);
	virtual void OnNetClear(const MUID& CommUID);
};
