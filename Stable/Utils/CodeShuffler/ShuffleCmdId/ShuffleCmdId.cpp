#include "stdafx.h"
#include <string>
#include <vector>
#include <set>
#include <windows.h>
#include <assert.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

// �� ���α׷��� Ŀ�ǵ� ID�� �����ִ� ����� ������ �ֽ��ϴ�.
// ���� ���ڷ� MSharedCommandTable.h�� �־��ָ� �Ľ��ؼ�
// Ŀ�ǵ� ID�� ��ġ�� �ʴ� ������ȣ�� �ο��մϴ�.

#define TOK_BEGIN	"[[SHUFFLE_BEGIN]]"
#define TOK_END		"[[SHUFFLE_END]]"
#define TOK_RANGE	"[[SHUFFLE_RANGE]]"
#define RANGEFORMAT	"//"##TOK_RANGE##"(%d,%d)"	//[[SHUFFLE_RANGE]](70000,79999) �̷� ������ Ŀ�ǵ�ID ���� ������ ���� �ִ�.

typedef vector<string>	VecString;
typedef vector<int>		VecId;
typedef set<int>		SetId;
typedef SetId::iterator	ItorId;

int FindToken(const char* szTok, VecString& vec)
{
	int numLine = (int)vec.size();
	size_t pos = string::npos;
	for (int i=0; i<numLine; ++i)
	{
		pos = vec[i].find(szTok);
		if (pos != string::npos)
		{
			return i;
		}
	}

	return -1;
}

// ���ڿ� �� ���� �޾Ƽ� Ŀ�ǵ� ID ���ǰ� ����ִ��� �˻��Ѵ�
bool _IsCommandString(string& str)
{
	return string::npos != str.find("#define MC_"); // �̷��� �˻��ϸ� �ּ�ó���� Ŀ�ǵ嵵 ���Ե� �� ������ �� ������ ���� �ʴ´�
}

int CountCommands(VecString& vec, int nBeginLine, int nEndLine)
{
	int numCmd = 0;
	int numLine = nEndLine - nBeginLine;
	for (int i=0; i<numLine; ++i)
	{
		if (_IsCommandString(vec[nBeginLine+i]))
			++numCmd;
	}
	return numCmd;
}

