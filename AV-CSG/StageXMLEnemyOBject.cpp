#include "stdafx.h"
#include "StageXMLEnemyOBject.h"

CStageXMLEnemy::CStageXMLEnemy()
    : m_Appear(0)
{
}

CStageXMLEnemy::~CStageXMLEnemy()
{
    _Close();
}

void CStageXMLEnemy::_Close()
{
    if (!m_mapItem.empty())
    {
        for (auto it = m_mapItem.begin(); it != m_mapItem.end(); it++)
        {
            delete it->second;
        }
    }
}

bool CStageXMLEnemy::PushItem(CStageXMLItem* sItemObject)
{
    if (!sItemObject)
    {
        return false;
    }
    if (sItemObject->GetId() == "")
    {
        return false;
    }
    m_mapItem[sItemObject->GetId()] = sItemObject;
    return true;
}

const ItemObejctMap::const_iterator CStageXMLEnemy::Begin() const
{
    return m_mapItem.begin();
}

const ItemObejctMap::const_iterator CStageXMLEnemy::End() const
{
    return m_mapItem.end();
}

void CStageXMLEnemy::SetPoint(int iPosX, int iPosY)
{
    m_Point.SetPoint(iPosX, iPosY);
}

void CStageXMLEnemy::SetPoint(const PosObject& pos)
{
    m_Point.SetPoint(pos.PosX, pos.PosY);
}

const PosObject& CStageXMLEnemy::GetPoint() const
{
    return m_Point;
}

bool CStageXMLEnemy::SetItem(const std::string& strId,CStageXMLItem* sItemObject)
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

const CStageXMLItem* CStageXMLEnemy::GetItem(const std::string& strId) const
{
    auto it = m_mapItem.find(strId);
    if (it == m_mapItem.end())
    {
        return NULL;
    }
    return it->second;
}

void CStageXMLEnemy::SetAppear(long lnAppear)
{
    m_Appear = lnAppear;
}
const long CStageXMLEnemy::GetAppear() const
{
    return m_Appear;
}

void CStageXMLEnemy::SetBind(const std::string& strBind)
{
    m_Bind = strBind;
}

const std::string& CStageXMLEnemy::GetBind() const
{
    return m_Bind;
}