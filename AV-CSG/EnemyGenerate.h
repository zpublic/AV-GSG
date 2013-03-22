#pragma once

#include "StageXMLStageObject.h"

class CEnemyPlane;

class CEnemyGenerate
{
public:
    CEnemyGenerate(void);
    ~CEnemyGenerate(void);

    static void CreateEnemy(const CStageXMLStage* pStage, long lnTime);
    static void ReleaseEnemy(CEnemyPlane* pEnemy);

    static long EnemyNumber();

public:
    static CEnemyPlane *spEnemyHead;
    static long m_lnDeadPlane;
};

