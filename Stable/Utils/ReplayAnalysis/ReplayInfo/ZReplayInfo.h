#ifndef _ZREPLAYINFO_H
#define _ZREPLAYINFO_H

#include "ZFile.h"
#include "HeaderFile.h"



// ���� ���÷��� ����
#define GUNZ_REC_FILE_ID		0x95b1308a

// version 4 : duel ����� ���� ���� ������ �߰��Ǿ����ϴ�.
// version 5 : duel_tournament�� ������ �߰��Ǿ����ϴ�. (MTD_CharInfo�� ������ ��ŷ��� ���� �߰�, �����ʸ�Ʈ�� ���� ���� ����)
// version 6 : ���� �����ۿ� ���������� �߰��Ǿ����ϴ�. (�Ҹ� �����ۿ�)
#define GUNZ_REC_FILE_VERSION	6
#define GUNZ_REC_FILE_EXT		"gzr"
#define MAXPLAYERCOUNT			16

class ZReplayInfo
{
private:
public:
	ZReplayInfo() {}
	~ZReplayInfo() {}

};

class ZReplayLoader
{
public:
	static unsigned int				m_nVersion;
private:
	REPLAY_STAGE_SETTING_NODE		m_StageSetting;
	int								m_nCharacterCount;
	MTD_CharInfo					m_CharInfo[MAXPLAYERCOUNT];

	bool LoadHeader(ZFile* file);
	bool LoadStageSetting(ZFile* file);
	bool LoadStageSettingEtc(ZFile* file);
	bool LoadCharInfo(ZFile* file);
	bool ZCharacter_Load(ZFile *file,int nVersion);
	bool ZItem_Load(ZFile *file, int nReplayVersion);
	char* GetGameType(MMATCH_GAMETYPE gameType);

public:
	ZReplayLoader();
	~ZReplayLoader() {}
	bool Load(const char* filename);
	bool Save(const char* filename);
};

typedef struct _DTPlayerInfo
{
	char m_szCharName[MATCHOBJECT_NAME_LENGTH];
	MUID uidPlayer;
	int m_nTP;
} DTPlayerInfo;

//////////////////////////////////////////////////////
// ���� ������ ĳ���� ���� ����ü
//////////////////////////////////////////////////////

#pragma pack(push, old)
#pragma pack(1)

struct MTD_CharInfo_v0	// ver0 ver1
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
	unsigned long int	nEquipedItemDesc[12];		// MMatchCharItemParts_v0::MMCIP_END0

	// account �� ����
	MMatchUserGradeID	nUGradeID;
};

struct MTD_CharInfo_v2	// ver2 ~ 4
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
	unsigned long int	nEquipedItemDesc[12];		// MMatchCharItemParts_v0::MMCIP_END0

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;
};

struct MTD_CharInfo_v5	// ver5
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
	unsigned long int	nEquipedItemDesc[12];		// MMatchCharItemParts_v0::MMCIP_END0

	// account �� ����
	MMatchUserGradeID	nUGradeID;

	// ClanCLID
	unsigned int		nClanCLID;

	// ������ �����ʸ�Ʈ ���
	int					nDTLastWeekGrade;	
};

struct MTD_DuelQueueInfo
{
	MUID			m_uidChampion;
	MUID			m_uidChallenger;
	MUID			m_WaitQueue[14];				// ��
	char			m_nQueueLength;
	char			m_nVictory;						// ���¼�
	bool			m_bIsRoundEnd;					// ���� �������ΰ�
};

struct MTD_DuelTournamentGameInfo
{
	MUID			uidPlayer1;					// ������ ������ ������ Player1
	MUID			uidPlayer2;					// ������ ������ ������ Player1
	int				nMatchType;					// ������ ������ MatchType(
	int				nMatchNumber;				// ������ ������ MatchNumber
	int				nRoundCount;				// ������ ������ �����
	bool			bIsRoundEnd;				// ���尡 ����Ǿ��°��� ���� Flag(�÷��̾� ��Ż�� ������..)
	char			nWaitPlayerListLength;		// ����� ����Ʈ�� Length
	byte			dummy[2];					// 4����Ʈ�� ���߱� ���� ����
	MUID			WaitPlayerList[8];			// ����ڵ��� MUID
};

#pragma pack(pop, old)



#endif