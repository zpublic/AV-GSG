#include "EasyCustom.h"

CEasyCustom::CEasyCustom()
    : m_Id(0)
    , m_BossPlane_Ptr(NULL)
{
}

CEasyCustom::~CEasyCustom()
{
}

void CEasyCustom::SetName(const TString& strName)
{
    m_Name = strName;
}

const TString& CEasyCustom::GetName() const
{
    return m_Name;
}

void CEasyCustom::SetCustomId(int strName)
{
    m_Id = strName;
}

int CEasyCustom::GetCustomId() const
{
    return m_Id;
}

void CEasyCustom::SetEnemy(const EnemyList& vecEnemyList)
{
    m_vecEnemyList.clear();
    m_vecEnemyList.resize(vecEnemyList.size());
    std::copy(vecEnemyList.begin(), vecEnemyList.end(), m_vecEnemyList.begin());
}

EnemyList::const_iterator CEasyCustom::EnemyBegin() const
{
    return m_vecEnemyList.begin();
}

EnemyList::const_iterator CEasyCustom::EnemyEnd() const
{
    return m_vecEnemyList.end();
}

void CEasyCustom::SetEnemyBoss(const CEnemyPlane& epBoss)
{

}

const CEnemyPlane& CEasyCustom::GetEnemyBoss() const
{
    return *(m_BossPlane_Ptr);
}

bool CEasyCustom::IsBoss() const
{
    return m_IsBoss;
}

void CEasyCustom::MapBackgroud(const TString& lpszPath)
{
    m_strPath = lpszPath;
}