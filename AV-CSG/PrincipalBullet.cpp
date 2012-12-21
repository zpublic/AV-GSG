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

CPrincipalBullet::~CPrincipalBullet(void)
{

}

void CPrincipalBullet::Update()
{
    float fDis = (float)m_nSpeed;
    int nStartX = 0, nStartY = 0;

    m_nPosX += int(cos(m_fAngle) * fDis);
    m_nPosY += int(sin(m_fAngle) * fDis);

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