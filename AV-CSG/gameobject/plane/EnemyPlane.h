#pragma once
#include "IPlane.h"

///> �л���
class CEnemyPlane : public PlaneBase
{
public:
    CEnemyPlane(PlaneType enemyType, IEmitter* piEmitter, int nPosX = -1);
    virtual ~CEnemyPlane(void);

    //��ײ���
    virtual bool CheckCollision(int x, int y, int width, int height, int power);

    virtual void Render(HDC hDC);
    virtual void Update();
    virtual bool IsVisible();


    CEnemyPlane * m_pEmnemyNext;

private:
    CEnemyPlane();
    std::string m_SkinType; ///> �ɻ�����
    BulletType m_BulletType; ///> �ӵ�����
    float   m_fFireTime;
    PlaneType   m_nEnemyType;
};
