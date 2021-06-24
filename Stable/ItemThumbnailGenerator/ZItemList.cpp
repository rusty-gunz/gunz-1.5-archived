#include "StdAfx.h"
#include ".\zitemlist.h"
#include "tinyxml\tinyxml.h"
#include "MDebug.h"

UpdateNotifier* GetUpdateNotifier()
{
	static UpdateNotifier un;
	return &un;
}

void MakeThumbnailFilename(int id, CString& out_str)
{
	out_str.Format("interface/loadable/itemicon%d.dds", id);
}

// �̰� system��ɿ� ����ҰŶ� ���丮 �����ڷ� /�� ����ϸ� �ȵ˴ϴ�
#define CONFIG_FILEPATH "itemThumbnailGenerator\\config.xml"
#define CONFIG_BACKUP_FILEPATH "itemThumbnailGenerator\\config_bak.xml"

// �ظ��ϸ� cml�� �ִ� xml�ڵ�� �ε��Ϸ� �ߴµ� ��ũ���� �峭�ƴմϴ� �ذ��� ���� ���� ����ּ���
// �׷��� tinyxml�� �߽��ϴ�.


ZItemList::ZItemList(void)
{
	// ó�� ����� �� ���� ����xml�� ����صΰ� �����Ѵ�. ����� ���� ���鶧���� xml�� �Ź� ����Ǳ� ������..
	CString strCopy;
	strCopy.Format("copy %s %s /y", CONFIG_FILEPATH, CONFIG_BACKUP_FILEPATH);

	system(LPCTSTR(strCopy));

	GetUpdateNotifier()->Register(this);
}

ZItemList::~ZItemList(void)
{
	Clear();
}

void ZItemList::Clear()
{
	for (ItorItem it=m_mapItem.begin(); it!=m_mapItem.end(); ++it)
		delete it->second;
	m_mapItem.clear();

	m_currItem = m_mapItem.end();
}

bool ZItemList::Load()
{
	Clear();
	if (!ReadZItemXml("system/zitem.xml"))
		return false;
	if (!ReadZItemXml("system/zitem_locale.xml"))
		return false;
	return true;
}

bool ZItemList::ReadZItemXml(const char* szFileName)
{
	TiXmlDocument doc(szFileName);
	if (!doc.LoadFile())
		return false;

	TiXmlElement* pRootElem = doc.RootElement();
	if (!pRootElem) 
		return false;

	TiXmlElement* pElem;
	for (pElem=pRootElem->FirstChildElement(MICTOK_ITEM); pElem; pElem=pElem->NextSiblingElement(MICTOK_ITEM))
	{
		ParseItem(pElem);
	}

	m_currItem = m_mapItem.end();

	// ������ �����ϴ� �������� �Ǻҷ� �´�.
	LoadConfigureXml();

	//ĳ���͸޽� �׽�Ʈ��
	//m_currItem = m_mapItem.find(21001);

	return true;
}