void ReplaceId(VecString& vecLine, VecId& vecId, int nBeginLine, int nEndLine)
{
	char szOldId[256];
	char szNewId[256];

	VecId::iterator it = vecId.begin();
	int numLine = nEndLine - nBeginLine;
	for (int i=0; i<numLine; ++i)
	{
		string& str = vecLine[i+nBeginLine];
		if (_IsCommandString(str))
		{
			if (it == vecId.end())
			{
				printf("���� ����: ID �Ҵ� ���ε� ���ڶ���.\n");
				__asm int 3;
			}

			int oldId = 0;
			if (1 != sscanf(str.c_str(), "%*s %*s %d", &oldId) || oldId == 0)
			{
				printf("Ŀ�ǵ尡 ���ǵ� �࿡�� ID �κ��� ã�µ� �����߽��ϴ�.(%d��)\n", i);
				__asm int 3;
			}

			sprintf(szOldId, "%d", oldId);
			sprintf(szNewId, "%d", (*it));
			size_t pos = str.find(szOldId);
			str.replace(pos, strlen(szOldId),szNewId); 

			++it;
		}
	}

	if (it != vecId.end())
	{
		printf("���� ����: ID�� ��� �Ҵ������� ���� ���� �ִ�.\n");
		__asm int 3;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	VecString vecLine;
	VecId vecId;
	SetId setId;

	char* szFile = argv[1];
	if (!szFile)
	{
		printf("����� �μ��� ��� ������ �����ϼ���.\n");
		goto TERMINATE;
	}
	FILE* fp = fopen(szFile, "rt");
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

	// SHUFFLE_BEGIN�� ã�´�
	int nBeginLine = FindToken(TOK_BEGIN, vecLine);
	if (nBeginLine == -1)
	{
		printf("%s <= ��ū�� ã�� �� �����ϴ�.\n", TOK_BEGIN);
		goto TERMINATE;
	}

	// SHUFFLE_END�� ã�´�
	int nEndLine = FindToken(TOK_END, vecLine);
	if (nEndLine == -1)
	{
		printf("%s <= ��ū�� ã�� �� �����ϴ�.\n", TOK_END);
		goto TERMINATE;
	}

	// ����
	if (!(nBeginLine < nEndLine))
	{
		printf("%s�� %s �տ� �־�� �մϴ�.\n%s:%d line\n%s:%d line\n", TOK_BEGIN, TOK_END, TOK_BEGIN, nBeginLine, TOK_END, nEndLine);
		goto TERMINATE;
	}

	// SHUFFLE_RANGE�� ã�´�
	int nRangeLine = FindToken(TOK_RANGE, vecLine);
	if (nRangeLine == -1)
	{
		printf("%s <= ��ū�� ã�� �� �����ϴ�.\n", TOK_RANGE);
		goto TERMINATE;
	}
	// SHUFFLE_RANGE �Ľ�
	int nRangeBegin, nRangeEnd;
	if (2 != sscanf(vecLine[nRangeLine].c_str(), RANGEFORMAT, &nRangeBegin, &nRangeEnd))
	{
		printf("%s �Ľ� ����\n=> %s\n=> %s�� �Ȱ��� ���¿��� �մϴ�.\n", TOK_RANGE, vecLine[nRangeLine].c_str(), RANGEFORMAT);
		goto TERMINATE;
	}

	printf("[%d,%d] �� �������� ����ID�� �������ϴ�...\n", nRangeBegin, nRangeEnd);

	// BEGIN END ������ ������ �� �پ� Ȯ���ϸ鼭 '(����)#define MC_'�� �����ϴ� ���� ������ ����
	int numCmd = CountCommands(vecLine, nBeginLine, nEndLine);

	printf("%d ���� Ŀ�ǵ忡 ����ID�� �ο��մϴ�...\n", numCmd);

	// RANGE ���̿��� ��ġ�� �ʴ� �������� ���� ������� �����س���
	srand(timeGetTime());
	setId.clear();
	for (int i=0; i<numCmd; ++i)
	{
		while (1)	// �ߺ����� ���ؾ� �ϹǷ� ������ ���� ���ڰ� ���ö����� ����
		{
			int r = rand() % (nRangeEnd - nRangeBegin + 1);
			r += nRangeBegin;
			if (setId.find(r) == setId.end())
			{
				setId.insert(r);
				break;
			}
		}
	}

	// ����
	if (setId.size() != numCmd)
	{
		printf("���� ���� �߻�. ����� �ʿ�.\n");
		goto TERMINATE;
	}
	for (ItorId it=setId.begin(); it!=setId.end(); ++it)
	{
		if (!(nRangeBegin <= (*it) && (*it) <= nRangeEnd))
		{
			printf("���� ���� �߻�. ����� �ʿ�. ���������� ���\n");
			int id = *it;
			goto TERMINATE;
		}
	}

	// set���� id�� �����߱� ������ ���� ���ĵǾ� �ִ�. �������� ����
	vecId.clear();
	while (!setId.empty())
	{
		int r = rand() % (int)setId.size();
		ItorId it = setId.begin();
		for (int i=0; i<r; ++i)
			++it;
		vecId.push_back(*it);
		setId.erase(it);
	}

	assert(vecId.size() == numCmd);

	// �� ���ο��� ID��ġ�� ã�� �� ������ replace�Ѵ�
	ReplaceId(vecLine, vecId, nBeginLine, nEndLine);

	
	// ������ �ٽ� ����.
	fp = fopen(szFile, "wt");
	if (!fp) {
		printf("������ �� �� �����ϴ�. %s\n", szFile);
		goto TERMINATE;
	}

	int numLine = (int)vecLine.size();
	for (int i=0; i<numLine; ++i)
	{
		fputs(vecLine[i].c_str(), fp);
	}
	fclose(fp);

	printf("ID ���� �Ϸ�...\n");
	

TERMINATE:
	printf("\n\n");
	system("pause");
	return 0;
}

