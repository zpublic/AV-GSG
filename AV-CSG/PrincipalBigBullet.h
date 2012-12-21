#pragma once

#include "PrincipalBullet.h"

///> 大招
class CPrincipalBigBullet : public CPrincipalBullet
{
public:
    CPrincipalBigBullet(int x, int y, BulletType bulletType, float angle);
    virtual ~CPrincipalBigBullet(void);

    virtual void Update();
    virtual void Render(HDC hDC);
    virtual bool IsVisible();

private:
    int     m_nFrameStartY;     //图片开始贴图的Y坐标
};

