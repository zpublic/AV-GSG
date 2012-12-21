#pragma once

#include "Bullet.h"

///> 大招
class CBigBullet : public CBullet
{
public:
    CBigBullet(int x, int y, BulletType bulletType, float angle);
    virtual ~CBigBullet(void);

    virtual void Update();
    virtual void Render(HDC hDC);
    virtual bool IsVisible();

private:
    int     m_nFrameStartY;     //图片开始贴图的Y坐标
};

