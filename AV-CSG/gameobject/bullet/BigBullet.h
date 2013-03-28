#pragma once

#include "gameobject\sprite\Sprite.h"

///> ����
class CBigBullet : public CSprite
{
public:
    CBigBullet(int x, int y);
    virtual ~CBigBullet(void);

    virtual void Update();
    virtual void Render(HDC hDC);
    virtual bool IsVisible();

private:
    int     m_nFrameStartY;     //ͼƬ��ʼ��ͼ��Y����
};

