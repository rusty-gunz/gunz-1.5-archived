#include <stdio.h>
#include <iostream>
#include <windows.h>

#define FILE_LIMIT_QUERY_LINE 50000
char* g_csFileName = 0;

void Separator(char* szOutbuf, char* cSeparator)
{
	char *token = NULL;
	token = strtok(szOutbuf, cSeparator); // ù��° ��ū ����
	sprintf(szOutbuf, "%s", token);

	while ((token = strtok(NULL, cSeparator)) != NULL) // ��ū�� �߻��� ������ ����
		sprintf(szOutbuf, "%s%s", szOutbuf, token);
}

char* CharInsert(char* to, char* from, int pos, char* s) {
	strncpy(to,from,pos);
	strcpy(to+pos,s);
	strcpy(to+pos+strlen(s),from+pos);
	return to;
}

// ��Ʈ���� "'"���ڰ� ������ "'"�� �Ѱ� �� �ٿ��ش�(������...)
void Insert_Char(char* szOutbuf)
{
	int nStrTemp = 0;
	char separator2[2] = {0};
	sprintf(separator2, "'");
	while( szOutbuf[nStrTemp] != NULL )
	{
		if(szOutbuf[nStrTemp] == separator2[0])
		{
			char tmp[256];
			CharInsert(tmp, szOutbuf, nStrTemp, "'");
			strcpy(szOutbuf, tmp);
			printf("%s\n", szOutbuf);
			++nStrTemp;
		}
		++nStrTemp;
	}
}

int g_nOutPutFileNumber = 1;

void OutPutFileName(char* csOutFileName, char* csInName)
{
	int nFileName = 0;
	while(1)
	{
		if(csInName[nFileName] == '.')
		{
			char buf[8] = {0};
			sprintf(buf, "%d", g_nOutPutFileNumber);
			CharInsert(csOutFileName, csInName, nFileName, buf);
			break;
		}
		++nFileName;
	}
	++g_nOutPutFileNumber;
}

main()
{
	FILE *rfp=NULL;
	FILE *wfp=NULL;
	rfp = fopen( "ip-to-country.csv" , "r" );
	if(!rfp)
	{
		::MessageBox(NULL, " 'ip-to-country.csv' File does not exist. ", "MessageBox", MB_OK);
		return;
	}


	char* csFileName = new char[32];
	OutPutFileName(csFileName, "ip-to-country.sql");
	wfp = fopen( csFileName , "w" );
	// ���â�� �� ���������� �׸��� �ʴ´�.
	fputs("SET NOCOUNT ON;\n\n", wfp);
	// �ϴ� IPtoCountry�� �����ش�.
	fputs("DELETE IPtoCountry\n\n", wfp);

	char szbuf[256] = {0};
	int i = 0;	int j = 0;
	unsigned long ulLineCount = 0;
	while ( !feof(rfp) )
	{
		fgets( szbuf , sizeof(szbuf) , rfp );
		if(strlen(szbuf) < 1)	continue; // ����ִ� �����϶�
		szbuf[strlen(szbuf)-1] = 0x00;
		/////////////////////////////////////////////////////////////////////////////////
		// ��) szbuf == "1040982608","1040982615","CI","CIV","COTE D'IVOIRE"
		/////////////////////////////////////////////////////////////////////////////////


		// ��Ʈ������ '"'�� ����
		char separator[2] = {'"', 0};
		Separator(szbuf, separator);
		/////////////////////////////////////////////////////////////////////////////////
		// ��) szbuf == 1040982608,1040982615,CI,CIV,COTE D'IVOIRE
		/////////////////////////////////////////////////////////////////////////////////


		// ��Ʈ���� "'"���ڰ� ������ "'"�� �Ѱ� �� �ٿ��ش�(������...)
		Insert_Char(szbuf);
		/////////////////////////////////////////////////////////////////////////////////
		// ��) szbuf == 1040982608,1040982615,CI,CIV,COTE D''IVOIRE
		/////////////////////////////////////////////////////////////////////////////////

		char csCharArr[5][64];
		while(1)
		{	// csCharArr�� �� ��Ʈ�� ����
			if(ulLineCount >= FILE_LIMIT_QUERY_LINE)
			{	// SQL���� ������ 10���̻�Ǹ� �����÷ο찡 �ɸ�
				fclose(wfp);
				OutPutFileName(csFileName, "ip-to-country.sql");
				wfp = fopen( csFileName , "w" );
				// ���â�� �� ���������� �׸��� �ʴ´�.
				fputs("SET NOCOUNT ON;\n\n", wfp);
				ulLineCount = 0;
			}

			if(szbuf[i] == ',')
			{
				if(j == 4)
				{	// ������ ���ڴ� �ٷ� �������ش�(������ �����߿� ','���ڰ� �ִ°�� ������)
					strcpy(csCharArr[j], szbuf);
					j = i = 0;
					break;
				}
				strncpy(csCharArr[j], szbuf, i);
				csCharArr[j][i]=0;

				strcpy(szbuf, szbuf+(i+1));
				++j;
				i = 0;
				/////////////////////////////////////////////////////////////////////////////////
				// ��) csCharArr[0]=1040982608, csCharArr[1]=1040982615, csCharArr[2]=CI
				//		, csCharArr[3]=CIV, csCharArr[4]=COTE D''IVOIRE
				/////////////////////////////////////////////////////////////////////////////////
			}

			if(szbuf[i] == 0x00)
			{
				strncpy(csCharArr[j], szbuf, i);
				csCharArr[j][i]=0;
				break;
			}
			++i;
		}
		
		sprintf(szbuf, "INSERT INTO IPtoCountry(IPFrom, IPTo, CountryCode2, CountryCode3, CountryName) Values (%s, %s, '%s', '%s', '%s')\n", 
			csCharArr[0], csCharArr[1], csCharArr[2], csCharArr[3], csCharArr[4]);

		fputs(szbuf , wfp);
		szbuf[0] = 0x00;
		j = i = 0;
		++ulLineCount;
	}

	if(csFileName)
		delete []csFileName;

	fclose(rfp);
	fclose(wfp);

	return true;
}
