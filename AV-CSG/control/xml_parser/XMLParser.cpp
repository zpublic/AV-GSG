#include "stdafx.h"
#include "XMLParser.h"

CXMLParser::CXMLParser()
{
}

CXMLParser::~CXMLParser()
{
}

bool CXMLParser::BaseParse(CXMLObject* xmlobj, TiXmlElement* tiElement)
{
    if (!xmlobj || !tiElement)
    {
        return false;
    }
    std::string strId;
    std::string strName;
    std::string strType;
    if (Unit::GetXmlStrAttributeA(tiElement, ID_OBJECT, strId))
    {
        Unit::GetXmlStrAttributeA(tiElement, NAME_OBJECT, strName);
        Unit::GetXmlStrAttributeA(tiElement, TYPE_OBJECT, strType);
        xmlobj->SetId(strId);
        xmlobj->SetName(strName);
        xmlobj->SetType(strType);
        return true;
    }
    return false;
}

bool CXMLParser::BasePos(PosObject* posobj, TiXmlElement* tiElement)
{
    if (!posobj || !tiElement)
    {
        return false;
    }
    //Unit::GetXmlIntAttribute(posobj->PosX, , )
    return false;
}