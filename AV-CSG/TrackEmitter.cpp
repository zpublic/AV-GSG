#include "stdafx.h"
#include "TrackEmitter.h"
#include "TrackBullet.h"
#include "PrincipalPlane.h"

CTrackEmitter::CTrackEmitter(void)
{
}

CTrackEmitter::~CTrackEmitter(void)
{
}

void CTrackEmitter::Emit( int nPosX, int nPosY, BulletType bulletType )
{
    float fAngle;
    int x = CPrincipalPlane::GetInstance()->GetX();
    int y = CPrincipalPlane::GetInstance()->GetY();
    fAngle = Unit::CalcAngle(nPosX, nPosY, x, y);

    new CTrackBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, fAngle);
}
