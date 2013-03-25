#ifndef ENEMY_CREATEQUEUE_
#define ENEMY_CREATEQUEUE_

#include "StageXMLParser.h"
#include "EnemyPlane.h"
#include "EmitterGenerate.h"
#include <vector>

typedef std::vector<std::pair<long, CEnemyPlane*> > vecEnemyList;

class CEnemyCraeteQueue
{
public:
    CEnemyCraeteQueue();
    virtual ~CEnemyCraeteQueue();

    bool PushStage(const CStageXMLStage* pStage);

    void Push(CStageXMLEnemy* pStageEnemy);

    CEnemyPlane* Pop();

    CEnemyPlane* Pop(long lnTime);

    long PresentNumbe() const;

private:
    std::vector<CStageXMLEnemy*> m_spEnemyList;
    long m_ExclusionTime;
};

#endif