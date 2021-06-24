// ShuffleLineOrder.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <string>
#include <windows.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// [[SHUFFLE_LINE]] tag �� ���·� ǥ���� �κ��� ã�Ƽ� ���� �ڸ��� �ٲ۴�.
// ���� �ڵ�� �Ʒ��� ����... 

/* [[SHUFFLE_LINE]] ZGame */ int m_pMyCharacter;
/* [[SHUFFLE_LINE]] ZGame */ int m_someVar;
/* [[SHUFFLE_LINE]] ZGame */ int m_barbar;

// tag <- �κ��� �̸�ǥ��. �� �ҽ����� ������ �� �� �̻��� �±׸� ����ϸ� ���� �±׳����� ���̰� �ȴ�.
// tag �յڿ� ������ �ʿ��ϰ� tag ���� ������ ���ԵǸ� �ȵȴ�.

// �� ���� �뵵:
// ZGame ��ü �����͸� ã�Ƽ� Ư�� �������� ���� m_pMyCharacter�� ��� ���� �ִ�.
// ����ϰ�, �� ĳ���� ��ü���� ������ �������� ���� HPAP module�� �� ���� ���� �����Ѵ�.
// ��ġ�� �ֱ������� �Ѵٴ� �����Ͽ�, ��ġ�� ������ ������ ��Ŀ���� �������� �ٽ� ã�ƾ� �ϴ� ���ŷο��� ���ڴ� �����̴�.
// ��� �������� �ƴ϶� MCommandParameterType�� enum ������ �ڼ��� �Ϳ��� ����� �� �ִ�.
////////////////////////////////////////////////////////////////////////////////


#define TOK_SWAP	"[[SHUFFLE_LINE]]"
#define SWAPFORMAT	TOK_SWAP##"%s"


typedef vector<string>	VecString;
typedef vector<int>		VecInt;

typedef map<string, VecInt>		MapTaggedLine;
typedef MapTaggedLine::iterator	ItorTaggedLine;

void _SwapString(string& s1, string& s2)
{
	if (&s1 == &s2) return;

	// ���� �Ű�Ⱦ�
	string temp(s1);
	s1 = s2;
	s2 = temp;
}


int _tmain(int argc, _TCHAR* argv[])
{
	FILE* fp = NULL;
	VecString vecLine;
	MapTaggedLine mapTaggedLine;

	char* szFile = argv[1];
	//char* szFile = "test.h";//todok ����׿�
	if (!szFile)
	{
		printf("����� �μ��� ��� ������ �����ϼ���.\n");
		goto TERMINATE;
	}
	fp = fopen(szFile, "rt");
	if (!fp) {
		printf("������ �� �� �����ϴ�. %s\n", szFile);
		goto TERMINATE;
	}

	// ���� ��ü�� ���ڿ� ���ۿ� �о���δ�
	char buffer[4096];
	while (1)
	{
		if (NULL == fgets(buffer, 4096, fp))
			break;

		vecLine.push_back(string(buffer));
	}

	fclose(fp);

	// ���� ��ū�� �ִ� ������ ��� ã�´�
	mapTaggedLine.clear();
	char szTag[1024];
	int numLine = (int)vecLine.size();
	size_t pos = string::npos;
	for (int i=0; i<numLine; ++i)
	{
		pos = vecLine[i].find(TOK_SWAP);
		if (pos != string::npos)
		{
			// ��ū ������������ �Ľ�
			const char* szTokFound = vecLine[i].c_str() + pos;
			if (1 != sscanf(szTokFound, SWAPFORMAT, szTag))
			{
				printf("��ū�� �߰�������. �Ľ� ����\n=> %s\n", vecLine[i].c_str());
				goto TERMINATE;
			}
			mapTaggedLine[szTag].push_back(i);	// ���� ��ȣ ����صα�
		}
	}

	if (mapTaggedLine.empty())
	{
		printf("�� ���Ͽ� ��ū�� �����...\n");
		goto TERMINATE;
	}

	// ���� �±׸� ���� ���γ��� ���´�
	srand(timeGetTime());
	for (ItorTaggedLine it=mapTaggedLine.begin(); it!=mapTaggedLine.end(); ++it)
	{
		const string& strTag = it->first;
		VecInt& vecLineIdx = it->second;
		//printf("%s\n", strTag.c_str()); //todok ����׿�

		int num = (int)vecLineIdx.size();
		if (num < 2)
			continue;

		for (int repeat=0; repeat<2; ++repeat)	// ��� �ݺ�������
		{
			// �ε��� i�� �ٰ� i�� �ƴ� ������ �ε��� k�� ���� ������ ���� �¹ٲ۴�
			for (int i=0; i<num; ++i)
			{
				int k = i;
				while (k == i)
					k = rand() % num;

				int lineIdx1 = vecLineIdx[i];
				int lineIdx2 = vecLineIdx[k];
				//printf("\t%s\n\t%s\n", vecLine[lineIdx1].c_str(), vecLine[lineIdx2].c_str()); //todok ����׿�
				_SwapString(vecLine[lineIdx1], vecLine[lineIdx2]);
			}
		}
	}

	// ������ �ٽ� ����.
	fp = fopen(szFile, "wt");
	if (!fp) {
		printf("������ �� �� �����ϴ�. %s\n", szFile);
		goto TERMINATE;
	}

	for (int i=0; i<numLine; ++i)
	{
		fputs(vecLine[i].c_str(), fp);
	}
	fclose(fp);

	printf("���� �ڸ� �ٲٱ� �Ϸ�...\n");



TERMINATE:
	printf("\n\n");
	system("pause");
	return 0;
}

