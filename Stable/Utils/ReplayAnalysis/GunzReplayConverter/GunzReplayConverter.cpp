// GunzReplayConverter.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "ReplayConverter.h"

using namespace std;

int _tmain( int argc, _TCHAR* argv[] )
{
	if( argc < 2 )
	{
		cout << "���÷��� ���ϵ��� �ִ� ������ ������ �巡�� �ؼ� ������ �ּ���.\n";
		getchar();
		return -1;
	}

	char szModuleFileName[_MAX_DIR] = {0,};
	GetModuleFileName( NULL, szModuleFileName, _MAX_DIR );
	PathRemoveFileSpec( szModuleFileName );
	SetCurrentDirectory( szModuleFileName );

	InitLog( "log.txt" );

	for( int i = 1; i < argc; ++i )
	{
		cout << "����: " << argv[i] << "\n";
		Log( "����: %s\n", argv[i] );
	}

	ReplayConverter replayConverter;

	for( int i = 1; i < argc; ++i )
	{
		string path = argv[i];
		path += "\\";
		string filter = path;
	//	filter += "*";
		filter += "*."; filter += GUNZ_REC_FILE_EXT;

		WIN32_FIND_DATA findFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		hFind = FindFirstFile( filter.c_str(), &findFileData );

		if( hFind == INVALID_HANDLE_VALUE )
		{
			continue;
		}

		cout << "����: " << findFileData.cFileName << "\n";
		Log( "����: %s\n", findFileData.cFileName );
		if( !replayConverter.Add( path + findFileData.cFileName ) )
		{
			cout << "[[���� �б� ����]]: " << findFileData.cFileName << "\n";
			Log( "[[���� �б� ����]]: %s\n", findFileData.cFileName );
		}

		while( FindNextFile( hFind, &findFileData ) ) 
		{
			cout << "����: " << findFileData.cFileName << "\n";
			Log( "����: %s\n", findFileData.cFileName );
			if( !replayConverter.Add( path + findFileData.cFileName ) )
			{
				cout << "[[���� �б� ����]]: " << findFileData.cFileName << "\n";
				Log( "[[���� �б� ����]]: %s\n", findFileData.cFileName );
			}
		}

		FindClose( hFind );
	}

	if( !replayConverter.SaveCSV() )
	{
		cout << "[[CSV ���� ���� ����]]\n";
	}

	CloseLog();

	cout << "...�ƹ�Ű�� ��������.\n";
	getchar();

	return 0;
}

