#pragma once
#include "IPlane.h"

///> µÐ»úÀà
class CEnemyPlane : public PlaneBase
{
public:
    CEnemyPlane(EnemyType enemyType, IEmitter* piEmitter, int nPosX = -1);
    virtual ~CEnemyPlane(void);

    //Åö×²¼ì²â
    virtual bool CheckCollision(int x, int y, int width, int height, int power);

    virtual void Render(HDC hDC);
    virtual void Update();
    virtual bool IsVisible();

    CEnemyPlane * m_pEmnemyNext;

private:
    CEnemyPlane();

    float   m_fFireTime;
    EnemyType   m_nEnemyType;
};
