#include "StdAfx.h"
#include ".\thumbnail.h"
#include "MDebug.h"
#include "RealSpace2.h"

_USING_NAMESPACE_REALSPACE2

CThumbnail::CThumbnail()
: m_pTexture(0)
, m_pSurface(0)
, m_pOldRenderTarget(0)
{
}

CThumbnail::~CThumbnail()
{
	SAFE_RELEASE(m_pOldRenderTarget);
	SAFE_RELEASE(m_pSurface);
	SAFE_RELEASE(m_pTexture);
}
/* ����Ÿ�� �ؽ�ó�� Ȱ���Ϸ��� �ߴµ�, �׳� ����ۿ��� Ư�� ������ crop�ؿ��°� ���ڴ� �; ���
bool CThumbnail::PrepareRenderTargetTexture()
{
	if(FAILED( D3DXCreateTexture( RGetDevice(), THUMBNAILSIZE, THUMBNAILSIZE, 1, D3DUSAGE_RENDERTARGET, 
		RGetPixelFormat(), D3DPOOL_DEFAULT, &m_pTexture)))
	{
		mlog( "RenderTarget Texture Creation Failed.\n" );
		return false;
	}

	if(FAILED(m_pTexture->GetSurfaceLevel( 0, &m_pSurface )))
	{
		mlog( "RenderTarget Texture GetSurface Failed.\n");
		return false;
	}

	RGetDevice()->GetRenderTarget(0, &m_pOldRenderTarget);
	RGetDevice()->SetRenderTarget(0, m_pSurface);
	
	return true;
}

void CThumbnail::RestoreRenderTargetTexture()
{
	RGetDevice()->SetRenderTarget(0, m_pOldRenderTarget);
	SAFE_RELEASE(m_pOldRenderTarget);
}
*/
void CThumbnailList::Add( int id, CThumbnail* pThumbnail )
{
	if (m_map.end() != m_map.find(id)) {
		mlog("����� ����Ʈ�� �ߺ��� id�� �߰��Ϸ��մϴ�(id:%d)\n", id);
		return;
	}

	m_map[id] = pThumbnail;
}