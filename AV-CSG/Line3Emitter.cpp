#include "stdafx.h"
#include "Line3Emitter.h"
#include "Bullet.h"

CLine3Emitter::CLine3Emitter(void)
{
}

CLine3Emitter::~CLine3Emitter(void)
{
}

void CLine3Emitter::Emit( int nPosX, int nPosY, BulletType bulletType )
{
    new CBullet(
        nPosX, nPosY,
        m_bFriend,
        bulletType, float(17 * PI / 10.0));
    new CBullet(
        nPosX, nPosY,
        m_bFriend,
        bulletType, float(3 * PI / 2.0));
    new CBullet(
        nPosX, nPosY,
        m_bFriend,
        bulletType, float(13 * PI / 10.0));
}

void CLine3Emitter::SetParam( bool bFriend, int nPower, int nSpeed )
{
    m_bFriend = bFriend;
    m_nPower = nPower;
    m_nSpeed = nSpeed;
}

