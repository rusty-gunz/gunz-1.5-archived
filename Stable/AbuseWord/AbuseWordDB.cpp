#include "StdAfx.h"
#include ".\abuseworddb.h"
#include <algorithm>

#pragma comment( lib, "libmysql.lib" )




bool CAbuseList::InsertAbuseWord( const ABUSE_WORD_INFO& AbuseWordInfo )
{
	return InsertAbuseWord( AbuseWordInfo.m_strKeyAbuseWord, 
							AbuseWordInfo.m_strReplaceWord, 
							AbuseWordInfo.m_nCheckState );
}


bool CAbuseList::InsertAbuseWord( const string& strKeyAbuseWord, const string& strReplaceWord, const AW_CHECK_STATE nCheckState )
{
	// ����Ʈ�� �ߺ��Ǵ� �ܾ ����� ��.
	const ABUSE_WORD_INFO* pDupAbuseWord = GetAbuseWordByKeyAbuseWord( strKeyAbuseWord );

	ASSERT( (0 == pDupAbuseWord) && "CAbuseList::InsertAbuseWord -> ����Ʈ�� ������ �ܾ ������ �ʵ�." );

	if( 0 == pDupAbuseWord )
	{
		ABUSE_WORD_INFO AbuseWordInfo;

		AbuseWordInfo.m_strKeyAbuseWord = strKeyAbuseWord;
		AbuseWordInfo.m_strReplaceWord	= strReplaceWord;
		AbuseWordInfo.m_nCheckState		= nCheckState;

		if( AW_USED == nCheckState )
			m_AbuseWordList.push_back( AbuseWordInfo );
		else
			m_AbuseWordList.push_front( AbuseWordInfo );

		return true;
	}

	return false;
}


AbuseWordDeq::iterator CAbuseList::Find( const string& strKeyAbuseWord )
{
	if( strKeyAbuseWord.empty() || m_AbuseWordList.empty() )
		return m_AbuseWordList.end();

	return find_if( m_AbuseWordList.begin(), 
					m_AbuseWordList.end(), 
					CAbuseWordFinder<ABUSE_WORD_INFO>(strKeyAbuseWord) );
}

AbuseWordDeq::iterator CAbuseList::FindFirstUncheckedPos()
{
	if( m_AbuseWordList.empty() )
		return m_AbuseWordList.end();

	return find_if( m_AbuseWordList.begin(), 
					m_AbuseWordList.end(), 
					CUncheckedFinder<ABUSE_WORD_INFO>() );
}

const ABUSE_WORD_INFO* CAbuseList::FindFirstUnchecked()
{
	AbuseWordDeq::iterator itFind = FindFirstUncheckedPos();
	if( m_AbuseWordList.end() != itFind )
		return &(*itFind);
	
	return 0;
}	


const ABUSE_WORD_INFO* CAbuseList::GetAbuseWordByPos( const unsigned int nPos )
{
	if( nPos < m_AbuseWordList.size() )
		return &m_AbuseWordList[ nPos ];

	return 0;
}


const ABUSE_WORD_INFO* CAbuseList::GetAbuseWordByKeyAbuseWord( const string& strKeyAbuseWord )
{
	AbuseWordDeq::iterator itFind = Find( strKeyAbuseWord );

	if( m_AbuseWordList.end() != itFind )
		return &(*itFind);
	
	return 0;
}


void CAbuseList::Check( const string& strKeyAbuseWord, const AW_CHECK_STATE nCheckState )
{
	if( !m_AbuseWordList.empty() )
	{
		AbuseWordDeq::iterator itFind = Find( strKeyAbuseWord );

		if( m_AbuseWordList.end() != itFind )
			(*itFind).m_nCheckState = nCheckState;
	}
}


void CAbuseList::Delete( const string& strKeyAbuseWord )
{
	AbuseWordDeq::iterator itFind = Find( strKeyAbuseWord );
	if( m_AbuseWordList.end() != itFind )
		m_AbuseWordList.erase( itFind );
}


