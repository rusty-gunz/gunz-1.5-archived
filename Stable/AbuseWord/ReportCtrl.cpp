// ReportCtrl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AbuseWord.h"
#include "ReportCtrl.h"
#include ".\reportctrl.h"
#include "AbuseWordDlg.h"


// CReportCtrl

IMPLEMENT_DYNAMIC(CReportCtrl, CListCtrl)
CReportCtrl::CReportCtrl()
{
}

CReportCtrl::~CReportCtrl()
{
}


const int CReportCtrl::FindSelectItem()
{
	bool isFocus = ( GetFocus() == this );

	LVITEM lvi;
	const int nItemCount = GetItemCount();
	bool isSelected;

	for( int i = 0; i < nItemCount; ++i )
	{
		lvi.mask = LVIF_STATE;
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = 0;
		lvi.cchTextMax = 0;
		lvi.stateMask = 0xFFFF;

		GetItem( &lvi );

		isSelected = (isFocus || (GetStyle() & LVS_SHOWSELALWAYS)) && lvi.state & LVIS_SELECTED;
		isSelected	= isSelected || (lvi.state & LVIS_DROPHILITED);

		if( isSelected )
			return i;
	}

	return -1;
}


const int CReportCtrl::FindChageCheckState()
{
	CWnd* pWnd = theApp.GetMainWnd();
	if( 0 != pWnd )
	{
		CAbuseWordDlg* pDlgWnd		= reinterpret_cast< CAbuseWordDlg* >( pWnd );
		CAbuseWordDB& AbuseWordDB	= pDlgWnd->GetAbuseWordDB();

		LVITEM lvi;
		const int nItemCount = GetItemCount();
		char szItemName[ 1024 ];

		for( int i = 0; i < nItemCount; ++i )
		{
			lvi.mask = LVIF_TEXT;
			lvi.iItem = i;
			lvi.iSubItem = 0;
			lvi.pszText = szItemName;
			lvi.cchTextMax = 1023;

			GetItem( &lvi );

			ASSERT( (0 != strlen(szItemName)) && "CReportCtrl::FindChageCheckState -> ���� ���̰� 0�̵Ǹ� �ʵ�." );

			const ABUSE_WORD_INFO* pAbuseWord = AbuseWordDB.GetAbuseWordByKeyAbuseWord( string(szItemName) );
			if( 0 == pAbuseWord )
			{
				ASSERT( (0 != pAbuseWord) && "CReportCtrl::FindChageCheckState -> �ܾ ã�� ����." );
				break;
			}

			if( GetCheck(i) )
			{
				if( (AW_NEW == pAbuseWord->m_nCheckState) || (AW_DEL == pAbuseWord->m_nCheckState) )
					return i;
			}
			else
			{
				if( (AW_NEW != pAbuseWord->m_nCheckState) && (AW_DEL != pAbuseWord->m_nCheckState) )
					return i;
				// 
			}
		}
	}

	return -1;
}


const int CReportCtrl::FindPosition( const string& strAbuseWord )
{
	if( !strAbuseWord.empty() )
	{
		LVITEM lvi;
		char szItemName[ 1024 ];

		const int nListCount = GetItemCount();
		for( int i = 0; i < nListCount; ++i )
		{
			lvi.mask = LVIF_TEXT;
			lvi.iItem = i;
			lvi.iSubItem = 0;
			lvi.pszText = szItemName;
			lvi.cchTextMax = 1023;

			GetItem( &lvi );

			ASSERT( (0 != strlen(szItemName)) && "CReportCtrl::FindPosition -> ���� ���̰� 0�̵Ǹ� �ʵ�." );

			if( 0 == strncmp(strAbuseWord.c_str(), szItemName, strAbuseWord.length() > strlen(szItemName) ? strAbuseWord.length() : strlen(szItemName)) )
				return i;	
		}
	}

	return -1;
}


void CReportCtrl::ScrollUp( const int nPos )
{
	if( 0 < nPos ) 
		return;

	CSize sz;
	sz.SetSize( 0, nPos );

	Scroll( sz );
}


void CReportCtrl::ScrollDown( const int nPos )
{
	if( 0 > nPos )
		return;

	CSize sz;
	sz.SetSize( 0, nPos );

	Scroll( sz );
}


const string CReportCtrl::GetSelectedItemText()
{
	char szItemText[ 512 ];

	GetItemText( FindSelectItem(), 0, szItemText, 511 );

	return string( szItemText );
}


BEGIN_MESSAGE_MAP(CReportCtrl, CListCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CReportCtrl �޽��� ó�����Դϴ�.


void CReportCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CListCtrl::OnLButtonDown(nFlags, point);

	if( 0 == GetItemCount() ) return;

	// Check�ڽ��� Ŭ���������� �۵��ؾ� ��.
	if( -1 == FindSelectItem() )
	{
		const int nItemID = FindChageCheckState();
		ASSERT( (-1 != nItemID) && "CReportCtrl::OnLButtonDown -> ��ȿ���� ���� ������ ID��" );
		char szItemName[ 1024 ] = {0};
		LVITEM lvi;

		lvi.mask = LVIF_TEXT;
		lvi.iItem = nItemID;
		lvi.iSubItem = 0;
		lvi.pszText = szItemName;
		lvi.cchTextMax = 1024;

		GetItem( &lvi );

		CWnd* pWnd = theApp.GetMainWnd();
		if( 0 != pWnd )
		{
			CAbuseWordDlg* pDlgWnd		= reinterpret_cast< CAbuseWordDlg* >( pWnd );
			CAbuseWordDB& AbuseWordDB	= pDlgWnd->GetAbuseWordDB();

			const ABUSE_WORD_INFO* pAbuseWord = AbuseWordDB.GetAbuseWordByKeyAbuseWord( string(szItemName) );
			if( 0 != pAbuseWord )
			{
				if( AW_NEW == pAbuseWord->m_nCheckState )
					AbuseWordDB.Check( string(szItemName), AW_ADD );
				else if( AW_USED == pAbuseWord->m_nCheckState )
					AbuseWordDB.Check( string(szItemName), AW_DEL ); // ���ŵǴ� �ܾ�ǥ�÷� ������ �ٲ�� �ϰ� ���� ��...��.��
				else if( AW_DEL == pAbuseWord->m_nCheckState )
					AbuseWordDB.Check( string(szItemName), AW_USED );
				else
					AbuseWordDB.Check( string(szItemName), AW_NEW );
			}
			else
			{
				ASSERT( 0 );
			}
		}
	}
}
