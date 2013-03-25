#include "stdafx.h"
#include "EnemyCreateQueue.h"

#define CraeteQueueEnd -1

CEnemyCraeteQueue::CEnemyCraeteQueue()
    : m_ExclusionTime(CraeteQueueEnd)
{

}

CEnemyCraeteQueue::~CEnemyCraeteQueue()
{

}

bool CEnemyCraeteQueue::PushStage(const CStageXMLStage* pStage)
{
    if (!pStage)
    {
        return false;
    }
    for (auto ItEnemy = pStage->EnemyBegin();
        ItEnemy != pStage->EnemyEnd(); ItEnemy++)
    {
        m_spEnemyList.push_back(ItEnemy->second);
    }
    return true;
}

void CEnemyCraeteQueue::Push(CStageXMLEnemy* pStageEnemy)
{
    m_spEnemyList.push_back(pStageEnemy);
}

CEnemyPlane* CEnemyCraeteQueue::Pop()
{
    auto It = m_spEnemyList.cbegin();
    CEnemyPlane* pTmpEnemy = new CEnemyPlane(
            (*It)->GetType(),
            CEmitterGenerate::GenerateEnemyEmitter(),
            (*It)->GetPoint().PosX);
    m_spEnemyList.erase(It);
    return pTmpEnemy;
}

CEnemyPlane* CEnemyCraeteQueue::Pop(long lnTime)
{
    if (lnTime == m_ExclusionTime)
    {
        return NULL;
    }
    CEnemyPlane* pTmpEnemy = NULL;
    for (auto it  = m_spEnemyList.begin();
        it != m_spEnemyList.end();
        it++)
    {
        if ((*it)->GetAppear() == lnTime)
        {
            pTmpEnemy = new CEnemyPlane(
                (*it)->GetType(),
                CEmitterGenerate::GenerateEnemyEmitter(),
                (*it)->GetPoint().PosX);
            m_spEnemyList.erase(it);
            return pTmpEnemy;
        }
    }
    m_ExclusionTime = lnTime;
    return NULL;
}