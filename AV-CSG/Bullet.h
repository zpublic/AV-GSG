#pragma once
#include "Sprite.h"
#include "ExplosinXMLParser.h"

///> 子弹基类，划分为我方子弹和敌方子弹
class CBullet : public CSprite
{
public:
    CBullet(
        int x, int y,
        bool bFriend,
        BulletType bulletType,
        float fAngle);
    virtual ~CBullet(void);

    virtual bool IsVisible();
    virtual void Render(HDC hDC);
    virtual void Update();
protected:
    int                       m_nPower;           //威力
    const CExplosinXMLObject* m_Bullet;
    BulletType                m_BulletType;      //子弹类型
    bool                      m_bFriend;          //敌友
    int                       m_nSpeed;           //子弹速度
    float                     m_fAngle;           //角度
};

