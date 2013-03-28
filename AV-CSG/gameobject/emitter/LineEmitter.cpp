#include "stdafx.h"
#include "LineEmitter.h"
#include "gameobject\bullet\Bullet.h"

CLineEmitter::CLineEmitter(void)
{
}

CLineEmitter::~CLineEmitter(void)
{
}

void CLineEmitter::Emit( int nPosX, int nPosY, BulletType bulletType )
{
    new CBullet(
        nPosX, nPosY,
        m_bFriend,
        bulletType, m_fAngle);
}

void CLineEmitter::SetParam( bool bFriend, int nPower, int nSpeed, float fAngle )
{
    m_bFriend = bFriend;
    m_nPower = nPower;
    m_nSpeed = nSpeed;
    m_fAngle = fAngle;
}
