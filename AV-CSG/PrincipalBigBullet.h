#pragma once

#include "PrincipalBullet.h"

///> ¥Û’–
class CPrincipalBigBullet : public CPrincipalBullet
{
public:
    CPrincipalBigBullet(int x, int y, BulletType bulletType, float angle);
    virtual ~CPrincipalBigBullet(void);

    void Update();
    bool IsVisible();
};

