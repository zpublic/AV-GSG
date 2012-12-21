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

    //碰撞检测
    virtual bool CheckCollision(int x, int y, int width, int height, int power);

    //渲染
    virtual void Render(HDC hDC);

    //更新精灵函数（位置，角度等属性）
    virtual void Update();

    //加载飞机图片和血量图片
    static void LoadBimap();
    static void FreeBitmap();

    BulletType GetBulletType(){ return m_nBulletType; }
    void SetBulletType(BulletType bulletType)
    {
        m_nBulletType = bulletType;
        if (m_nBulletType == emBulletTypeAMMO5 || m_nBulletType == emBulletTypeAMMO6)
        {
            SetAmmoCount(3);
        }
        if (m_nBulletType == emBulletTypeAmmoSB)
        {
            SetAmmoCount(5);
        }
    }

    void SetAmmoCount(int nAmmoCount){ m_nAmmoCount = nAmmoCount ;}

    void Control(ActionType actionType);

    static bool GetGameOver() { return m_emGameStatus == emGameStatusOver; }
    static bool GetGameReady() { return m_emGameStatus == emGameStatusReady; }
    static bool GetGameRuning() { return m_emGameStatus == emGameStatusRuning; }

    static void ClearGameStatus() { m_emGameStatus = emGameStatusNone; }
    static bool IsNeedUpdate() { return m_emGameStatus != emGameStatusNone; }
    static void StartGame() { m_emGameStatus = emGameStatusRuning; }
private:
    CPrincipalPlane(int x, int y);

    static CPrincipalPlane*     pCPrincipalPlane;
    static CPicture*            pPicturePlane;      //飞机图片
    static CPicture*            pPictureLife;       //生命图片
    static CPicture*            pPictureHP;
    static CPicture*            pPictureHPSide;
    BulletType                  m_nBulletType;
    int                         m_nHP;
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
    static GameStatus           m_emGameStatus;
};
