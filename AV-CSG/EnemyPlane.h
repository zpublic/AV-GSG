#pragma once

#include "IPlane.h"
#include "Picture.h"

///> 敌机类
class CEnemyPlane : public PlaneBase
{
public:
    CEnemyPlane(EnemyType enemyType);
    virtual ~CEnemyPlane(void);

    //碰撞检测
    virtual bool CheckCollision(int x, int y, int width, int height, int power);

    static void CreateEnemy();

    //渲染
    virtual void Render(HDC hDC);

    //更新精灵函数（位置，角度等属性）
    virtual void Update();

    //加载飞机图片
    static void LoadBimap();
    static void FreeBitmap();

    bool IsVisible();

    static CEnemyPlane *spEnemyHead;
    CEnemyPlane * m_pEmnemyNext;

private:
    static int snEnemyCount;
    static float sfLastCreateTime;
    float   m_fFireTime;
    int     m_nHP;
    EnemyType   m_nEnemyType;
};
