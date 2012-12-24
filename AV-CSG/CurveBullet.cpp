#include "stdafx.h"
#include "CurveBullet.h"
#include "GameControler.h"
#include <math.h>
#include "Explosion.h"
#include "PrincipalPlane.h"
#include "EnemyPlane.h"
#include "EnemyGenerate.h"

CCurveBullet::CCurveBullet(
    int x, int y,
    bool bFriend,
    int nPower,
    int nSpeed,
    BulletType bulletType,
    float fAngle)
    : CBullet(x, y, bFriend, nPower, nSpeed, bulletType, fAngle)
{
    m_nStatus = 7;
}

CCurveBullet::~CCurveBullet(void)
{
}

void CCurveBullet::Update()
{
    float fDis = CGameControler::GetInstance()->GetElapsedTime() * m_nSpeed;
    m_nPosX += int(cos(m_fAngle) * fDis);
    m_nPosY += int(sin(m_fAngle) * fDis);
    if (m_nStatus < 15)
    {
        m_nPosX += 5;
    }
    else
    {
        m_nPosX -= 5;
    }
    m_nStatus++;
    m_nStatus %= 30;

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
