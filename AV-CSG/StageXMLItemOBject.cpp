#include "stdafx.h"
#include "StageXMLItemOBject.h"

CStageXMLItem::CStageXMLItem()
    : m_Way(0)
    , m_Number(0)
{
}

CStageXMLItem::CStageXMLItem(const std::string& strWay)
{
    m_Way = strWay;
}

CStageXMLItem::~CStageXMLItem()
{
}

void CStageXMLItem::SetNumber(long lnNumber)
{
    m_Number = lnNumber;
}

long CStageXMLItem::GetNumber() const
{
    return m_Number;
}

const std::string& CStageXMLItem::Way()
{
    return m_Way;
}

void CStageXMLItem::SetPoint(int iPosX, int iPosY)
{
    m_Point.SetPoint(iPosX, iPosY);
}

void CStageXMLItem::SetPoint(const PosObject& pos)
{
    m_Point.SetPoint(pos.PosX, pos.PosY);
}

const PosObject& CStageXMLItem::GetPoint() const
{
    return m_Point;
}