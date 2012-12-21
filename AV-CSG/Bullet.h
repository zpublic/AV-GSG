#pragma once
#include "Sprite.h"
#include "Picture.h"

///> 子弹基类，划分为我方子弹和敌方子弹
class CBullet : public CSprite
{
public:
    CBullet(int x, int y);
    virtual ~CBullet(void);

    bool IsVisible();
protected:
    int                 m_nPower;           //威力
    BulletType          m_nBulletType;      //子弹类型
};

