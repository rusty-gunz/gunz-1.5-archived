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

// bb 가 보이는지를 판정한다
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

		// 하나의 occlusion 에라도 가려져있으면 더이상 볼필요없다.
		if(!bVisible) 
			return false;
	}
	return true;
}

// 카메라에 따라 occlusion의 평면을 갱신한다.		
void ROcclusionList::UpdateCamera(rmatrix &matWorld,rvector &cameraPos)
{
	// TODO : matWorld 가 identity 가 아닌경우 검증이 안되어있음

	float	fDet;
	rmatrix invWorld;
	D3DXMatrixInverse(&invWorld,&fDet,&matWorld);

	// camera 의 좌표를 local로 가져온다
	rvector localCameraPos;
	D3DXVec3TransformCoord(&localCameraPos,&cameraPos,&invWorld);

	rmatrix trInvMat;
	D3DXMatrixTranspose(&trInvMat, &invWorld);

	for(ROcclusionList::iterator i=begin();i!=end();i++)
	{
		ROcclusion *poc=*i;

		bool bm_pPositive=D3DXPlaneDotCoord(&poc->plane,&localCameraPos)>0;

		// 로컬의 평면의 방정식을 월드로 가져가고 싶다. matWorld 로 변환하면되는데,
		// D3DXPlaneTransform 의 사용법이 변환행렬의 inverse transpose 매트릭스를 넘겨줘야하므로
		// tr(inv(matWorld)) 가 되므로 결국 tr(mat) 가 된다
		D3DXPlaneTransform(poc->pPlanes,poc->pPlanes,&trInvMat);

		poc->pPlanes[0] = bm_pPositive ? poc->plane : -poc->plane;
		for(int j=0;j<poc->nCount;j++)
		{
			if(bm_pPositive)
				D3DXPlaneFromPoints(poc->pPlanes+j+1,&poc->pVertices[j],&poc->pVertices[(j+1)%poc->nCount],&localCameraPos);
			else
				D3DXPlaneFromPoints(poc->pPlanes+j+1,&poc->pVertices[(j+1)%poc->nCount],&poc->pVertices[j],&localCameraPos);

			// 로컬의 평면의 방정식을 월드로 가져가고 싶다. 위와 같다
			D3DXPlaneTransform(poc->pPlanes+j+1,poc->pPlanes+j+1,&trInvMat);
		}
	}
}

_NAMESPACE_REALSPACE2_END
