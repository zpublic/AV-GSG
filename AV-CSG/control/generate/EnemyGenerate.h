#pragma once

#include "control\xml_parser\StageXMLStageObject.h"
#include <vector>
#include <list>
#include <algorithm>

typedef std::vector<CStageXMLEnemy*> EnemyList;

class CEnemyPlane;

class CEnemyGenerate
{
public:
    CEnemyGenerate(void);
    ~CEnemyGenerate(void);

    static bool IniEnemy(const CStageXMLStage* pStage);
    static void ClearEnemy();
    static void CreateEnemy(long lnTime);
    static void ReleaseEnemy(CEnemyPlane* pEnemy);

    static long EnemyNumber();

private:
    static EnemyList m_EnemyList;
public:
    static EnemyList::const_iterator m_spPosEnemyList;
    static CEnemyPlane *spEnemyHead;
    static long m_lnDeadPlane;
    static long m_ExclusionTime;
    static int m_IsVaild;
};

