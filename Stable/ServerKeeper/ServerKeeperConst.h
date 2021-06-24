#ifndef _SERVER_KEEPER_CONST
#define _SERVER_KEEEPR_CONST

/// Server state
enum CONNECTION_STATE
{
	CNN_START_CHECK					= 0,
	CNN_FAIL_CONNECT,
	CNN_NOT_CONNECTED_SERVER,
	CNN_NOT_CONNECTED_KEEPER,
	CNN_FAIL_CONNECT_KEEPER,
	CNN_CONNECTING_TO_KEEPER,
	CNN_CONNECTED_SERVER,
	CNN_CONNECTING_TO_SERVER,
	CNN_CHECKING_SERVER_HEARTBEAT,

	CNN_END,
};

// for PatchInterface.
static const char* CONNECTION_STATE_LIST[] = { "START CHECK",  
											   "FAIL TO CONNECT", "NOT CONNECTED SERVER", "NOT CONNECTED KEEPER",
											   "FAIL CONNECT KEEPER", "CONNECTING TO KEEPER", "CONNECTED SERVER", "CONNECTING TO SERVER",
											   "CHECKING SERVER HEARTBEAT" };

/// job state
enum JOB_STATE
{
	JOB_NON	= 0,
	JOB_SUCCESS_CONNECT_FTP_SERVER,			JOB_FAIL_CONNECT_FTP_SERVER,
	JOB_SUCCESS_DOWNLOAD_SERVER_PATCH_FILE,	JOB_FAIL_DOWNLOAD_SERVER_PATCH_FILE,
	JOB_SUCCESS_PREPARE_SERVER_PATCH,		JOB_FAIL_PREPARE_SERVER_PATCH,
	JOB_SUCCESS_STOP_AGENT,					JOB_FAIL_STOP_AGENT,
	JOB_SUCCESS_STOP_SERVER,				JOB_FAIL_STOP_SERVER,
	JOB_SUCCESS_PATCH_SERVER,				JOB_FAIL_PATCH_SERVER,	
	JOB_SUCCESS_START_SERVER,				JOB_FAIL_START_SERVER,
	JOB_SUCCESS_START_AGENT,				JOB_FAIL_START_AGENT,
	JOB_FAIL_CREATE_SERVER_DOWNLOAD_THREAD,
	JOB_FAIL_CREATE_SERVER_PREPARE_THREAD,
	JOB_FAIL_CREATE_SERVER_PATCH_THREAD,
	JOB_DOWNLOADING_SERVER_PATCH,
	JOB_PREPARING_SERVER_PATCH,
	JOB_PATCHING_SERVER,
	JOB_SUCCESS_DOWNLOAD_AGENT_PATCH_FILE,	JOB_FAIL_DOWNLOAD_AGENT_PATCH_FILE,
	JOB_SUCCESS_PREPARE_AGENT_PATCH,		JOB_FAIL_PREPARE_AGENT_PATCH,
	JOB_SUCCESS_PATCH_AGENT,				JOB_FAIL_PATCH_AGENT,
	JOB_FAIL_CREATE_AGENT_DOWNLOAD_THREAD,
	JOB_FAIL_CREATE_AGENT_PREPARE_THREAD,
	JOB_FAIL_CREATE_AGENT_PATCH_THREAD,
	JOB_DOWNLOADING_AGENT_PATCH,
	JOB_PREPARING_AGENT_PATCH,
	JOB_PATCHING_AGENT,
	JOB_FAIL_REBOOT,
	JOB_ANNOUNCE_STOP_SERVER,
	JOB_SUCCESS_ADD_ANNOUNCE_SCHEDULE,
	JOB_FAIL_ADD_ANNOUNCE_SCHEDULE,
	JOB_SUCCESS_ADD_SERVER_STOP_SCHEDULE,
	JOB_FAIL_ADD_SERVER_STOP_SCHEDULE,
	JOB_SUCCESS_ADD_RESTART_SERVER_SCHEDULE,
	JOB_FAIL_ADD_RESTART_SERVER_SCHEDULE,
	JOB_DISABLE_SERVER_PATCH,
	JOB_DISABLE_AGENT_PATCH,
	JOB_RELOAD_SERVER_CONFIG,
	
	JOB_END,
};

// for PatchInterface.
static const char* JOB_STATE_LIST[] = { "����", 
										"FTP ���� ����",		"FTP ���� ����", 
										"S ��ġ �ޱ� ����",		"S ��ġ �ޱ� ����",
										"S ��ġ �غ� ����",		"S ��ġ �غ� ����", 
										"A ���� ����",			"A ���� ����",
										"S ���� ����",			"S ���� ����",
										"S ��ġ ����",			"S ��ġ ����", 
										"S ���� ����",			"S ���� ����",
										"A ���� ����",			"A ���� ����",
										"S ��ġ�ޱ� ������ ���� ����",
										"S ��ġ�غ� ������ ���� ����",
										"S ��ġ ������ ���� ����",
										"S ��ġ ���� �޴� ��",
										"S ��ġ �۾� �غ� ��",
										"S ��ġ ��",
										"A ��ġ �ޱ� ����",		"A ��ġ �ޱ� ����",
										"A ��ġ �غ� ����",		"A ��ġ �غ� ����",
										"A ��ġ ����",			"A ��ġ ����",
										"A ��ġ�ޱ� ������ ���� ����",
										"A ��ġ�غ� ������ ���� ����",
										"A ��ġ������ ���� ����",
										"A ��ġ �޴� ��",
										"A ��ġ �۾� �غ� ��",
										"A ��ġ ��",
										"����� ����",
										"������ ���� ����",
										"���� ������ ��� ����",
										"���� ������ ��� ����", 
										"�������� ������ ��� ����",
										"�������� ������ ��� ����",
										"��������� ������ ��� ����",
										"��������� ������ ��� ����", 
										"S ��ġ ����",
										"A ��ġ ����",
										"���� �������� ���ε�.",
										"END OF JOB" };


enum CONFIG_STATE
{
	CONFIG_ERROR = 0,
	CONFIG_NO,
	CONFIG_AUTO_START_SERVER,
	CONFIG_MANUAL_START_SERVER,
	CONFIG_AUTO_START_AGENT,
	CONFIG_MANUAL_START_AGENT,
	CONFIG_OK_DOWNLOAD,
	CONFIG_NO_DOWNLOAD,
	CONFIG_OK_PREPARE,
	CONFIG_NO_PREPARE,
	CONFIG_OK_PATCH,
	CONFIG_NO_PATCH,

	CONFIG_END,
};

static const char* CONFIG_STATE_LIST[] = { "Error",
										   "NO",
										   "�ڵ�", "����", 
										   "�ڵ�", "����", 
										   "OK", "NO", 
										   "OK", "NO", 
										   "OK", "NO" };

enum COLUMN_ID
{
	COLUMN_SERVER_START = 7,
	COLUMN_AGENT_START,
	COLUMN_DOWNLOAD,
	COLUMN_PREPARE,
	COLUMN_PATCH,

	COLUMN_END,
};

enum RUN_STATE
{
	RS_NO = 0,
	RS_RUN,
	RS_STOP,

	RS_END,
};

static const char* RUN_STATE_LIST[] = { "NO", "RUN", "STOP" };

static const char* SERVER_ERR_STATE_LIST[] = { "NO", "DB ERROR" };

#define MAX_ELAPSE_RESPONSE_REQUEST_HEARBEAT (1000 * 30)	// 10�ʿ� �ѹ��� �˻� ��.

#endif /// _SERVER_KEEPER_CONST