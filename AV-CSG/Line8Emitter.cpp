#include "stdafx.h"
#include "Line8Emitter.h"
#include "Bullet.h"

CLine8Emitter::CLine8Emitter(void)
{
}

CLine8Emitter::~CLine8Emitter(void)
{
}

void CLine8Emitter::Emit( int nPosX, int nPosY, BulletType bulletType )
{
    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, float(0*PI/4.0));
    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, float(1*PI/4.0));
    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, float(2*PI/4.0));
    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, float(3*PI/4.0));
    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, float(4*PI/4.0));
    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, float(5*PI/4.0));
    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, float(6*PI/4.0));
    new CBullet(
        nPosX, nPosY,
        m_bFriend, m_nPower, m_nSpeed,
        bulletType, float(7*PI/4.0));
}

void CLine8Emitter::SetParam( bool bFriend, int nPower, int nSpeed )
{
    m_bFriend = bFriend;
    m_nPower = nPower;
    m_nSpeed = nSpeed;
}
