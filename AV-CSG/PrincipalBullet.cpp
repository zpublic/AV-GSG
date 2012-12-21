#include "StdAfx.h"
#include "PrincipalBullet.h"
#include <math.h>
#include "EnemyPlane.h"
#include "Explosion.h"

CPrincipalBullet::CPrincipalBullet(int x, int y, BulletType bulletType, float angle)
    : CBullet(x, y)
{
    m_nSpeed = 10;
    m_nPower = 3;
    m_nBulletType = bulletType;
    m_fAngle = angle;
    m_nFrameStartY = 0;
    switch(bulletType)
    {
    case AMMO0:
        m_nWidth = 16;
        m_nHeight = 16;
        m_nFrameCount = 8;
        break;
    case AMMO1:
        m_nWidth = 16;
        m_nHeight = 16;
        m_nFrameCount = 6;
        break;
    case AMMO2:
        m_nWidth = 11;
        m_nHeight = 11;
        m_nFrameCount = 1;
        break;
    case AMMO3:
        m_nWidth = 16;
        m_nHeight = 16;
        m_nFrameCount = 6;
        break;
    case AMMO4:
        m_nWidth = 12;
        m_nHeight = 60;
        m_nFrameCount = 5;
        break;
    case AMMO5:
        m_nWidth = 23;
        m_nHeight = 49;
        m_nFrameCount = 1;
        break;
    case AMMO6:
        m_nWidth = 26;
        m_nHeight = 31;
        m_nFrameCount = 3;
        break;
    case WHOLEFRIED:
        m_nWidth = 224;
        m_nHeight = 320;
        m_nFrameCount = 12;
        break;
    }
}

CPrincipalBullet::~CPrincipalBullet(void)
{
}

bool CPrincipalBullet::IsVisible()
{
    if (m_nBulletType == WHOLEFRIED)
    {
        if (m_nCurrentFrame > 11)
        {
            return false;
        }
        return true;
    }
    if (m_bIsVisible == false)
    {
        return m_bIsVisible;
    }
    if (m_nPosX < -50               ||
        m_nPosY < -50               ||
        m_nPosX > SCREEN_WIDTH + 50 ||
        m_nPosY > SCREEN_HEIGHT + 50)
    {
        return false;
    }
    return true;
}

void CPrincipalBullet::Render(HDC hDC)
{
    CPicturePool::GetPicture(emPicTypeBullet)[m_nBulletType]->DrawBitmap(
        hDC,
        m_nPosX, m_nPosY,
        m_nWidth, m_nHeight,
        m_nFrameStartX, m_nFrameStartY);
}

void CPrincipalBullet::Update()
{
    if (m_nBulletType == WHOLEFRIED)
    {
        int row = m_nCurrentFrame / 3;
        int col = m_nCurrentFrame % 3;
        m_nFrameStartX = col * 224 + col / 1;
        m_nFrameStartY = row * 320 + (row + 1) / 1;
        m_nCurrentFrame++;
        return;
    }
    float fDis = m_nSpeed;
    int nStartX = 0, nStartY = 0;

    m_nPosX += cos(m_fAngle) * fDis;
    m_nPosY += sin(m_fAngle) * fDis;

    m_nFrameStartX = m_nCurrentFrame * m_nWidth;
    ++m_nCurrentFrame;
    m_nCurrentFrame %= m_nFrameCount;

    CEnemyPlane* temp = CEnemyPlane::spEnemyHead;
    for( ; temp!=NULL; temp=temp->m_pEmnemyNext )
    {
        if(temp->CheckCollision(m_nPosX, m_nPosY, m_nWidth, m_nHeight, m_nPower))
        {
            m_bIsVisible = false;
            new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, BULLETBLAST);
            break;
        }
    }
}