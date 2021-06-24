#pragma once

#include "Camera.h"



#define MICTOK_ITEM		"ITEM"

#define MICTOK_ID			"id"
#define MICTOK_TYPE			"type"
#define MICTOK_MESH_NAME	"mesh_name"
#define MICTOK_TYPE			"type"
#define MICTOK_WEAPON		"weapon"
#define MICTOK_RES_SEX		"res_sex"
#define MICTOK_SLOT			"slot"
#define MICTOK_AVATAR_HEAD_MESH_NAME	"avatar_head"
#define MICTOK_AVATAR_CHEST_MESH_NAME	"avatar_chest"

#define MICTOK_TYPE_MELEE	"melee"
#define MICTOK_TYPE_RANGE	"range"
#define MICTOK_TYPE_EQUIP	"equip"
#define MICTOK_TYPE_CUSTOM	"custom"
#define MICTOK_TYPE_TICKET	"ticket"
#define MICTOK_TYPE_AVATAR	"avatar"




// ����� ����path �����
void MakeThumbnailFilename(int id, CString& out_str);

// ���� ���õ� �������� ����Ǿ����� �����ϱ� ���� ��ü��
class IUpdateListener
{
public:
	virtual void UpdateSelection(int id) = 0;
};

class UpdateNotifier
{
	std::set<IUpdateListener*> m_listeners;

public:

	void Register(IUpdateListener* p) { m_listeners.insert(p); }
	void Unregister(IUpdateListener* p) { m_listeners.erase(p); }

	void NotifyListeners(int id)
	{
		std::set<IUpdateListener*>::iterator it;
		for (it=m_listeners.begin(); it!=m_listeners.end(); ++it)
			(*it)->UpdateSelection(id);
	}
};

UpdateNotifier* GetUpdateNotifier();


// ZItem.xml �Ľ��� ����� ��ü

class TiXmlElement;

#define SEX_MALE	0
#define SEX_FEMALE	1
#define SEX_ALL		-1

class ZItem
{
public:
	bool m_bIsCashItem;
	int m_nID;
	std::string m_strType;
	std::string m_strWeaponType;
	std::string m_strMeshName;
	std::string m_strAvatarHeadMeshName;
	std::string m_strAvatarChestMeshName;
	std::string m_strSlot;
	int m_nSex;

	// ������ ���� ���
	rvector m_vPos, m_vRot, m_vScale;
	rvector m_vPos2, m_vRot2, m_vScale2;

	// �� �����ۿ� ����� ī�޶� ����
	CameraSetting m_cameraSetting;

	ZItem()
	{
		m_bIsCashItem = false;
		m_nID = 0;
		m_nSex = -1;
		m_strSlot = "none";

		m_vPos = m_vPos2 = rvector(0,0,0);
		m_vRot = m_vRot2 = rvector(0,0,0);
		m_vScale = m_vScale2 = rvector(1,1,1);
	}
};

class ZItemList : public IUpdateListener
{
public:

	typedef std::map<int, ZItem*>	MapItem;
	typedef MapItem::iterator		ItorItem;

	MapItem m_mapItem;
/*
	typedef std::map<std::string, std::string>	MapWeaponFile;
	typedef MapWeaponFile::iterator				ItorWeaponFile;

	MapWeaponFile m_mapWeaponFile;	// zitem.xml�� mesh_name�� ���� elu���� ��θ� ���� (weapon.xml)
*/

private:
	ItorItem m_currItem;


public:
	ZItemList(void);
	~ZItemList(void);

	bool Load();

	ZItem* GetCurrZItem();
	void NextZItem();
	void PrevZItem();
	ZItem* GetZItem(int id);

	virtual void UpdateSelection(int id);

	void SaveConfigureXml();
	bool LoadConfigureXml();


private:
	bool ReadZItemXml(const char* szFileName);
	void ParseItem(TiXmlElement* pElem);
	void Clear();
};


