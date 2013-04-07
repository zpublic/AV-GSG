#pragma once
#include "ISprite.h"
#include "data\resourcedata\PicturePool.h"

extern ISprite * g_pHead;

class CSpriteBase : public ISprite
{
public:
    //����λ��
    CSpriteBase(int x = 0, int y = 0);
    virtual ~CSpriteBase(void);

public:
    //�жϾ����Ƿ�ɼ�
    virtual bool IsVisible();

    //����Ϊ���úͻ�ȡλ�ú���
    int GetX(){ return m_nPosX; }
    int GetY(){ return m_nPosY; }
    void SetX(int x){ m_nPosX = x; }
    void SetY(int y){ m_nPosY = y; }

protected:
    int     m_nPosX;
    int     m_nPosY;
    int     m_nFrameStartX;     //ͼƬ��ʼ��ͼ��X����
    int     m_nCurrentFrame;    //��ǰ֡
    int     m_nSpeed;           //�����ٶ�
    int     m_nFrameCount;      //֡������һ���ӵ��м���ͼ��
    int     m_nWidth;
    int     m_nHeight;
    float   m_fAngle;
    bool    m_bIsVisible;
};

class CNoneSprit : public CSpriteBase
{
public:
    CNoneSprit(int x = 0, int y = 0) : CSpriteBase(x,y) {}
    virtual ~CNoneSprit() {}
};

class CSprite : public CSpriteBase
{
public:
    CSprite(int x = 0, int y = 0) : CSpriteBase(x,y)
    {
        this->pNext = g_pHead;
        g_pHead = static_cast<ISprite *>(this);
    }
    virtual ~CSprite() {}
};