void ZItemList::ParseItem(TiXmlElement* pElem)
{
	if (!pElem)
		return;

	const char* sz;
	ZItem* pNewItem = new ZItem;

	pElem->Attribute(MICTOK_ID, &pNewItem->m_nID);
	
	sz = pElem->Attribute(MICTOK_TYPE);
	if (sz) pNewItem->m_strType = sz;
	
	sz = pElem->Attribute(MICTOK_WEAPON);
	if (sz) pNewItem->m_strWeaponType = sz;
	
	sz = pElem->Attribute(MICTOK_MESH_NAME);
	if (sz) pNewItem->m_strMeshName = sz;

	sz = pElem->Attribute(MICTOK_RES_SEX);
	if (sz) {
		if (0==stricmp(sz, "m")) pNewItem->m_nSex = SEX_MALE;
		else if (0==stricmp(sz, "f"))  pNewItem->m_nSex = SEX_FEMALE;
		else if (0==stricmp(sz, "a"))  pNewItem->m_nSex = SEX_ALL;
		else
			mlog("������ ����attribute�� ���� �� �����ϴ�. \"%s\"\n", sz);
	}

	sz = pElem->Attribute(MICTOK_SLOT);
	if (sz) pNewItem->m_strSlot = sz;

	if (pNewItem->m_strType == MICTOK_TYPE_AVATAR)
	{
		sz = pElem->Attribute(MICTOK_AVATAR_HEAD_MESH_NAME);
		if (sz) pNewItem->m_strAvatarHeadMeshName = sz;

		sz = pElem->Attribute(MICTOK_AVATAR_CHEST_MESH_NAME);
		if (sz) pNewItem->m_strAvatarChestMeshName = sz;
	}

	// ���� ���� ��ȿ�� �˻�� ���߿� ���� �׸��� ����� �� ������..

	ItorItem it = m_mapItem.find(pNewItem->m_nID);
	if (it != m_mapItem.end()) {
		mlog("�ߺ��� id�Դϴ�. (%d)\n", pNewItem->m_nID);
		_ASSERT(0);
	}

	//mlog("id:%d, type:%s, wtype:%s, meshname:%s\n", pNewItem->m_nID, pNewItem->m_strType.c_str(), pNewItem->m_strWeaponType.c_str(), pNewItem->m_strMeshName.c_str());

	m_mapItem[pNewItem->m_nID] = pNewItem;
}

ZItem* ZItemList::GetCurrZItem()
{
	if (m_currItem == m_mapItem.end()) return NULL;

	return m_currItem->second;
}

void ZItemList::NextZItem()
{
	if (m_mapItem.empty())
	{
		m_currItem = m_mapItem.end();
		return;
	}

	++m_currItem;

	if (m_currItem == m_mapItem.end())
		m_currItem = m_mapItem.begin();
}

void ZItemList::PrevZItem()
{
	if (m_mapItem.empty())
	{
		m_currItem = m_mapItem.end();
		return;
	}

	if (m_currItem == m_mapItem.begin())
		m_currItem = m_mapItem.end();
	
	--m_currItem;
}

void ZItemList::UpdateSelection(int id)
{
	ItorItem it = m_mapItem.find(id);
	//if (it == m_mapItem.end())
	//	return;
	m_currItem = it;
}

ZItem* ZItemList::GetZItem(int id)
{
	ItorItem it = m_mapItem.find(id);
	if (it == m_mapItem.end()) return NULL;
	return it->second;
}


static void VectorToXmlSubElement(TiXmlElement* pElemParent, const char* szElemTag, rvector& v)
{
	TiXmlElement* pElemVector = new TiXmlElement(szElemTag);
	pElemVector->SetAttribute("x", int(v.x * 1000));
	pElemVector->SetAttribute("y", int(v.y * 1000));
	pElemVector->SetAttribute("z", int(v.z * 1000));
	pElemParent->LinkEndChild(pElemVector);
}

static void XmlSubElementToVector(TiXmlElement* pElemParent, const char* szElemTag, rvector& out)
{
	TiXmlElement* pElemVector = pElemParent->FirstChildElement(szElemTag);
	if (pElemVector)
	{
		int i;
		if (pElemVector->Attribute("x", &i)) out.x = i/1000.f;
		if (pElemVector->Attribute("y", &i)) out.y = i/1000.f;
		if (pElemVector->Attribute("z", &i)) out.z = i/1000.f;
	}
}

