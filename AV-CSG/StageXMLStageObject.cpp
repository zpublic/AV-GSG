#include "stdafx.h"
#include "StageXMLStageObject.h"

CStageXMLStage::CStageXMLStage()
    : m_Difficulty(0)
    , m_Boss(0)
{
}

CStageXMLStage::~CStageXMLStage()
{
    _Close();
}

void CStageXMLStage::_Close()
{
    if (!m_mapItem.empty())
    {
        for (auto it = m_mapItem.begin(); it != m_mapItem.end(); it++)
        {
            delete it->second;
        }
    }
    if (!m_mapEnemy.empty())
    {
        for (auto it = m_mapEnemy.begin(); it != m_mapEnemy.end(); it++)
        {
            delete it->second;
        }
    }
}

bool CStageXMLStage::PushEnemy(CStageXMLEnemy* sEnemyObject)
{
    if (!sEnemyObject)
    {
        return false;
    }
    m_mapEnemy[sEnemyObject->GetId()] = sEnemyObject;
    return true;
}

const EnemyObejctMap::const_iterator CStageXMLStage::EnemyBegin() const
{
    return m_mapEnemy.begin();
}

const EnemyObejctMap::const_iterator CStageXMLStage::EnemyEnd() const
{
    return m_mapEnemy.end();
}

bool CStageXMLStage::PushItem(CStageXMLItem* sItemObject)
{
    if (!sItemObject)
    {
        return false;
    }
    m_mapItem[sItemObject->GetId()] = sItemObject;
    return true;
}

const ItemObejctMap::const_iterator CStageXMLStage::ItemBegin() const
{
    return m_mapItem.begin();
}

const ItemObejctMap::const_iterator CStageXMLStage::ItemEnd() const
{
    return m_mapItem.end();
}

void CStageXMLStage::SetMap(const std::string& strMap)
{
    m_MapPath = strMap;
}

const std::string& CStageXMLStage::GetMap() const
{
    return m_MapPath;
}

void CStageXMLStage::SetDifficulty(long lnMap)
{
    m_Difficulty = lnMap;
}

const long CStageXMLStage::GetDifficulty() const
{
    return m_Difficulty;
}

bool CStageXMLStage::SetItem(const std::string& strId, CStageXMLItem* sItemObject)
{
    auto it = m_mapItem.find(strId);
    if (it == m_mapItem.end() && sItemObject != NULL)
    {
        return false;
    }
    delete it->second;
    it->second = sItemObject;
    return true;
}

CStageXMLItem* CStageXMLStage::GetItem(const std::string& strId) const
{
    auto it = m_mapItem.find(strId);
    if (it == m_mapItem.end())
    {
        return NULL;
    }
    return it->second;
}