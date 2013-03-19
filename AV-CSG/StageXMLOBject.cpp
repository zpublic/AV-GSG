#include "stdafx.h"
#include "StageXMLObject.h"

CStageXMLOBject::CStageXMLOBject()
{
}

CStageXMLOBject::~CStageXMLOBject()
{
}

void CStageXMLOBject::SetName(const std::string& strName)
{
    m_Name = strName;
}

const std::string& CStageXMLOBject::GetName() const
{
    return m_Name;
}

void CStageXMLOBject::SetId(const std::string& strId)
{
    m_Id = strId;
}

std::string CStageXMLOBject::GetId() const
{
    return m_Id;
}

void CStageXMLOBject::SetType(const std::string& strType)
{
    m_Type = strType;
}

const std::string& CStageXMLOBject::GetType() const
{
    return m_Type;
}