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
    Unit::GetXmlIntAttribute(tiElement, POSX_OBJECT, posobj->PosX);
    Unit::GetXmlIntAttribute(tiElement, POSY_OBJECT, posobj->PosY);
    return true;
}

bool CXMLParser::BaseShape(ShapeObject* shapeobj, TiXmlElement* tiElement)
{
    if (!shapeobj || !tiElement)
    {
        return false;
    }
    Unit::GetXmlIntAttribute(tiElement, WIDTH_OBJCET, shapeobj->nWidth);
    Unit::GetXmlIntAttribute(tiElement, HEIGHT_OBJECT, shapeobj->nHeight);
    return true;
}