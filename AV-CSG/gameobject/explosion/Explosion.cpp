#include "StdAfx.h"
#include "Explosion.h"

CExplosion::CExplosion(int x, int y, BlastType blastType)
    : CSprite(x, y)
    , m_emBlastType(blastType)
{
    m_Blast = CBulletXMLParse::GetInstance().Get(blastType);
    if (m_Blast == NULL)
    {
        return;
    }
    m_nWidth = m_Blast->GetWidth();
    m_nHeight = m_Blast->GetHeight();
    m_nFrameCount = m_Blast->GetFrameCount();
}

CExplosion::~CExplosion(void)
{

}

void CExplosion::Update()
{
    if (m_nCurrentFrame >= m_nFrameCount)
    {
        m_bIsVisible = false;
    }
    m_nFrameStartX = m_nCurrentFrame * m_nWidth;
    m_nCurrentFrame++;
}

void CExplosion::Render(HDC hDC)
{
    CPicturePool::GetInstance()->GetPicture(m_Blast->GetSkinId())->DrawBitmap(
        hDC,
        m_nPosX - m_nWidth / 2,
        m_nPosY - m_nHeight / 2,
        m_nWidth,
        m_nHeight,
        m_nFrameStartX,
        0);
}