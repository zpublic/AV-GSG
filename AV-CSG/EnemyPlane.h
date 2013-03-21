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
    int m_nSkinType; ///> 飞机类型
    int m_nBulletType; ///> 子弹类型
    float   m_fFireTime;
    EnemyType   m_nEnemyType;
};
