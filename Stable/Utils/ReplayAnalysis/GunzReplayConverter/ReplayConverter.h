#pragma once

#include <Windows.h>
#include <stdio.h>
#include "MUID.h"
#include "MBaseGameType.h"
#include "MMatchGlobal.h"
#include "MMatchClan.h"
#include "MMatchItem.h"

//-----------------------------------------------------------------------------
// Gunz/ZReplay.h
struct REPLAY_STAGE_SETTING_NODE 
{
	MUID				uidStage;
	char				szMapName[MAPNAME_LENGTH];	// ���̸�
	char				nMapIndex;					// ���ε���
	MMATCH_GAMETYPE		nGameType;					// ����Ÿ��
	int					nRoundMax;					// ����
	int					nLimitTime;					// ���ѽð�(1 - 1��)
	int					nLimitLevel;				// ���ѷ���
	int					nMaxPlayers;				// �ִ��ο�
	bool				bTeamKillEnabled;			// ��ų����
	bool				bTeamWinThePoint;			// ������ ����
	bool				bForcedEntryEnabled;		// ������ ���� ����
};

// ���� ���÷��� ����
#define GUNZ_REC_FILE_ID		0x95b1308a

// version 4 : duel ����� ���� ���� ������ �߰��Ǿ����ϴ�.
#define GUNZ_REC_FILE_VERSION	4
#define GUNZ_REC_FILE_EXT		"gzr"
//-----------------------------------------------------------------------------
// CSCommon/Include/MMatchObject.h
enum MMatchUserGradeID
{
	MMUG_FREE			= 0,	// ���� ����
	MMUG_REGULAR		= 1,	// ���� ����
	MMUG_STAR			= 2,	// ��Ÿ����(����¯)

	MMUG_CRIMINAL		= 100,	// ������
	MMUG_WARNING_1		= 101,	// 1�� ���
	MMUG_WARNING_2		= 102,	// 2�� ���
	MMUG_WARNING_3		= 103,	// 3�� ���
	MMUG_CHAT_LIMITED	= 104,  // ä�� ����
	MMUG_PENALTY		= 105,	// �Ⱓ ����

	MMUG_EVENTMASTER	= 252,	// �̺�Ʈ ������
	MMUG_BLOCKED		= 253,	// ��� ����
	MMUG_DEVELOPER		= 254,	// ������
	MMUG_ADMIN			= 255	// ������
};

enum MMatchSex
{
	MMS_MALE = 0,		// ����
	MMS_FEMALE = 1		// ����
};
//-----------------------------------------------------------------------------
#pragma pack(push, old)
#pragma pack(1)
// CSCommon/Include/MMatchTransDataType.h
struct MTD_DuelQueueInfo
{
	MUID			m_uidChampion;
	MUID			m_uidChallenger;
	MUID			m_WaitQueue[14];				// ��
	char			m_nQueueLength;
	char			m_nVictory;						// ���¼�
	bool			m_bIsRoundEnd;					// ���� �������ΰ�
};

struct MTD_CharInfo
{
	// ĳ���� ����
	char				szName[MATCHOBJECT_NAME_LENGTH];
	char				szClanName[CLAN_NAME_LENGTH];
	MMatchClanGrade		nClanGrade;
	unsigned short		nClanContPoint;
	char				nCharNum;
	unsigned short		nLevel;
	char				nSex;
	char				nHair;
	char				nFace;
	unsigned long int	nXP;
	int					nBP;
	float				fBonusRate;
	unsigned short		nPrize;
	unsigned short		nHP;
	unsigned short		nAP;
	unsigned short		nMaxWeight;
	unsigned short		nSafeFalls;
	unsigned short		nFR;
	unsigned short		nCR;
	unsigned short		nER;
	unsigned short		nWR;

	// ������ ����
	unsigned long int	nEquipedItemDesc[MMCIP_END];

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;
};

/// Ŭ���̾�Ʈ�� �˾ƾ��� ��Ÿ���� : AdminHide ���¸� ��������� ��ȯ & ��ȭ���Ͽ� ����
struct MTD_ExtendInfo
{
	char			nTeam;
	unsigned char	nPlayerFlags;	// �÷��̾� �Ӽ�(��ڼ����) - MTD_PlayerFlags ���
	unsigned char	nReserved1;		// ����
	unsigned char	nReserved2;
};

struct MTD_PeerListNode
{
	MUID			uidChar;
	DWORD			dwIP;
	unsigned int	nPort;
	MTD_CharInfo	CharInfo;
	MTD_ExtendInfo	ExtendInfo;
};

// ������ ���� ����
struct MTD_WorldItem
{
	unsigned short	nUID;
	unsigned short	nItemID;
	unsigned short  nItemSubType;
	short			x;
	short			y;
	short			z;
	//float			x;
	//float			y;
	//float			z;
};
//-----------------------------------------------------------------------------
// ZPost.h
// ���� �ð��������� ĳ���͵鳢�� ��� �ְ�޴� ������
struct ZPACKEDBASICINFO {
	float	fTime;
	short	posx,posy,posz;
	short	velx,vely,velz;
	short	dirx,diry,dirz;
	BYTE	upperstate;
	BYTE	lowerstate;
	BYTE	selweapon;
};

