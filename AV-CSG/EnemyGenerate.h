#pragma once

#include "StageXMLStageObject.h"
#include "EnemyCreateQueue.h"

class CEnemyPlane;

class CEnemyGenerate
{
public:
    CEnemyGenerate(void);
    ~CEnemyGenerate(void);

    static void CreateEnemy(long lnTime);
    static void ReleaseEnemy(CEnemyPlane* pEnemy);

    static long EnemyNumber();

public:
    static CEnemyPlane *spEnemyHead;
    static long m_lnDeadPlane;
    static CEnemyCraeteQueue m_CreateQueue;
};

