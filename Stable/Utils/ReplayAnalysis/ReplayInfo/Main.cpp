#include <iostream>
#include <Shlwapi.h>
#include <tchar.h>

#include "ZReplayInfo.h"


#define MAXFILENAME		512

void Manual()
{
	printf("ReplayInfo for GunZ the Duel\n");
	printf(" This program is created by MAIET Entertainment for solemn use of assisting \n");
	printf("GunZ GM to analyze the reported replay files. \n");
	printf("This program will create [filename].txt file with the replay file information.\n");
	printf("There are two ways to use this program.\n");
	printf("\n");
	printf("[Method 1]\n");
	printf(" 1.Copy the ReplayInfo.exe program to the folder that contains the replay files\n");
	printf(" 2.Run the program: ReplayInfo.exe and press Enter.\n");
	printf(" 3.Find the text files of all the replay files inside the folder.\n");
	printf("\n");
	printf("[Method 2]\n");
	printf(" 1.Run the program : ReplayInfo.exe\n");
	printf(" 2.Drag and drop the replay file folder over the running program��s screen.\n");
	printf(" 3.When the folder��s directory appears on the screen, press enter.\n");
	printf(" 4.Find the text files of all the replay files inside the folder.\n");
	printf("\n");
	printf("���÷��� ���� ���α׷� ��� ���\n");
	printf(" 1.���÷��� ���ϵ��� �ִ� ������ ���α׷��� ���� -> ���α׷� ���� -> �����Է�\n");
	printf(" 2.���÷��� ���ϵ��� �ִ� ������ ����� ���α׷� ȭ������ �巡�� �� �� �����Է�\n");
	printf(" 3.���� �� ������ ��� ����� ����ϼŵ� �������ϴ�. ��� �� ���α׷��� �ִ� ���� �ȿ� ���÷��� ���ϸ��� ������ �ؽ�Ʈ ������ �����˴ϴ�\n");
}
// �巡�׵� ���� �ּ� ��Ʈ�� ���
void GetFolderPath(char* filename)
{
	char c = {0};
	int c_cnt = 0;

	while( c != '\n' && (c = getchar()) != EOF) 
	{
		if(c == '\n' && c_cnt == 0)
		{	// ���� ��ũ���� �ʰ� ���÷����ִ� �������� ���� ������� ó�����ش�.
			GetModuleFileName( NULL, filename, _MAX_DIR );
			PathRemoveFileSpec( filename );
			return;
		}
		if(c == '"' || c == '\n')
			continue;
		filename[c_cnt] = c;
		c_cnt++;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ��� ����
	Manual();

	char fileFullName[512] = "0";
	char folderPath[512] = "0";
	GetFolderPath(folderPath);
	sprintf(fileFullName, "%s\\*.gzr", folderPath);

	HANDLE hSrc;
	WIN32_FIND_DATA wfd;
	hSrc = FindFirstFile(fileFullName, &wfd);		// �ش������� ù��° ������ wfd�� �ִ´�
	{
		if (hSrc == INVALID_HANDLE_VALUE)
		{
			fprintf(stderr, "Can't Find [%s].\n", folderPath);
			return 0;
		} 

		do
		{
			sprintf(fileFullName, "%s\\%s", folderPath, wfd.cFileName);

			ZReplayLoader zReplayLoader;
			zReplayLoader.Load(fileFullName);	// ���÷��� ���Ͽ��� ���� �ε�
			zReplayLoader.Save(wfd.cFileName);	// ���÷��� ���� txt���Ͽ� ����
		}
		while	(FindNextFile(hSrc, &wfd));		// wfd�� ���� ���Ϸ� �Ѿ� ����.
	}
	FindClose(hSrc);		// ���� �ڵ� �ݱ�

	return 0;
}
