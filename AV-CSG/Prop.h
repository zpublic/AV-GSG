#pragma once
#include "Sprite.h"

class CProp : public CSprite
{
public:
    CProp(int x, int y);
    virtual ~CProp();

    virtual void Render(HDC hDC);
    virtual void Update();
    virtual bool IsVisible();

protected:
    int m_nStatus;
};
