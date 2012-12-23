#pragma once
#include "Bullet.h"

///> ÇúÏß×Óµ¯
class CCurveBullet : public CBullet
{
public:
    CCurveBullet(
        int x, int y,
        bool bFriend,
        int nPower,
        int nSpeed,
        BulletType bulletType,
        float fAngle);
    virtual ~CCurveBullet(void);

    virtual void Update();

private:
    int m_nStatus;
};

