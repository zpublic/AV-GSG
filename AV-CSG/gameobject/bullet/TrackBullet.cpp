#include "stdafx.h"
#include "TrackBullet.h"
#include "gameobject\plane\SelfPlane.h"
#include "control\generate\EnemyGenerate.h"
#include "gameobject\explosion\Explosion.h"
#include "gameobject\plane\EnemyPlane.h"


CTrackBullet::CTrackBullet(
    int x, int y,
    bool bFriend,
    BulletType bulletType,
    float fAngle)
    : CBullet(x, y, bFriend, bulletType, fAngle)
{
    m_bNeedTrack = true;
}


CTrackBullet::~CTrackBullet(void)
{
}

void CTrackBullet::Update()
{
    int x = 0, y = 0;
    if (m_bFriend)
    {
        CEnemyPlane* temp = CEnemyGenerate::spEnemyHead;
        if (temp == NULL)
        {
            m_bNeedTrack = false;
        }
        else
        {
            while (temp->m_pEmnemyNext != NULL)
            {
                temp = temp->m_pEmnemyNext;
            }
            x = temp->GetX();
            y = temp->GetY();
        }
    }
    else
    {
        x = CSelfPlane::GetInstance()->GetX();
        y = CSelfPlane::GetInstance()->GetY();
    }
    if (m_bNeedTrack)
    {
        if ((y < m_nPosY) && !m_bFriend)
            m_bNeedTrack = false;
    }
    if (m_bNeedTrack)
    {
        m_fAngle = Unit::CalcAngle(m_nPosX, m_nPosY, x, y);
    }

    float fDis = ElapsedTime * m_nSpeed;
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
                new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, "emBlastTypeBullet");
                break;
            }
        }
    }
    else
    {
        if (CSelfPlane::GetInstance()->CheckCollision(
            m_nPosX, m_nPosY,
            m_nWidth, m_nHeight,
            m_nPower))
        {
            m_bIsVisible = false;
            new CExplosion(m_nPosX + m_nWidth / 2, m_nPosY + m_nHeight / 2, "emBlastTypeBullet");
        }
    }
}
