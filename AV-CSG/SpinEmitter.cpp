#include "stdafx.h"
#include "SpinEmitter.h"
#include "Bullet.h"

CSpinEmitter::CSpinEmitter(void)
{
    m_nAngle = 8;
}

CSpinEmitter::~CSpinEmitter(void)
{
}

void CSpinEmitter::Emit( int nPosX, int nPosY, BulletType bulletType )
{
    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, float(m_nAngle * PI / 16.0));
    m_nAngle++;
    m_nAngle %= 32;
}

void CSpinEmitter::SetParam( bool bFriend, int nPower, int nSpeed )
{
    m_bFriend = bFriend;
    m_nPower = nPower;
    m_nSpeed = nSpeed;
}
