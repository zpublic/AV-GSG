#include "stdafx.h"
#include "XMLObject.h"

CXMLObject::CXMLObject()
{
}

CXMLObject::~CXMLObject()
{
}

void CXMLObject::SetName(const std::string& strName)
{
    m_Name = strName;
}

const std::string& CXMLObject::GetName() const
{
    return m_Name;
}

void CXMLObject::SetId(const std::string& strId)
{
    m_Id = strId;
}

std::string CXMLObject::GetId() const
{
    return m_Id;
}

void CXMLObject::SetType(const std::string& strType)
{
    m_Type = strType;
}

const std::string& CXMLObject::GetType() const
{
    return m_Type;
}