void CAbuseList::DeleteUncheckedAbuseWord()
{
	AbuseWordDeq::iterator itFind;
	for( itFind = FindFirstUncheckedPos(); 
		 m_AbuseWordList.end() != itFind; 
		 itFind = FindFirstUncheckedPos() )
	{
		m_AbuseWordList.erase( itFind );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CAbuseWordDB::CAbuseWordDB(void) : m_bIsConnected( false )
{
	mysql_init( &m_MySql );
}

CAbuseWordDB::~CAbuseWordDB(void)
{
}


bool CAbuseWordDB::ConnectDB()
{
	if( !m_bIsConnected )
	{
		if( !mysql_real_connect(&m_MySql, 
								m_strHost.c_str(), 
								m_strUser.c_str(), 
								m_strPassword.c_str(), 
								m_strDB.c_str(), 
								0, 
								(char*)NULL, 
								0) )
		{
#ifdef _DEBUG
			const char* pszError = mysql_error( &m_MySql );
			OutputDebugString( pszError );
#endif
			return false;
		}
		
		m_bIsConnected = true;
	}
	
	return m_bIsConnected;
}


void CAbuseWordDB::DisconnectDB()
{
	if( m_bIsConnected )
	{
		mysql_close( &m_MySql );

		m_bIsConnected = false;
	}
}


bool CAbuseWordDB::GetDBAbuseList()
{
	if( m_bIsConnected )
	{
		string strQuery = "SELECT * FROM abuse_word";
		if( Query(strQuery) )
		{
			MYSQL_RES* pRes;

			pRes = mysql_store_result( &m_MySql );
			if( 0 != pRes )
			{
				MYSQL_ROW Row;
				
				while( (Row = mysql_fetch_row(pRes)) )
				{
					const int nFieldNum = static_cast<int>( mysql_num_fields(pRes) );
					ASSERT( COLUMN_COUNT == nFieldNum );

					m_AbuseWordList.InsertAbuseWord( Row[0], Row[1], ((1 == atoi(Row[2])) ? AW_USED : AW_NEW) );
				}
			}
		}
	}

	return false;
}


bool CAbuseWordDB::UpdateDB()
{
	// ������Ʈ�� CheckState�� AW_ADD�ΰ͸� ���� ��� ������ ��.
	AW_CHECK_STATE nCheckState;
	const int nAbuseListCount = m_AbuseWordList.Size();
	for( int i = 0; i < nAbuseListCount; ++i )
	{
		const ABUSE_WORD_INFO* pAbuseWordInfo = m_AbuseWordList.GetAbuseWordByPos( i );

		ASSERT( 0 != pAbuseWordInfo );

		nCheckState = pAbuseWordInfo->m_nCheckState;

		if( (0 != pAbuseWordInfo) && (AW_USED != nCheckState) && (AW_NEW != nCheckState) )
			if( !UpdateOneAbuseWordDB(pAbuseWordInfo->m_strKeyAbuseWord) )
				return false;
	}

	return true;
}


bool CAbuseWordDB::UpdateOneAbuseWordDB( const string& strKeyAbuseWord )
{
	if( m_bIsConnected && !strKeyAbuseWord.empty() )
	{
		const ABUSE_WORD_INFO* pAbuseWordInfo = m_AbuseWordList.GetAbuseWordByKeyAbuseWord( strKeyAbuseWord );
		if( 0 != pAbuseWordInfo ) 
		{
			const AW_CHECK_STATE nCheckState = pAbuseWordInfo->m_nCheckState;

			if( AW_ADD == nCheckState )
			{
				const string strQuery( "UPDATE abuse_word SET Checked = 1 WHERE AbuseWord LIKE BINARY('" + strKeyAbuseWord + "')" );
				if( !Query(strQuery) )
					return false;

				return true;
			}
			else if( AW_DEL == nCheckState )
			{
				const string strQuery( "UPDATE abuse_word SET Checked = 0 WHERE AbuseWord LIKE BINARY('" + strKeyAbuseWord + "')" );
				if( !Query(strQuery) )
				{
					ASSERT( "CAbuseWordDB::UpdateOneAbuseWordDB -> 'Checked = 0'���� ����." );
					return false;
				}

				return true;
			}
			else
			{
				ASSERT( 0 && "���ǵ��� ����" );
			}
		}
	}

	return false;
}


void CAbuseWordDB::Check( const string& strKeyString, const AW_CHECK_STATE nCheckState )
{
	if( !strKeyString.empty() || (0 != m_AbuseWordList.Size()) )
		m_AbuseWordList.Check( strKeyString, nCheckState );
}


bool CAbuseWordDB::DeleteUnchecked()
{
	// ���� ���� ���Ű� �Ǿ�� ��.

	const unsigned int nAbuseWordCount = m_AbuseWordList.Size();
	for( unsigned int i = 0; i < nAbuseWordCount; ++i )
	{
		const ABUSE_WORD_INFO* pAbuseWordInfo = m_AbuseWordList.GetAbuseWordByPos( i );
		if( 0 != pAbuseWordInfo )
		{
			const AW_CHECK_STATE nCheckState = pAbuseWordInfo->m_nCheckState;
			if( (AW_NEW == nCheckState) || (AW_DEL == nCheckState) )
			{
				if( ConnectDB() )
				{
					if( DeleteAbuseWord(pAbuseWordInfo->m_strKeyAbuseWord) )
					{
						// �ݺ��� �߰��� ����Ʈ ������ �̷������ Index�� ��ȿ���� ������ �Ҽ� ����.
						// ������ �� ������ �ϰ������� ����Ʈ���� Checked�� AW_DEL�� ��� ��ü�� ������.
					}
					else 
					{
						DisconnectDB();
						return false;
					}
				}
				else
					return false;
				DisconnectDB();
			}
		}
		else
		{
			ASSERT( (0 != pAbuseWordInfo) && "�߸��� �ε��� ����." );
			return false;
		}
	}

	// ���⼭ Checked�� AW_DEL�� ��ü�� ��� ������.
	m_AbuseWordList.DeleteUncheckedAbuseWord();

	return true;
}


bool CAbuseWordDB::InsertAbuseWord( const string& strKeyAbuseWord, const string& strReplaceWord, const AW_CHECK_STATE nCheckState )
{
	if( m_AbuseWordList.InsertAbuseWord(strKeyAbuseWord, strReplaceWord, nCheckState) )
		return true;
	return false;
}


bool CAbuseWordDB::DeleteAbuseWord( const string& strKeyAbuseWord )
{
	const string strQuery( "DELETE FROM abuse_word  WHERE AbuseWord LIKE BINARY('" + strKeyAbuseWord + "')" );
	if( Query(strQuery) )
		return true;

	return false;
}


void CAbuseWordDB::SetReplaceWord( const string& strKeyAbuseWord, const string& strReplaceWord )
{
	ASSERT( 0 && "���� �����ϴ� ����� �ƴ�." );

	// ���Ŀ� ����� �ϰԵȴٸ� ��� �߰���.
	// ������ ������� Ȯ������ �ʾƼ� �������̽��� ����� ����.
}


const ABUSE_WORD_INFO* CAbuseWordDB::GetAbuseWordByPos( const unsigned int nPos )
{
	ASSERT( (nPos < m_AbuseWordList.Size()) && "CAbuseWordDB::GetAbuseWordByPos -> ã�� ��ġ�� ��ȿ���� ����." );

	if( nPos < static_cast<unsigned int>(m_AbuseWordList.Size()) )
	{
		const ABUSE_WORD_INFO* pAbuseWordInfo = m_AbuseWordList.GetAbuseWordByPos( nPos );
		if( 0 != pAbuseWordInfo )
			return pAbuseWordInfo;
	}

	return 0;
}


const ABUSE_WORD_INFO* CAbuseWordDB::GetAbuseWordByKeyAbuseWord( const string& strKeyAbuseWord )
{
	ASSERT( !strKeyAbuseWord.empty() && "CAbuseWordDB::GetAbuseWordByKeyAbuseWord -> ���� ���̰� 0�Ǹ� �ʵ�." );

	if( !strKeyAbuseWord.empty() )
	{
		const ABUSE_WORD_INFO* pAbuseWordInfo = m_AbuseWordList.GetAbuseWordByKeyAbuseWord( strKeyAbuseWord );
		if( 0 != pAbuseWordInfo )
			return pAbuseWordInfo;
	}

	return 0;
}


bool CAbuseWordDB::Query( const string& strQuery )
{
	if( 0 == mysql_real_query(&m_MySql, strQuery.c_str(), static_cast<unsigned long>(strQuery.length())) )
		return true;
	
	return false;
}


bool CAbuseWordDB::InsertAbuseWordDirectDB( const string& strKeyAbuseWord , const string& strReplaceWord, const AW_CHECK_STATE nCheckState )
{
	if( !strKeyAbuseWord.empty() )
	{
		const string strQuery( "INSERT INTO abuse_word( AbuseWord, ReplaceWord, Checked ) VALUES ('" +
			strKeyAbuseWord + "', '" + strReplaceWord + "', 0)" );
		if( Query(strQuery) )
		{
			if( InsertAbuseWord(strKeyAbuseWord, string("NULL"), AW_NEW) )
				return true;
		}
	}

	return false;
}


bool CAbuseWordDB::SaveLocalFile( const string& strLocalFileName )
{
	if( !strLocalFileName.empty() )
	{
		// ������ ����Ʈ ���� ����.
		const string strBuf = MakeLocalFileInfo();
		if( !strBuf.empty() )
		{
			FILE* fp = fopen( strLocalFileName.c_str(), "w" );
			if( 0 != fp )
			{
				try
				{
					fprintf( fp, "%s", strBuf.c_str() );
				}
				catch( ... )
				{
					if( 0 != fp )
						fclose( fp );

					ASSERT( 0 && "�������Ͽ� ���忡�� Exception�߻�" );

					return false;
				}
			}
			fclose( fp );
		}
	}

	return true;
}


const string CAbuseWordDB::MakeLocalFileInfo()
{
	SYSTEMTIME SystemTime;
	GetSystemTime( &SystemTime );

	char szDate[ 1024 ];
	_snprintf( szDate, 1023, "%d-%d-%d %d:%d:%d", 
		SystemTime.wYear,
		SystemTime.wMonth,
		SystemTime.wDay,
		SystemTime.wHour + 9,
		SystemTime.wMinute,
		SystemTime.wSecond );
	
	string strBuf( "ABUSE_BEGIN\t" + string(szDate) + "\n" );

	const unsigned int nAbuseListCount = m_AbuseWordList.Size();
	for( unsigned int i = 0; i < nAbuseListCount; ++i )
	{
		const ABUSE_WORD_INFO* pAbuseWordInfo = m_AbuseWordList.GetAbuseWordByPos( i );
		if( 0 != pAbuseWordInfo )
		{
			strBuf += pAbuseWordInfo->m_strKeyAbuseWord + " " + 
					  pAbuseWordInfo->m_strReplaceWord + "\n";
		}
		else
		{
			ASSERT( (0 != pAbuseWordInfo) && ("�߸��� ������.") );
		}
	}

	strBuf += string( "END" );

	return strBuf;
}