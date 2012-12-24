#include "stdafx.h"
#include "TrackBullet.h"
#include "PrincipalPlane.h"
#include "GameControler.h"
#include "EnemyGenerate.h"
#include "Explosion.h"
#include "EnemyPlane.h"


CTrackBullet::CTrackBullet(
    int x, int y,
    bool bFriend,
    int nPower,
    int nSpeed,
    BulletType bulletType,
    float fAngle)
    : CBullet(x, y, bFriend, nPower, nSpeed, bulletType, fAngle)
{
    m_bNeedTrack = true;
}


CTrackBullet::~CTrackBullet(void)
{
}

void CTrackBullet::Update()
{
    int x = CPrincipalPlane::GetInstance()->GetX();
    int y = CPrincipalPlane::GetInstance()->GetY();
    if (m_bNeedTrack)
    {
        if (y < m_nPosY)
            m_bNeedTrack = false;
    }
    if (m_bNeedTrack)
    {
        m_fAngle = Unit::CalcAngle(m_nPosX, m_nPosY, x, y);
    }

    float fDis = CGameControler::GetInstance()->GetElapsedTime() * m_nSpeed;
    m_nPosX += int(cos(m_fAngle) * fDis);
    m_nPosY += int(sin(m_fAngle) * fDis);

    m_nFrameStartX = m_nCurrentFrame * m_nWidth;
    ++m_nCurrentFrame;
    m_nCurrentFrame %= m_nFrameCount;

    if (m_bFriend)
    {
        CEnemyPlane* temp = CEnemyGenerate::spEnemyHead;
        for( ; temp!=NULL; temp=temp->m_pEmnemyNext )
        {
            if(temp->CheckCollision(m_nPosX, m_nPosY, m_nWidth, m_nHeight, m_nPower))
            {
                m_bIsVisible = false;
                new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, emBlastTypeBullet);
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
            new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, emBlastTypeBullet);
        }
    }
}
