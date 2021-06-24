#include "stdafx.h"
#include "ROcclusionList.h"
#include "RToken.h"
#include "RealSpace2.h"

_NAMESPACE_REALSPACE2_BEGIN

ROcclusion::ROcclusion()
{
	nCount=0;
	pVertices=NULL;
	pPlanes=NULL;
}

ROcclusion::~ROcclusion()
{ 
	SAFE_DELETE(pVertices); 
	SAFE_DELETE(pPlanes);
}

ROcclusionList::~ROcclusionList()
{
	for(iterator i=begin();i!=end();i++)
		delete *i;
}

#define READVECTOR(v,s) sscanf(s,"%f %f %f",&v.x,&v.y,&v.z)


bool ROcclusionList::Open(rapidxml::xml_node<>* pElement)
{
	for (auto itor = pElement->first_node(); itor; itor = itor->next_sibling())
	{
		ROcclusion *poc = new ROcclusion;
		poc->Name = itor->first_attribute()->value();
		rapidxml::xml_node<>* childNode = itor->first_node();
		list<rvector> winding;
		for (auto it = childNode; it; it = it->next_sibling())
		{
			if (stricmp(it->name(), RTOK_POSITION) == 0) {
				rvector temp;
				READVECTOR(temp, it->value());
				winding.push_back(temp);
			}
		}
		poc->nCount = winding.size();
		poc->pVertices = new rvector[poc->nCount];
		list<rvector>::iterator k = winding.begin();
		for (int j = 0; j < poc->nCount; j++)
		{
			poc->pVertices[j] = *k;
			k++;
		}

		push_back(poc);
	}
	return true;
}

bool ROcclusionList::Save(rapidxml::xml_node<>* pElement,rapidxml::xml_document<>& doc)
{
	rapidxml::xml_node<>* rootNode = doc.allocate_node(rapidxml::node_element, RTOK_OCCLUSIONLIST);
	for (auto i = begin(); i != end(); ++i)
	{
		ROcclusion *poc = *i;
		char buffer[256];

		rapidxml::xml_node<>* parentNode = doc.allocate_node(rapidxml::node_element, RTOK_OCCLUSION);
		parentNode->append_attribute(doc.allocate_attribute(RTOK_NAME, doc.allocate_string(poc->Name.c_str())));

		for (int j = 0; j<poc->nCount; j++)
		{

			rapidxml::xml_node<>* childNode = doc.allocate_node(rapidxml::node_element, RTOK_POSITION, doc.allocate_string(Format(buffer, poc->pVertices[j])));
			parentNode->insert_node(0, childNode);
		}
		rootNode->insert_node(0, parentNode);
	}
	pElement->insert_node(0, rootNode);


	return true;
}

// bb �� ���̴����� �����Ѵ�
bool ROcclusionList::IsVisible(rboundingbox &bb)
{
	for(ROcclusionList::iterator i=begin();i!=end();i++)
	{
		ROcclusion *poc=*i;

		bool bVisible=false;

		for(int j=0;j<poc->nCount+1;j++)
		{
			if(isInPlane(&bb,&poc->pPlanes[j]))
			{
				bVisible=true;
				break;
			}
		}

		// �ϳ��� occlusion ���� ������������ ���̻� ���ʿ����.
		if(!bVisible) 
			return false;
	}
	return true;
}

// ī�޶� ���� occlusion�� ����� �����Ѵ�.		
void ROcclusionList::UpdateCamera(rmatrix &matWorld,rvector &cameraPos)
{
	// TODO : matWorld �� identity �� �ƴѰ�� ������ �ȵǾ�����

	float	fDet;
	rmatrix invWorld;
	D3DXMatrixInverse(&invWorld,&fDet,&matWorld);

	// camera �� ��ǥ�� local�� �����´�
	rvector localCameraPos;
	D3DXVec3TransformCoord(&localCameraPos,&cameraPos,&invWorld);

	rmatrix trInvMat;
	D3DXMatrixTranspose(&trInvMat, &invWorld);

	for(ROcclusionList::iterator i=begin();i!=end();i++)
	{
		ROcclusion *poc=*i;

		bool bm_pPositive=D3DXPlaneDotCoord(&poc->plane,&localCameraPos)>0;

		// ������ ����� �������� ����� �������� �ʹ�. matWorld �� ��ȯ�ϸ�Ǵµ�,
		// D3DXPlaneTransform �� ������ ��ȯ����� inverse transpose ��Ʈ������ �Ѱ�����ϹǷ�
		// tr(inv(matWorld)) �� �ǹǷ� �ᱹ tr(mat) �� �ȴ�
		D3DXPlaneTransform(poc->pPlanes,poc->pPlanes,&trInvMat);

		poc->pPlanes[0] = bm_pPositive ? poc->plane : -poc->plane;
		for(int j=0;j<poc->nCount;j++)
		{
			if(bm_pPositive)
				D3DXPlaneFromPoints(poc->pPlanes+j+1,&poc->pVertices[j],&poc->pVertices[(j+1)%poc->nCount],&localCameraPos);
			else
				D3DXPlaneFromPoints(poc->pPlanes+j+1,&poc->pVertices[(j+1)%poc->nCount],&poc->pVertices[j],&localCameraPos);

			// ������ ����� �������� ����� �������� �ʹ�. ���� ����
			D3DXPlaneTransform(poc->pPlanes+j+1,poc->pPlanes+j+1,&trInvMat);
		}
	}
}

_NAMESPACE_REALSPACE2_END
