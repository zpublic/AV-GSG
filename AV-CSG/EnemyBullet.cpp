#include "StdAfx.h"
#include "EnemyBullet.h"
#include <math.h>
#include "GameControler.h"
#include "PrincipalPlane.h"
#include "Explosion.h"

CEnemyBullet::CEnemyBullet(int x, int y, BulletType bulletType, float angle)
    : CBullet(x, y, false, 5, 220, bulletType, angle)
{

}

CEnemyBullet::~CEnemyBullet(void)
{
}

void CEnemyBullet::Update()
{
    float tD = CGameControler::GetInstance()->GetElapsedTime();
    float fDis = tD * m_nSpeed;
    int nStartX = 0, nStartY = 0;

    m_nPosX += int(cos(m_fAngle) * fDis);
    m_nPosY += int(sin(m_fAngle) * fDis);

    m_nFrameStartX = m_nCurrentFrame * m_nWidth;
    ++m_nCurrentFrame;
    m_nCurrentFrame %= m_nFrameCount;

    if (CPrincipalPlane::GetInstance()->CheckCollision(
        m_nPosX, m_nPosY,
        m_nWidth, m_nHeight,
        m_nPower))
    {
        m_bIsVisible = false;
        new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, BULLETBLAST);
    }
}