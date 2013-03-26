#include "stdafx.h"
#include "EnemyGenerate.h"
#include "GameControler.h"
#include "EnemyPlane.h"
#include "EmitterGenerate.h"

CEnemyPlane * CEnemyGenerate::spEnemyHead = NULL;
long CEnemyGenerate::m_lnDeadPlane = 0;
long CEnemyGenerate::m_ExclusionTime = 0;
int CEnemyGenerate::m_IsVaild = 0;
EnemyList CEnemyGenerate::m_EnemyList;
EnemyList::const_iterator CEnemyGenerate::m_spPosEnemyList;

#define MAX_SCHEDULE 1000000000

CEnemyGenerate::CEnemyGenerate(void)
{
}

CEnemyGenerate::~CEnemyGenerate(void)
{
}

class EnemySort : public std::less<CStageXMLEnemy*>
{
public:
    bool operator ()(CStageXMLEnemy* lhs, CStageXMLEnemy* rhs)
    {
        if (lhs->GetAppear() < rhs->GetAppear())
        {
            return true;
        }
        return false;
    }
};

void CEnemyGenerate::CreateEnemy(long lnTime)
{
    if (lnTime > MAX_SCHEDULE)
    {
        return;
    }
    if ((m_ExclusionTime == lnTime) && (m_IsVaild == 0))
    {
        return;
    }
    else
    {
        m_IsVaild = 0;
    }
    if (m_spPosEnemyList == m_EnemyList.end())
    {
        return;
    }
    for (auto It = m_spPosEnemyList;
        It != m_EnemyList.end();
        It++)
    {
        if (((*It) != NULL) && ((*It)->GetAppear() == lnTime))
        {
            if ((*It)->GetAppear() > lnTime)
            {
                break;
            }
            CEnemyPlane* pEnemy = new CEnemyPlane(
                (*It)->GetType(),
                CEmitterGenerate::GenerateEnemyEmitter(),
                (*It)->GetPoint().PosX);
            pEnemy->m_pEmnemyNext = spEnemyHead;
            spEnemyHead = pEnemy;
            m_IsVaild = 1;
            It++;
            if (It != m_EnemyList.end())
            {
                m_spPosEnemyList = It;
            }
            It--;
        }
    }
    if (m_IsVaild == 0)
    {
        m_ExclusionTime = lnTime;
    }
}

bool CEnemyGenerate::IniEnemy(const CStageXMLStage* pStage)
{
    if (!pStage)
    {
        return false;
    }
    for (auto ItEnemy = pStage->EnemyBegin();
        ItEnemy != pStage->EnemyEnd(); ItEnemy++)
    {
        m_EnemyList.push_back(ItEnemy->second);
    }
    std::sort(m_EnemyList.begin(), m_EnemyList.end(), EnemySort());
    m_spPosEnemyList = m_EnemyList.begin();
    return true;
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
