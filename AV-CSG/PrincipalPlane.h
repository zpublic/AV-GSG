#pragma once

#include "IPlane.h"
#include "Picture.h"

///> 主控飞机类
class CPrincipalPlane : public PlaneBase
{
public:
    //控制生成单例
    static CPrincipalPlane * GetInstance();
    virtual ~CPrincipalPlane();

    //初始化飞机，包括血量的更新
    void InitPlane();

    virtual bool CheckCollision(int x, int y, int width, int height, int power);

    virtual void Render(HDC hDC);
    virtual void Update();

    //加载飞机图片和血量图片
    static void LoadBimap();
    static void FreeBitmap();

    BulletType GetBulletType();
    void SetBulletType(BulletType bulletType);
    void SetAmmoCount(int nAmmoCount);

    void Control(ActionType actionType);
private:
    CPrincipalPlane(int x, int y);

    static CPrincipalPlane*     pCPrincipalPlane;
    static CPicture*            pPicturePlane;      //飞机图片
    static CPicture*            pPictureLife;       //生命图片
    static CPicture*            pPictureHP;
    static CPicture*            pPictureHPSide;
    BulletType                  m_nBulletType;
    int                         m_nLife;
    float                       m_fBulletFrequency;
    float                       m_fInvincibletime;  //无敌时间(单位秒)
    int                         m_nAmmoCount;       //每次发射子弹数量
    float                       m_fFrequencyTime;   //连续发射子弹时间(秒)
    bool                        m_bUnDead;
    bool                        m_bIsStopMove;
    bool                        m_bFire;
    int                         m_nWholeFired;      //全炸数量
    ActionType                  m_nAction;
};
