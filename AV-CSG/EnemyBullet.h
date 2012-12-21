#pragma once

#include "Bullet.h"

///> µÐ·½×Óµ¯
class CEnemyBullet : public CBullet
{
public:
    CEnemyBullet(int x, int y, BulletType bulletType, float angle);
    virtual ~CEnemyBullet(void);

    void Update();
};
