#include "stdafx.h"
#include "AimEmitter.h"
#include "gameobject\plane\SelfPlane.h"
#include "gameobject\bullet\Bullet.h"

CAimEmitter::CAimEmitter(void)
{
}

CAimEmitter::~CAimEmitter(void)
{
}

void CAimEmitter::Emit( int nPosX, int nPosY, BulletType bulletType )
{
    float fAngle;
    int x = CSelfPlane::GetInstance()->GetX();
    int y = CSelfPlane::GetInstance()->GetY();
    fAngle = Unit::CalcAngle(nPosX, nPosY, x, y);

    new CBullet(
        nPosX, nPosY,
        m_bFriend,
        bulletType, fAngle);
}
 
void CAimEmitter::SetParam( bool bFriend, int nPower, int nSpeed )
{
    m_bFriend = bFriend;
    m_nPower = nPower;
    m_nSpeed = nSpeed;
}
