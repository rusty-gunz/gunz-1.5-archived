#include "stdafx.h"
//#include <sys/stat.h>
#include "MDebug.h"
#include "RMaterialList.h"

_NAMESPACE_REALSPACE2_BEGIN

RMaterialList::~RMaterialList()
{
	for(iterator i=begin();i!=end();i++)
		delete *i;
}

/*
bool RMaterialList::Save(const char *szFileName)
{
	FILE *file=fopen(szFileName,"w");
	if(!file) return false;	
	for(iterator i=begin();i!=end();i++)
	{
		RMATERIAL *pMaterial=*i;
		if(!pMaterial->Name.empty())		// 이름이 있어야 한다.
		{
			fprintf(file,"%s { \n",RTOK_HEADER);
			fprintf(file,"%s \"%s\"\n",RTOK_NAME,pMaterial->Name.c_str());
			fprintf(file,"%s %x\n",RTOK_AMBIENT,pMaterial->Ambient);
			fprintf(file,"%s %x\n",RTOK_DIFFUSE,pMaterial->Diffuse);
			fprintf(file,"%s %x\n",RTOK_SPECULAR,pMaterial->Specular);
			fprintf(file,"%s %f\n",RTOK_POWER,pMaterial->Power);
			if(!pMaterial->DiffuseMap.empty())
				fprintf(file,"%s \"%s\"\n",RTOK_DIFFUSEMAP,pMaterial->DiffuseMap.c_str());
			
			// 플래그들.
			if((pMaterial->dwFlags & RM_FLAG_ADDITIVE) !=0 )
				fprintf(file,"%s\n",RTOK_ADDITIVE);
			if((pMaterial->dwFlags & RM_FLAG_USEOPACITY) !=0 )
				fprintf(file,"%s\n",RTOK_USEOPACITY);
			if((pMaterial->dwFlags & RM_FLAG_TWOSIDED) !=0 )
				fprintf(file,"%s\n",RTOK_TWOSIDED);

			fprintf(file,"} \n");
		}
	}
	fclose(file);

	return true;
}

bool RMaterialList::Open(void *pMemory,int nSize)
{
	char *pCurrent=(char*)pMemory;
	list<string> words;

	while(pCurrent<(char*)pMemory+nSize)
	{
		int nPos=
			(*pCurrent=='{' || *pCurrent=='}') ? 1 : 
			*pCurrent=='\"' ? strcspn(pCurrent+1,"\"")+2 : strcspn( pCurrent, "{}\t\n\r " );
		if(nPos>0)
		{
			words.push_back(string(pCurrent,pCurrent+nPos));
			pCurrent+=nPos;
		} else pCurrent++;
	}

	list<string>::iterator i;

	i=words.begin();
	while(i!=words.end())
	{
		if(*i==RTOK_HEADER)
		{
			if(*++i=="{")
			{
				RMATERIAL *pMaterial=new RMATERIAL;
				pMaterial->dwFlags=0;
				while(i!=words.end() && *i!="}")
				{
					i++;
					if(*i==RTOK_NAME) {i++;pMaterial->Name=(*i).substr(1,(*i).length()-2);} else
					if(*i==RTOK_DIFFUSEMAP) {i++;pMaterial->DiffuseMap=(*i).substr(1,(*i).length()-2);} else
					if(*i==RTOK_AMBIENT) sscanf((*++i).c_str(),"%x",&pMaterial->Ambient); else
					if(*i==RTOK_DIFFUSE) sscanf((*++i).c_str(),"%x",&pMaterial->Diffuse); else
					if(*i==RTOK_SPECULAR) sscanf((*++i).c_str(),"%x",&pMaterial->Specular); else
					if(*i==RTOK_POWER) sscanf((*++i).c_str(),"%f",&pMaterial->Power); else
					if(*i==RTOK_ADDITIVE) {pMaterial->dwFlags|=RM_FLAG_ADDITIVE;} else
					if(*i==RTOK_USEOPACITY) {pMaterial->dwFlags|=RM_FLAG_USEOPACITY;} else
					if(*i==RTOK_TWOSIDED) {pMaterial->dwFlags|=RM_FLAG_TWOSIDED;}
				}
				if(*i=="}")
				{
					push_back(pMaterial);
					i++;
				}
				else mlog("} needed.\n");
			}
			else
			{
				mlog("{ needed.\n");
				i++;
			}
		}
		else
		{
			mlog("%s needed.\n",RTOK_HEADER);
			i++;
		}
	}
	return true;
}

bool RMaterialList::Open(const char *szFileName)
{
	struct _stat buf;
	if(_stat(szFileName,&buf)!=0)
		return false;

	FILE *file=fopen(szFileName,"rb");
	char *buffer=new char[buf.st_size];
	fread(buffer,buf.st_size,1,file);
	fclose(file);
	bool bReturn=Open((void*)buffer,buf.st_size);
	delete []buffer;
	return bReturn;
}
*/

