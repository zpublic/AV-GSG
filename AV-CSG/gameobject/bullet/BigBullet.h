#pragma once

#include "gameobject\sprite\Sprite.h"

///> 大招
class CBigBullet : public CSprite
{
public:
    CBigBullet(int x, int y);
    virtual ~CBigBullet(void);

    virtual void Update();
    virtual void Render(HDC hDC);
    virtual bool IsVisible();

private:
    int     m_nFrameStartY;     //图片开始贴图的Y坐标
};

