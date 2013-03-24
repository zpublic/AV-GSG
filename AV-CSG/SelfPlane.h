#pragma once
#include "PlaneXMLObject.h"
#include "IPlane.h"

///> ���طɻ���
class CSelfPlane : public PlaneBase
{
public:
    static CSelfPlane * GetInstance();
    virtual ~CSelfPlane();

    void InitGame(const CPlaneXMLObject* pPlane);

    virtual bool CheckCollision(int x, int y, int width, int height, int power);
    virtual void Render(HDC hDC);
    virtual void Update();

    void SetBulletType(BulletType bulletType);

    void Control(ActionType actionType);
    void GetInput();

private:
    CSelfPlane(int x, int y);
    void InitPlane(int nHP);

private:
    static CSelfPlane*          pCSelfPlane;
    BulletType                  m_nBulletType;
    int                         m_nLifes;
    int                         m_FirstHP;
    float                       m_fBulletFrequency;
    float                       m_fInvincibletime;  //�޵�ʱ��(��λ��)
    float                       m_fFrequencyTime;   //���������ӵ�ʱ��(��)
    bool                        m_bUnDead;
    bool                        m_bIsStopMove;
    bool                        m_bFire;
    int                         m_nWholeFired;      //ȫը����
    ActionType                  m_nAction;
};
