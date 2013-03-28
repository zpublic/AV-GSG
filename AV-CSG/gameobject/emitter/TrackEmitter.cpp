#include "stdafx.h"
#include "TrackEmitter.h"
#include "gameobject\bullet\TrackBullet.h"
#include "gameobject\plane\SelfPlane.h"

CTrackEmitter::CTrackEmitter(void)
{
}

CTrackEmitter::~CTrackEmitter(void)
{
}

void CTrackEmitter::Emit( int nPosX, int nPosY, BulletType bulletType )
{
    float fAngle;
    if (m_bFriend)
    {
        fAngle = 1.5f * PI;
    }
    else
    {
        int x = CSelfPlane::GetInstance()->GetX();
        int y = CSelfPlane::GetInstance()->GetY();
        fAngle = Unit::CalcAngle(nPosX, nPosY, x, y);
    }

    new CTrackBullet(
        nPosX, nPosY,
        m_bFriend,
        bulletType, fAngle);
}
