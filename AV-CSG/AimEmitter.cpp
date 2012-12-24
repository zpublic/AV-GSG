#include "stdafx.h"
#include "AimEmitter.h"
#include "PrincipalPlane.h"
#include "Bullet.h"
#include "math.h"

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

    if (nPosX == x)
    {
        if (nPosY > y)
            fAngle = PI * 0.5;
        else
            fAngle = PI * 1.5;
    }
    else if (nPosY == y)
    {
        if (nPosX > x)
            fAngle = 0;
        else
            fAngle = PI;
    }
    else
    {
        float Result = atan((float)(nPosY - y) / (nPosX - x));
        if ((x < nPosX) && (y > nPosY))
            fAngle = Result + PI;
        else if ((x < nPosX) && (y < nPosY))
            fAngle = Result + PI;
        else if ((x > nPosX) && (y < nPosY))
            fAngle = Result + 2 * PI;
        else 
            fAngle = Result;
    }

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
