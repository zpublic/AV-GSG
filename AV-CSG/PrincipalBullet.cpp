#include "StdAfx.h"
#include "PrincipalBullet.h"
#include <math.h>
#include "EnemyPlane.h"
#include "Explosion.h"

CPrincipalBullet::CPrincipalBullet(int x, int y, BulletType bulletType, float angle)
    : CBullet(x, y, true, 3, 10, bulletType, angle)
{

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