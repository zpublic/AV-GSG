#pragma once
#include "Sprite.h"
#include "IEmitter.h"

typedef std::string PlaneType;

///> 飞机类基类
class PlaneBase : public CSprite
{
public:
    PlaneBase(int x, int y, IEmitter* piEmitter= NULL)
        : CSprite(x, y)
        , m_nHP(0)
        , m_piEmitter(piEmitter)
    {
    }
    virtual ~PlaneBase()
    {
        delete m_piEmitter;
    }

    //碰撞检测
    virtual bool CheckCollision(
        int x, int y,
        int width, int height,
        int power) = 0;

protected:
    int         m_nHP;      ///> 血量
    IEmitter*   m_piEmitter; ///> 子弹发射器
};