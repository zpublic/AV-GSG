#include "stdafx.h"
#include "EnemyGenerate.h"
#include "GameControler.h"
#include "EnemyPlane.h"

long CEnemyGenerate::m_Schedule = 0;
CEnemyPlane * CEnemyGenerate::spEnemyHead = NULL;

#define MAX_SCHEDULE 1000000000

CEnemyGenerate::CEnemyGenerate(void)
{
}

CEnemyGenerate::~CEnemyGenerate(void)
{
}

void CEnemyGenerate::CreateEnemy()
{
    if (m_Schedule > MAX_SCHEDULE)
    {
        return;
    }
    m_Schedule++;
    CStageXMLParse& XmlParse = CStageXMLParse::GetInstance();
    for (auto it = XmlParse.Begin(); it != XmlParse.End(); it++)
    {
        if (XmlParse.Get("1") != NULL)
        {
            for (auto ItEnemy = XmlParse.Get("1")->EnemyBegin();
                ItEnemy != XmlParse.Get("1")->EnemyEnd(); ItEnemy++)
            {
                if (ItEnemy->second->GetAppear() == m_Schedule)
                {
                    CEnemyPlane* pEnemy = new CEnemyPlane((EnemyType)(1),
                    ItEnemy->second->GetPoint().PosX);
                    pEnemy->m_pEmnemyNext = spEnemyHead;
                    spEnemyHead = pEnemy;
                }
            }
        }
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
}
