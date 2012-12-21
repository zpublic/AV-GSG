#pragma once
#include "Sprite.h"
#include "Picture.h"

///> 子弹基类，划分为我方子弹和敌方子弹
class CBullet : public CSprite
{
public:
    CBullet(
        int x, int y,
        bool bFriend,
        int nPower,
        int nSpeed,
        BulletType bulletType,
        float fAngle);
    virtual ~CBullet(void);

    virtual bool IsVisible();
    virtual void Render(HDC hDC);
    virtual void Update();
protected:
    int                 m_nPower;           //威力
    BulletType          m_nBulletType;      //子弹类型
    bool                m_bFriend;          //敌友
    int                 m_nSpeed;           //子弹速度
    float               m_fAngle;           //角度
};

