#ifndef _HEADERFILE_H
#define _HEADERFILE_H

#define MATCHOBJECT_NAME_LENGTH			32	// ĳ���� �̸� ���� - ���� ���÷��̶����� DB�� ����� ����. ���� �߰��ϴ� ������ ����. - by SungE. 2007-03-20
#define CLAN_NAME_LENGTH				16	// Ŭ�� �̸� �ִ� ���� - �̰� ����Ǹ� �������� ������ ����Ǿ�� ��.

/// ���� Ÿ��
enum MMATCH_GAMETYPE {
	MMATCH_GAMETYPE_DEATHMATCH_SOLO		=0,			///< ���� ������ġ
	MMATCH_GAMETYPE_DEATHMATCH_TEAM		=1,			///< �� ������ġ
	MMATCH_GAMETYPE_GLADIATOR_SOLO		=2,			///< ���� �۷�������
	MMATCH_GAMETYPE_GLADIATOR_TEAM		=3,			///< �� �۷�������
	MMATCH_GAMETYPE_ASSASSINATE			=4,			///< ������(�ϻ���)
	MMATCH_GAMETYPE_TRAINING			=5,			///< ����

	MMATCH_GAMETYPE_SURVIVAL			=6,			///< �����̹�
	MMATCH_GAMETYPE_QUEST				=7,			///< ����Ʈ

	MMATCH_GAMETYPE_BERSERKER			=8,			///< ������ġ ����Ŀ
	MMATCH_GAMETYPE_DEATHMATCH_TEAM2	=9,			///< ��������ġ �ͽ�Ʈ��
	MMATCH_GAMETYPE_DUEL				=10,		///< ��� ��ġ
	MMATCH_GAMETYPE_DUELTOURNAMENT		=11,		///< ��� ��ʸ�Ʈ
/*
#ifndef _CLASSIC
	MMATCH_GAMETYPE_CLASSIC_SOLO,
	MMATCH_GAMETYPE_CLASSIC_TEAM,
#endif
*/
	MMATCH_GAMETYPE_MAX,
};

// Ŭ�� ���
enum MMatchClanGrade
{
	MCG_NONE		= 0,		// Ŭ������ �ƴ�
	MCG_MASTER		= 1,		// Ŭ�� ������
	MCG_ADMIN		= 2,		// Ŭ�� ���

	MCG_MEMBER		= 9,		// �Ϲ� Ŭ����
	MCG_END
};

/// ������
enum MMatchCharItemParts
{
	MMCIP_HEAD		= 0,
	MMCIP_CHEST		= 1,
	MMCIP_HANDS  	= 2,
	MMCIP_LEGS		= 3,
	MMCIP_FEET		= 4,
	MMCIP_FINGERL	= 5,
	MMCIP_FINGERR	= 6,
	MMCIP_MELEE		= 7,
	MMCIP_PRIMARY	= 8,
	MMCIP_SECONDARY	= 9,
	MMCIP_CUSTOM1	= 10,	
	MMCIP_CUSTOM2	= 11,
	MMCIP_AVATAR	= 12,
	MMCIP_COMMUNITY1	= 13,
	MMCIP_COMMUNITY2	= 14,
	MMCIP_LONGBUFF1	= 15,
	MMCIP_LONGBUFF2	= 16,
	MMCIP_END
};

// ��� - �̰��� ����� UserGrade���̺�� ��ũ�� �¾ƾ� �Ѵ�.
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

enum MMatchTeam
{
	MMT_ALL			= 0,
	MMT_SPECTATOR	= 1,
	MMT_RED			= 2,
	MMT_BLUE		= 3,
	MMT_END
};

enum MMatchSex
{
	MMS_MALE = 0,		// ����
	MMS_FEMALE = 1		// ����
};

struct MUID{
	unsigned long int	High;	///< High 4 Byte
	unsigned long int	Low;	///< High 4 Byte
};

struct rvector
{
	float x;
	float y;
	float z;
};




////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// ���� Ŭ���̾�Ʈ���� ���÷��� ���� ����ɶ� Ŭ������ ���Ѵٸ� 
// �Ʒ� Ŭ������ ���� ����Ǿ�� �Ѵ�.
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

struct REPLAY_STAGE_SETTING_NODE 
{
	MUID				uidStage;
	char				szMapName[MATCHOBJECT_NAME_LENGTH];	// ���̸�
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


#pragma pack(push, old)
#pragma pack(1)
// ��Ŷ�� ������ ���� ����ü�̱� ������ 1Byte�� �ڸ��� ��ŷ�� ���ش�.
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

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;

	// ������ ���� �߰�
	MUID				uidEquipedItem[MMCIP_END];
	unsigned long int	nEquipedItemCount[MMCIP_END];
};
#pragma pack(pop, old)


/// ĳ���� �Ӽ� - �� ���� ������ �ʴ´�.
struct ZCharacterProperty_Old
{
	char		szName[MATCHOBJECT_NAME_LENGTH];
	char		szClanName[CLAN_NAME_LENGTH];
	MMatchSex	nSex;
	int			nHair;
	int			nFace;
	int			nLevel;
	float		fMaxHP;
	float		fMaxAP;
	int			nMoveSpeed;
	int			nWeight;
	int			nMaxWeight;
	int			nSafeFall;
	ZCharacterProperty_Old() :	nSex(MMS_MALE),
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

/// ĳ���� ���°�
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

#endif _HEADERFILE_H