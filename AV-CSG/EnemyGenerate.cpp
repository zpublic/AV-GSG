#include "stdafx.h"
#include "EnemyGenerate.h"
#include "GameControler.h"
#include "EnemyPlane.h"
#include "EmitterGenerate.h"

CEnemyPlane * CEnemyGenerate::spEnemyHead = NULL;
long CEnemyGenerate::m_lnDeadPlane = 0;
CEnemyCraeteQueue CEnemyGenerate::m_CreateQueue;

#define MAX_SCHEDULE 1000000000

CEnemyGenerate::CEnemyGenerate(void)
{
}

CEnemyGenerate::~CEnemyGenerate(void)
{
}

void CEnemyGenerate::CreateEnemy(long lnTime)
{
    if (lnTime > MAX_SCHEDULE)
    {
        return;
    }
    CEnemyPlane* pEnemy = m_CreateQueue.Pop(lnTime);
    if (!pEnemy)
    {
        return;
    }
    pEnemy->m_pEmnemyNext = spEnemyHead;
    spEnemyHead = pEnemy;
}

long CEnemyGenerate::EnemyNumber()
{
    return m_lnDeadPlane;
}

void CEnemyGenerate::ReleaseEnemy(CEnemyPlane* pEnemy)
{
    m_lnDeadPlane++;
    if (spEnemyHead == pEnemy)
    {
        spEnemyHead = pEnemy->m_pEmnemyNext;
    }
    else
    {
        CEnemyPlane* temp = spEnemyHead;
        for( ; temp->m_pEmnemyNext != NULL; temp = temp->m_pEmnemyNext)
        {
            if(temp->m_pEmnemyNext == pEnemy)
            {
                temp->m_pEmnemyNext = pEnemy->m_pEmnemyNext;
                break;
            }
        }
    }
}
