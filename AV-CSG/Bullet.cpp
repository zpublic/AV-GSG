#include "StdAfx.h"
#include "Bullet.h"
#include "PrincipalPlane.h"
#include "GameControler.h"
#include <math.h>
#include "EnemyPlane.h"
#include "Explosion.h"

CBullet::CBullet(int x, int y,
                 bool bFriend,
                 int nPower,
                 int nSpeed,
                 BulletType bulletType,
                 float fAngle)
    : CSprite(x, y)
{
    m_bFriend = bFriend;
    m_nPower = nPower;
    m_nSpeed = nSpeed;
    m_fAngle = fAngle;
    m_nBulletType = bulletType;
    switch(bulletType)
    {
    case emBulletTypeAMMO0:
        m_nWidth = 16;
        m_nHeight = 16;
        m_nFrameCount = 8;
        break;
    case emBulletTypeAMMO1:
        m_nWidth = 16;
        m_nHeight = 16;
        m_nFrameCount = 6;
        break;
    case emBulletTypeAMMO2:
        m_nWidth = 11;
        m_nHeight = 11;
        m_nFrameCount = 1;
        break;
    case emBulletTypeAMMO3:
        m_nWidth = 16;
        m_nHeight = 16;
        m_nFrameCount = 6;
        break;
    case emBulletTypeAMMO4:
        m_nWidth = 12;
        m_nHeight = 60;
        m_nFrameCount = 5;
        break;
    case emBulletTypeAMMO5:
        m_nWidth = 23;
        m_nHeight = 49;
        m_nFrameCount = 1;
        break;
    case emBulletTypeAMMO6:
        m_nWidth = 26;
        m_nHeight = 31;
        m_nFrameCount = 3;
        break;
    case emBulletTypeAmmoAll1:
        m_nWidth = 224;
        m_nHeight = 320;
        m_nFrameCount = 12;
        break;
    }
}

CBullet::~CBullet(void)
{

}

bool CBullet::IsVisible()
{
    if(m_bIsVisible == false)
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

void CBullet::Render(HDC hDC)
{
    CPicturePool::GetPicture(emPicTypeBullet)[m_nBulletType]->DrawBitmap(
        hDC,
        m_nPosX, m_nPosY,
        m_nWidth, m_nHeight,
        m_nFrameStartX, 0);
}

void CBullet::Update()
{
    float fDis = (float)m_nSpeed;
    if (!m_bFriend)
        fDis *= CGameControler::GetInstance()->GetElapsedTime();
    int nStartX = 0, nStartY = 0;

    m_nPosX += int(cos(m_fAngle) * fDis);
    m_nPosY += int(sin(m_fAngle) * fDis);

    m_nFrameStartX = m_nCurrentFrame * m_nWidth;
    ++m_nCurrentFrame;
    m_nCurrentFrame %= m_nFrameCount;

    if (m_bFriend)
    {
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
    else
    {
        if (CPrincipalPlane::GetInstance()->CheckCollision(
            m_nPosX, m_nPosY,
            m_nWidth, m_nHeight,
            m_nPower))
        {
            m_bIsVisible = false;
            new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, BULLETBLAST);
        }
    }
}