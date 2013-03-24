#pragma once
#include "IPlane.h"

///> 敌机类
class CEnemyPlane : public PlaneBase
{
public:
    CEnemyPlane(PlaneType enemyType, IEmitter* piEmitter, int nPosX = -1);
    virtual ~CEnemyPlane(void);

    //碰撞检测
    virtual bool CheckCollision(int x, int y, int width, int height, int power);

    virtual void Render(HDC hDC);
    virtual void Update();
    virtual bool IsVisible();


    CEnemyPlane * m_pEmnemyNext;

private:
    CEnemyPlane();
    std::string m_SkinType; ///> 飞机类型
    BulletType m_BulletType; ///> 子弹类型
    float   m_fFireTime;
    PlaneType   m_nEnemyType;
};
