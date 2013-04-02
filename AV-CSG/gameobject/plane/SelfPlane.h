#pragma once
#include "control/xml_parser/PlaneXMLObject.h"
#include "control/xml_parser/WeaponXMLParser.h"
#include "IPlane.h"

typedef std::string WeaponType;

///> 主控飞机类
class CSelfPlane : public PlaneBase
{
public:
    static CSelfPlane * GetInstance();
    virtual ~CSelfPlane();

    void InitGame(const CPlaneXMLObject* pPlane);

    virtual bool CheckCollision(int x, int y, int width, int height, int power);
    virtual void Render(HDC hDC);
    virtual void Update();

    void SetWeapon(WeaponType strWeaponType);

    void Control(ActionType actionType);

private:
    CSelfPlane(int x, int y);
    void InitPlane(int nHP);

private:
    static CSelfPlane*          pCSelfPlane;
    WeaponType                  m_WeaponType;
    int                         m_nLifes;
    int                         m_FirstHP;
    float                       m_fBulletFrequency;
    float                       m_fInvincibletime;  //无敌时间(单位秒)
    float                       m_fFrequencyTime;   //连续发射子弹时间(秒)
    bool                        m_bUnDead;
    bool                        m_bIsStopMove;
    bool                        m_bFire;
    int                         m_nWholeFired;      //全炸数量
    ActionType                  m_nAction;
    float                       m_fHpDot;
};