#define READVECTOR(v,s) sscanf(s,"%f %f %f",&v.x,&v.y,&v.z)
bool RMaterialList::Open(rapidxml::xml_node<> *pElement)
{
	for (auto itor = pElement->first_node(); itor; itor = itor->next_sibling())
	{
		RMATERIAL* pMaterial = new RMATERIAL;
		pMaterial->dwFlags = 0;
		pMaterial->Name = itor->first_attribute()->value();
		rapidxml::xml_node<>* subChild = itor->first_node();
		for (auto it = subChild; it; it = it->next_sibling())
		{
			if (stricmp(it->name(), RTOK_AMBIENT) == 0)
			{
				READVECTOR(pMaterial->Ambient, it->value());
			}
			if (stricmp(it->name(), RTOK_DIFFUSE) == 0)
			{
				READVECTOR(pMaterial->Diffuse, it->value());
			}
			if (stricmp(it->name(), RTOK_SPECULAR) == 0)
			{
				READVECTOR(pMaterial->Specular, it->value());
			}
			if (stricmp(it->name(), RTOK_DIFFUSEMAP) == 0)
			{
				pMaterial->DiffuseMap = it->value();
			}
			if (stricmp(it->name(), RTOK_POWER) == 0)
			{
				sscanf(it->value(), "%f", &pMaterial->Power);
			}
			if (stricmp(it->name(), RTOK_ADDITIVE) == 0)
				pMaterial->dwFlags |= RM_FLAG_ADDITIVE;
			if (stricmp(it->name(), RTOK_USEOPACITY) == 0)
				pMaterial->dwFlags |= RM_FLAG_USEOPACITY;
			if (stricmp(it->name(), RTOK_TWOSIDED) == 0)
				pMaterial->dwFlags |= RM_FLAG_TWOSIDED;
			if (stricmp(it->name(), RTOK_USEALPHATEST) == 0)
				pMaterial->dwFlags |= RM_FLAG_USEALPHATEST;
		}
		push_back(pMaterial);

	}
	return true;
}

bool RMaterialList::Save(rapidxml::xml_node<> *pElement, rapidxml::xml_document<>& doc)
{
	rapidxml::xml_node<>* rootNode = doc.allocate_node(rapidxml::node_element, RTOK_MATERIALLIST);

	for (auto i = begin(); i != end(); ++i)
	{
		RMATERIAL *pMaterial = *i;
		char buffer[256];

		rapidxml::xml_node<>*  parentNode = doc.allocate_node(rapidxml::node_element, RTOK_MATERIAL);
		parentNode->append_attribute(doc.allocate_attribute(RTOK_NAME, pMaterial->Name.c_str()));

		rapidxml::xml_node<>* childNode = doc.allocate_node(rapidxml::node_element, RTOK_DIFFUSE, doc.allocate_string(Format(buffer, pMaterial->Diffuse)));
		parentNode->insert_node(0, childNode);

		childNode = doc.allocate_node(rapidxml::node_element, RTOK_AMBIENT, doc.allocate_string(Format(buffer, pMaterial->Ambient)));
		parentNode->insert_node(0, childNode);

		childNode = doc.allocate_node(rapidxml::node_element, RTOK_SPECULAR, doc.allocate_string(Format(buffer, pMaterial->Specular)));
		parentNode->insert_node(0, childNode);

		childNode = doc.allocate_node(rapidxml::node_element, RTOK_DIFFUSEMAP, doc.allocate_string(pMaterial->DiffuseMap.c_str()));
		parentNode->insert_node(0, childNode);

		if ((pMaterial->dwFlags & RM_FLAG_ADDITIVE) != 0)
		{
			childNode = doc.allocate_node(rapidxml::node_element, RTOK_ADDITIVE);
			parentNode->insert_node(0, childNode);
		}
		if ((pMaterial->dwFlags & RM_FLAG_TWOSIDED) != 0)
		{
			childNode = doc.allocate_node(rapidxml::node_element, RTOK_TWOSIDED);
			parentNode->insert_node(0, childNode);
		}
		if ((pMaterial->dwFlags & RM_FLAG_USEOPACITY) != 0)
		{
			childNode = doc.allocate_node(rapidxml::node_element, RTOK_USEOPACITY);
			parentNode->insert_node(0, childNode);
		}
		if ((pMaterial->dwFlags & RM_FLAG_USEALPHATEST) != 0)
		{
			childNode = doc.allocate_node(rapidxml::node_element, RTOK_USEALPHATEST);
			parentNode->insert_node(0, childNode);
		}
		rootNode->insert_node(0, parentNode);

	}
	pElement->insert_node(0, rootNode);

	return true;
}

_NAMESPACE_REALSPACE2_END
