#include "stdafx.h"
#include "CurveEmitter.h"
#include "gameobject\bullet\CurveBullet.h"

CCurveEmitter::CCurveEmitter(void)
{
}

CCurveEmitter::~CCurveEmitter(void)
{
}

void CCurveEmitter::Emit( int nPosX, int nPosY, BulletType bulletType )
{
    new CCurveBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, m_fAngle);
}