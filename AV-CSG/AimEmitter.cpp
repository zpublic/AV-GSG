#include "stdafx.h"
#include "AimEmitter.h"
#include "PrincipalPlane.h"
#include "Bullet.h"

CAimEmitter::CAimEmitter(void)
{
}

CAimEmitter::~CAimEmitter(void)
{
}

void CAimEmitter::Emit( int nPosX, int nPosY, BulletType bulletType )
{
    float fAngle;
    int x = CPrincipalPlane::GetInstance()->GetX();
    int y = CPrincipalPlane::GetInstance()->GetY();
    fAngle = Unit::CalcAngle(nPosX, nPosY, x, y);

    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, fAngle);
}
 
void CAimEmitter::SetParam( bool bFriend, int nPower, int nSpeed )
{
    m_bFriend = bFriend;
    m_nPower = nPower;
    m_nSpeed = nSpeed;
}
