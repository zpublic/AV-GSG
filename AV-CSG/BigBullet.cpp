#include "stdafx.h"
#include "BigBullet.h"


CBigBullet::CBigBullet(int x, int y, BulletType bulletType, float angle)
    : CBullet(x, y, true, 0, 0, bulletType, angle)
{
    m_nFrameStartY = 0;
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
    CPicturePool::GetPicture(emPicTypeBullet)[m_nBulletType]->DrawBitmap(
        hDC,
        m_nPosX, m_nPosY,
        m_nWidth, m_nHeight,
        m_nFrameStartX, m_nFrameStartY);
}
