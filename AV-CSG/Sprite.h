#pragma once

#include "ISprite.h"
#include "PicturePool.h"

class CSprite : public ISprite
{
public:
    //精灵位置
    CSprite(int	x, int y);
    virtual ~CSprite(void);

public:
    //判断精灵是否可见
    virtual bool IsVisible();

    //以下为设置和获取位置函数
    int GetX(){ return m_nPosX; }
    int GetY(){ return m_nPosY; }
    void SetX(int x){ m_nPosX = x; }
    void SetY(int y){ m_nPosY = y; }

protected:
    int     m_nPosX;
    int     m_nPosY;
    int     m_nFrameStartX;     //图片开始贴图的X坐标
    int     m_nCurrentFrame;    //当前帧
    int     m_nSpeed;           //精灵速度
    int     m_nFrameCount;      //帧数（如一类子弹有几张图）
    int     m_nWidth;
    int     m_nHeight;
    float   m_fAngle;
    bool    m_bIsVisible;
};