struct ZPACKEDDASHINFO {
	short	posx, posy, posz;
	short	dirx, diry, dirz;
	BYTE	seltype;
};
#pragma pack(pop, old)
//-----------------------------------------------------------------------------
// ZCharacter.h
struct ZCharacterProperty
{
	char		szName[MATCHOBJECT_NAME_LENGTH];
	char		szClanName[CLAN_NAME_LENGTH];
	MMatchSex	nSex;
	int			nHair;
	int			nFace;
	int			nLevel;
	float		fMaxHP;		// *10 �Ȱ��̴�.
	float		fMaxAP;
	int			nMoveSpeed;
	int			nWeight;
	int			nMaxWeight;
	int			nSafeFall;
	ZCharacterProperty() :	nSex(MMS_MALE),
							nHair(0),
							nFace(0),
							nLevel(1),
							fMaxHP(1000.f), 
							fMaxAP(1000.f), 
							nMoveSpeed(100), 
							nWeight(0), 
							nMaxWeight(100), 
							nSafeFall(100)
							{ 
								szName[0] = 0;
								szClanName[0] = 0;
							}
	void SetName(const char* name) { strcpy(szName, name); }
	void SetClanName(const char* name) { strcpy(szClanName, name); }
};

struct ZCharacterStatus
{
	int			nLife;
	int			nKills;
	int			nDeaths;
	int			nLoadingPercent;	// ó�� �濡 ���ö� �ε��� �� �Ǿ������� �ۼ�Ʈ 100�� �Ǹ� �ε��� �ٵȰ�
	int			nCombo;
	int			nMaxCombo;
	int			nAllKill;
	int			nExcellent;
	int			nFantastic;
	int			nHeadShot;
	int			nUnbelievable;
	int			nExp;

	ZCharacterStatus() :	
							nLife(10),
							nKills(0),
							nDeaths(0),
							nLoadingPercent(0),
							nCombo(0),
							nMaxCombo(0),
							nAllKill(0),
							nExcellent(0),
							nFantastic(0),
							nHeadShot(0),
							nUnbelievable(0),
							nExp(0)
							{  }

	void AddKills(int nAddedKills = 1) { nKills += nAddedKills; }
	void AddDeaths(int nAddedDeaths = 1) { nDeaths += nAddedDeaths;  }
	void AddExp(int _nExp=1) { nExp += _nExp; }
};
//-----------------------------------------------------------------------------
struct rvector
{
    float x;
    float y;
    float z;
};
//-----------------------------------------------------------------------------
class ZFile;
//-----------------------------------------------------------------------------
class Logger
{
public:
	Logger() : m_File(NULL) {}
	~Logger() { Close(); }

	void Init( const char* fileName ) { Close(); m_File = fopen( fileName, "w" ); }
	void Close() { if( m_File ) fclose( m_File ); }
	void Print( const char* text ) { if( m_File ) fprintf( m_File, text ); }

private:
	FILE *m_File;
};
void InitLog( const char* fileName );
void CloseLog();
void Log( const char* format, ... );
//-----------------------------------------------------------------------------
struct DIE_INFO
{
	float fTime;
	float x;
	float y;
	float z;
};
typedef vector<DIE_INFO> DieInfoList;
typedef DieInfoList::const_iterator DieInfoConstIter;
//-----------------------------------------------------------------------------
class Replay
{
public:
	Replay();
	~Replay();

	bool Load(const string& filename );
	const string& GetMapName() { return m_MapName; }
	const DieInfoList& GetDieInfoList() { return m_DieInfoList; }

private:
	bool LoadHeader( ZFile* file );
	bool LoadStageSetting( ZFile* file );
	bool LoadStageSettingEtc( ZFile* file );
	bool LoadCharInfo( ZFile* file );
	bool LoadCommandStream( ZFile* file );

private:
	typedef map<MUID, rvector> RecentPosition;
	typedef RecentPosition::const_iterator RecentPositionConstIter;

	unsigned int				m_nVersion;
	float						m_fGameTime;
	REPLAY_STAGE_SETTING_NODE	m_StageSetting;
	MTD_DuelQueueInfo			m_DuelQueueInfo;

	string						m_MapName;

	RecentPosition				m_RecentPosition;

	DieInfoList					m_DieInfoList;
};
//-----------------------------------------------------------------------------
class ReplayConverter
{
public:
	ReplayConverter();
	~ReplayConverter();

	bool Add( const string& replayFileName );
	bool SaveCSV();

private:
	typedef pair<string, Replay*> ReplayListPair;
	typedef multimap<string, Replay*> ReplayList;
	typedef ReplayList::iterator ReplayListIter;
	typedef ReplayList::const_iterator ReplayListConstIter;

	ReplayList m_ReplayList;
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------