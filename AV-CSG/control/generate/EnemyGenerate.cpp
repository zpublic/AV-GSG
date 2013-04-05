#include "stdafx.h"
#include "EnemyGenerate.h"
#include "control/game/GameControler.h"
#include "gameobject\plane\EnemyPlane.h"
#include "control\xml_parser\BulletXMLParser.h"
#include "control\xml_parser\WeaponXMLParser.h"
#include "control\xml_parser\EmitterXMLParser.h"
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
            CPlaneXMLParse& pPlaneXML = CPlaneXMLParse::GetInstance();
            const CWeaponXMLObject* pWeaponXML = CWeaponXMLParse::Instance()->Get(pPlaneXML.GetEnemyPlane((*It)->GetType())->GetWeapon());
            if (!pWeaponXML)
            {
                return;
            }
            const CBulletXMLObject* pBullet = CBulletXMLParse::GetInstance().Get(pWeaponXML->GetBulletType());
            if (!pBullet)
            {
                return;
            }
            const CEmitterXMLObject* pEmitterXML = CEmitterXMLParse::Instance()->Get(pWeaponXML->GetEmitter());
            if (!pEmitterXML)
            {
                return;
            }
            IEmitter* pEmitter = CEmitterGenerate::GenerateEnemyEmitter(
                pEmitterXML->GetType(),
                false,
                pBullet->GetSpeed(),
                pBullet->GetPower(),
                0);
            if (!pEmitter)
            {
                return;
            }
            CEnemyPlane* pEnemy = new CEnemyPlane(
                (*It)->GetType(),
                pEmitter,
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

void CEnemyGenerate::ClearEnemy()
{
    m_EnemyList.clear();
    m_lnDeadPlane = 0;
    m_spPosEnemyList = m_EnemyList.end();
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
