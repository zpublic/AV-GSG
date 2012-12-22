#pragma once

#include "IPlane.h"
#include "Picture.h"

///> µÐ»úÀà
class CEnemyPlane : public PlaneBase
{
public:
    CEnemyPlane(EnemyType enemyType);
    virtual ~CEnemyPlane(void);

    //Åö×²¼ì²â
    virtual bool CheckCollision(int x, int y, int width, int height, int power);

    virtual void Render(HDC hDC);
    virtual void Update();
    virtual bool IsVisible();

    static CEnemyPlane *spEnemyHead;
    CEnemyPlane * m_pEmnemyNext;

private:
    float   m_fFireTime;
    EnemyType   m_nEnemyType;
};
