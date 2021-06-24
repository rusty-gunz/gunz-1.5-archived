#include "stdafx.h"
#include "RLightList.h"
#include "RToken.h"

_NAMESPACE_REALSPACE2_BEGIN

RLightList::~RLightList()
{
	for(iterator i=begin();i!=end();i++)
		delete *i;
}

#define READVECTOR(v,s) sscanf(s,"%f %f %f",&v.x,&v.y,&v.z)


bool RLightList::Open(rapidxml::xml_node<> *pElement)
{
	for (auto itor = pElement->first_node(); itor; itor = itor->next_sibling())
	{
		RLIGHT *plight = new RLIGHT;
		plight->Name = itor->first_attribute()->value();
		plight->dwFlags = 0;
		rapidxml::xml_node<>* subChild = itor->first_node();
		for (auto it = subChild; it; it = it->next_sibling())
		{
			if (stricmp(it->name(), RTOK_POSITION) == 0)
			{
				READVECTOR(plight->Position, it->value());
			}
			if (stricmp(it->name(), RTOK_COLOR) == 0)
			{
				READVECTOR(plight->Color, it->value());
			}
			if (stricmp(it->name(), RTOK_INTENSITY) == 0)
			{
				plight->fIntensity = atof(it->value());
			}
			if (stricmp(it->name(), RTOK_ATTNSTART) == 0)
			{
				plight->fAttnStart = atof(it->value());
			}
			if (stricmp(it->name(), RTOK_ATTNEND) == 0)
			{
				plight->fAttnEnd = atof(it->value());
			}
			if (stricmp(it->name(), RTOK_CASTSHADOW) == 0)
			{
				plight->dwFlags |= RM_FLAG_CASTSHADOW;
			}
		}
		push_back(plight);
	}
	return true;
	return true;
}

bool RLightList::Save(rapidxml::xml_node<>* pElement, rapidxml::xml_document<>& doc)
{
	rapidxml::xml_node<>* rootNode = doc.allocate_node(rapidxml::node_element, RTOK_LIGHTLIST);
	for (auto i = begin(); i != end(); ++i)
	{
		RLIGHT *plight = *i;
		char buffer[256];

		rapidxml::xml_node<>*  parentNode = doc.allocate_node(rapidxml::node_element, RTOK_LIGHT);
		parentNode->append_attribute(doc.allocate_attribute( RTOK_NAME, doc.allocate_string(plight->Name.c_str())));


		rapidxml::xml_node<>* childNode = doc.allocate_node(rapidxml::node_element, RTOK_POSITION, doc.allocate_string(Format(buffer, plight->Position)));
		parentNode->insert_node(0, childNode);

		childNode = doc.allocate_node(rapidxml::node_element, RTOK_COLOR, doc.allocate_string(Format(buffer, plight->Color)));
		parentNode->insert_node(0, childNode);

		childNode = doc.allocate_node(rapidxml::node_element, RTOK_INTENSITY, doc.allocate_string(Format(buffer, plight->fIntensity)));
		parentNode->insert_node(0, childNode);

		childNode = doc.allocate_node(rapidxml::node_element, RTOK_ATTNSTART, doc.allocate_string(Format(buffer, plight->fAttnStart)));
		parentNode->insert_node(0, childNode);

		childNode = doc.allocate_node(rapidxml::node_element, RTOK_ATTNEND, doc.allocate_string(Format(buffer, plight->fAttnEnd)));
		parentNode->insert_node(0, childNode);

		if ((plight->dwFlags & RM_FLAG_CASTSHADOW) != 0) {
			childNode = doc.allocate_node(rapidxml::node_element, RTOK_CASTSHADOW);
			parentNode->insert_node(0, childNode);
		}
		rootNode->insert_node(0, parentNode);

	}
	pElement->insert_node(0, rootNode);

	return true;
}

_NAMESPACE_REALSPACE2_END
