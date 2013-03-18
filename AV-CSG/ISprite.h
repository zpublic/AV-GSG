#pragma once

///> 精灵类的接口定义
class ISprite
{
public:
    ISprite() : pNext(NULL) {}
    virtual ~ISprite() {}

    //判断精灵是否可见
    virtual bool IsVisible() = 0;

    //渲染，即绘制函数
    virtual void Render(HDC hDC) = 0;

    //更新精灵函数（位置，角度等属性）
    virtual void Update() = 0;

    ISprite* pNext;
};