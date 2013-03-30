#include "stdafx.h"
#include "BigBullet.h"


CBigBullet::CBigBullet(int x, int y)
    : CSprite(x, y)
{
    m_nFrameStartY = 0;
    m_nWidth = 224;
    m_nHeight = 320;
    m_nFrameCount = 12;
}


CBigBullet::~CBigBullet(void)
{
}

void CBigBullet::Update()
{
    int row = m_nCurrentFrame / 3;
    int col = m_nCurrentFrame % 3;
    m_nFrameStartX = col * 224 + col / 1;
    m_nFrameStartY = row * 320 + (row + 1) / 1;
    m_nCurrentFrame++;
    return;
}

bool CBigBullet::IsVisible()
{
    if (m_nCurrentFrame > 11)
    {
        return false;
    }
    return true;
}

void CBigBullet::Render(HDC hDC)
{
    CPicture* pDraw = CPicturePool::GetInstance()->GetPicture("emBulletTypeAmmoAll1_skin");
    if (pDraw != NULL)
    {
        pDraw->DrawBitmap(
            hDC,
            m_nPosX, m_nPosY,
            m_nWidth, m_nHeight,
            m_nFrameStartX, m_nFrameStartY);
    }
}