// �� �������� ��������� ���� �� ����� ����̳� ī�޶� ������ xml�� �����صд�
void ZItemList::SaveConfigureXml()
{
	// Make xml: <?xml ..><Hello>World</Hello>
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );
	
	TiXmlComment* pComment = new TiXmlComment("all float values in this file are saved as integer scaled * 1000.");
	doc.LinkEndChild(pComment);

	TiXmlElement* pElemMain = new TiXmlElement("ROOT");

	for (ItorItem it=m_mapItem.begin(); it!=m_mapItem.end(); ++it)
	{
		ZItem* pItem = it->second;

		TiXmlElement* pElem = new TiXmlElement("ITEMCONFIG");
		pElem->SetAttribute("id", pItem->m_nID);
		
		VectorToXmlSubElement(pElem, "Pos", pItem->m_vPos);
		VectorToXmlSubElement(pElem, "Rot", pItem->m_vRot);
		VectorToXmlSubElement(pElem, "Scale", pItem->m_vScale);

		VectorToXmlSubElement(pElem, "Pos2", pItem->m_vPos2);
		VectorToXmlSubElement(pElem, "Rot2", pItem->m_vRot2);
		VectorToXmlSubElement(pElem, "Scale2", pItem->m_vScale2);

		TiXmlElement* pElemCamera = new TiXmlElement("CAMERA");
		pElemCamera->SetAttribute("initialized", pItem->m_cameraSetting.bInitialized ? 1 : 0);
		if (pItem->m_cameraSetting.bInitialized)
		{
			pElemCamera->SetAttribute("dist", pItem->m_cameraSetting.m_fDist * 1000);
			pElemCamera->SetAttribute("rot_x", pItem->m_cameraSetting.m_fRotX * 1000);
			pElemCamera->SetAttribute("rot_y", pItem->m_cameraSetting.m_fRotY * 1000);
			VectorToXmlSubElement(pElemCamera, "At", pItem->m_cameraSetting.m_vAt);
		}
		pElem->LinkEndChild(pElemCamera);

		pElemMain->LinkEndChild(pElem);
	}

	doc.LinkEndChild(pElemMain);

	doc.SaveFile( CONFIG_FILEPATH );
}

bool ZItemList::LoadConfigureXml()
{
	TiXmlDocument doc(CONFIG_FILEPATH);
	if (!doc.LoadFile())
		return false;

	TiXmlElement* pRootElem = doc.RootElement();
	if (!pRootElem) 
		return false;

	TiXmlElement* pElem;
	for (pElem=pRootElem->FirstChildElement("ITEMCONFIG"); pElem; pElem=pElem->NextSiblingElement("ITEMCONFIG"))
	{
		int id;
		if (pElem->Attribute("id", &id))
		{
			ItorItem it = m_mapItem.find(id);
			if (it == m_mapItem.end())
			{
				mlog("�������� �д� �� : id(%d)�� ã�� �� �����ϴ�.\n", id);
				continue;
			}

			ZItem* pItem = it->second;
			XmlSubElementToVector(pElem, "Pos", pItem->m_vPos);
			XmlSubElementToVector(pElem, "Rot", pItem->m_vRot);
			XmlSubElementToVector(pElem, "Scale", pItem->m_vScale);

			XmlSubElementToVector(pElem, "Pos2", pItem->m_vPos2);
			XmlSubElementToVector(pElem, "Rot2", pItem->m_vRot2);
			XmlSubElementToVector(pElem, "Scale2", pItem->m_vScale2);

			TiXmlElement* pElemCamera = pElem->FirstChildElement("CAMERA");
			if (pElemCamera)
			{
				int i;
				pItem->m_cameraSetting.bInitialized = false;

				if (pElemCamera->Attribute("initialized", &i) && i==1)
				{
					pItem->m_cameraSetting.bInitialized = true;

					if (pElemCamera->Attribute("dist", &i)) pItem->m_cameraSetting.m_fDist = i/1000.f;
					if (pElemCamera->Attribute("rot_x", &i)) pItem->m_cameraSetting.m_fRotX = i/1000.f;
					if (pElemCamera->Attribute("rot_y", &i)) pItem->m_cameraSetting.m_fRotY = i/1000.f;
					XmlSubElementToVector(pElemCamera, "At", pItem->m_cameraSetting.m_vAt);
				}
			}
		}
	}

	return true;
}

