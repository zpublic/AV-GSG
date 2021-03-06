#include "stdafx.h"
#include "Line3Emitter.h"
#include "gameobject\bullet\Bullet.h"

CLine3Emitter::CLine3Emitter(void)
    : m_fAngle(0.0)
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
        bulletType, float((13 * PI / 10.0) * m_fAngle));
    new CBullet(
        nPosX, nPosY,
        m_bFriend,
        bulletType, float((3 * PI / 2.0) * m_fAngle));
    new CBullet(
        nPosX, nPosY,
        m_bFriend,
        bulletType, float((15 * PI / 10.0) * (m_fAngle + 0.1)));
}

void CLine3Emitter::SetParam( bool bFriend, int nPower, int nSpeed , float fAngle)
{
    m_bFriend = bFriend;
    m_nPower = nPower;
    m_nSpeed = nSpeed;
    m_fAngle = fAngle;
}

