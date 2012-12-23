#include "stdafx.h"
#include "LineEmitter.h"
#include "Bullet.h"

CLineEmitter::CLineEmitter(void)
{
}

CLineEmitter::~CLineEmitter(void)
{
}

void CLineEmitter::Emit( int nPosX, int nPosY )
{
    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        m_bulletType, m_fAngle);
}

void CLineEmitter::SetParam( bool bFriend, int nPower, int nSpeed, BulletType bulletType, float fAngle )
{
    m_bFriend = bFriend;
    m_nPower = nPower;
    m_nSpeed = nSpeed;
    m_bulletType = bulletType;
    m_fAngle = fAngle;
}
