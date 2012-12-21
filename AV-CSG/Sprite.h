#pragma once

#include "ISprite.h"

class CSprite : public ISprite
{
public:
    //精灵位置
    CSprite(int	x, int y);
    virtual ~CSprite(void);

    //刷新一帧画面
    static void FrameRender(HDC hDC);

    //统一更新帧数据
    static void FrameUpdate();

public:
    //判断精灵是否可见
    virtual bool IsVisible();

    //渲染，即绘制函数
    virtual void Render(HDC hDC) = 0;

    //更新精灵函数（位置，角度等属性）
    virtual void Update() = 0;

    //以下为设置和获取位置函数
    int GetX(){ return m_nPosX; }
    int GetY(){ return m_nPosY; }
    void SetX(int x){ m_nPosX = x; }
    void SetY(int y){ m_nPosY = y; }

protected:
    int     m_nPosX;
    int     m_nPosY;
    int     m_nFrameStartX;     //当前帧，图片开始贴图的X坐标
    int     m_nSpeed;           //精灵速度
    int     m_nFrameCount;      //帧数（如一类子弹有几张图）
    int     m_nCurrentFrame;
    int     m_nWidth;
    int     m_nHeight;
    float   m_fAngle;
    bool    m_bIsVisible;
    static CSprite* g_pHead;
    CSprite* pNext;
};

