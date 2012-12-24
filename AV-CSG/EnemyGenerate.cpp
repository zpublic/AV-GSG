#include "stdafx.h"
#include "EnemyGenerate.h"
#include "GameControler.h"
#include "EnemyPlane.h"

float CEnemyGenerate::m_sfLastCreateTime = 0.0;
int CEnemyGenerate::m_snEnemyCount = 0;
CEnemyPlane * CEnemyGenerate::spEnemyHead = NULL;

CEnemyGenerate::CEnemyGenerate(void)
{
}

CEnemyGenerate::~CEnemyGenerate(void)
{
}

void CEnemyGenerate::CreateEnemy()
{
    m_sfLastCreateTime += CGameControler::GetInstance()->GetElapsedTime();
    if (m_sfLastCreateTime > 0.3f)//0.5秒产生一架敌机
    {
        if (m_snEnemyCount < 20)
        {
            CEnemyPlane* pEnemy = new CEnemyPlane((EnemyType)(rand() % 5));

            pEnemy->m_pEmnemyNext = spEnemyHead;
            spEnemyHead  = pEnemy;
            AddEnemyCount();
        }
        m_sfLastCreateTime -= 0.5f;
    }
}

void CEnemyGenerate::ReleaseEnemy(CEnemyPlane* pEnemy)
{
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
    SubEnemyCount();
}

int CEnemyGenerate::GetEnemyCount()
{
    return m_snEnemyCount;
}

void CEnemyGenerate::AddEnemyCount( int nNum /*= 1*/ )
{
    m_snEnemyCount += nNum;
}

void CEnemyGenerate::SubEnemyCount( int nNum /*= 1*/ )
{
    m_snEnemyCount -= nNum;
}
