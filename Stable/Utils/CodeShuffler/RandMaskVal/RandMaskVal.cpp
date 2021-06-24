// RandMaskVal.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <vector>
#include <windows.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

// MMemoryProxy.cpp�� 
// #define PTR_OFFSET 0x06C4BAF8
// ���� ����ũ ���� �����ϱ� ���� ������ �ִ� ������ ���α׷�

typedef vector<string>	VecString;


int _tmain(int argc, _TCHAR* argv[])
{
	FILE* fp = NULL;
	VecString vecLine;

	char* szFile = argv[1];
	//szFile = "test.h";//todok ����׿�
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

	// ����ũ�� �������� ã�´�
	srand(timeGetTime());
	int numLine = (int)vecLine.size();
	for (int i=0; i<numLine; ++i)
	{
		if (string::npos != vecLine[i].find("#define PTR_OFFSET"))
		{
			// ������ ���� �����
			// (�ʹ� ū ���� �� ��ü�� ����Ʈ ������ �Ǳ� ������ 
			// �ϴ� ����ũ ���� �˾Ƴ��� ���������� �߿��� ������ ã�Ⱑ ������ ������ ����� ..)
			int r = rand() % 0xFF00;
			r += 0xFF;

			char sz[4096];
			sprintf(sz, "#define PTR_OFFSET 0x%X\n", r);
			vecLine[i] = sz;
			break;
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

	printf("���� ����ũ �� �Ϸ�...\n");


TERMINATE:
	printf("\n\n");
	system("pause");

	return 0;
}

