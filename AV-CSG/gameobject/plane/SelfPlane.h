#pragma once
#include "control/xml_parser/PlaneXMLObject.h"
#include "control/xml_parser/WeaponXMLParser.h"
#include "control\generate\EmitterGenerate.h"
#include "IPlane.h"

///> ���طɻ���
class CSelfPlane : public SelfPlaneBase
{
public:
    static CSelfPlane * GetInstance();
    virtual ~CSelfPlane();

    void InitGame(const CPlaneXMLObject* pPlane);

    virtual bool CheckCollision(int x, int y, int width, int height, int power);
    virtual void Render(HDC hDC);
    virtual void Update();

    void SetWeapon(
        EmitterType strType,
        bool bFriend,
        int nPower,
        int nSpeed);

    void Control(ActionType actionType);

private:
    CSelfPlane(int x, int y);
    void InitPlane(int nHP);

private:
    static CSelfPlane*          pCSelfPlane;
    std::string                 m_WeaponType;
    int                         m_FirstHP;
    float                       m_fBulletFrequency;
    float                       m_fInvincibletime;  //�޵�ʱ��(��λ��)
    float                       m_fFrequencyTime;   //���������ӵ�ʱ��(��)
    bool                        m_bUnDead;
    bool                        m_bIsStopMove;
    bool                        m_bFire;
    int                         m_nWholeFired;      //ȫը����
    ActionType                  m_nAction;
    float                       m_fHpDot;
};
