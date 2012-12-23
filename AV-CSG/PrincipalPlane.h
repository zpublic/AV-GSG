#pragma once

#include "IPlane.h"
#include "Picture.h"

///> 主控飞机类
class CPrincipalPlane : public PlaneBase
{
public:
    static CPrincipalPlane * GetInstance();
    virtual ~CPrincipalPlane();

    void InitGame();

    virtual bool CheckCollision(int x, int y, int width, int height, int power);
    virtual void Render(HDC hDC);
    virtual void Update();

    void SetBulletType(BulletType bulletType);

    void Control(ActionType actionType);

private:
    CPrincipalPlane(int x, int y);
    void InitPlane();

private:
    static CPrincipalPlane*     pCPrincipalPlane;
    BulletType                  m_nBulletType;
    int                         m_nLife;
    float                       m_fBulletFrequency;
    float                       m_fInvincibletime;  //无敌时间(单位秒)
    float                       m_fFrequencyTime;   //连续发射子弹时间(秒)
    bool                        m_bUnDead;
    bool                        m_bIsStopMove;
    bool                        m_bFire;
    int                         m_nWholeFired;      //全炸数量
    ActionType                  m_nAction;
};
