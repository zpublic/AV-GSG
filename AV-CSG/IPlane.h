#pragma once

#include "Sprite.h"

///> 飞机类基类
class PlaneBase : public CSprite
{
public:
    PlaneBase(int x, int y) : CSprite(x, y) {}
    virtual ~PlaneBase() {}

    //碰撞检测
    virtual bool CheckCollision(
        int x, int y,
        int width, int height,
        int power) = 0;

protected:
    int     m_nHP;
};