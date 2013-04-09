#include "stdafx.h"
#include "xmlresource.h"

CXMLResource::CXMLResource()
{
}

CXMLResource::~CXMLResource()
{
}

int CXMLResource::LoadXML(const std::string& strPath)
{
    TiXmlDocument XmlParse;

    if (strPath.empty())
    {
        return false;
    }

    if (XmlParse.LoadFile(strPath.c_str()))
    {
        return _Parse(XmlParse);
    }
    return true;
}

int CXMLResource::_Parse(TiXmlDocument& tiDoc)
{
    TiXmlElement* tiRoot = tiDoc.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != XMLLIST_ROOT)
    {
        return false;
    }

    TiXmlNode* tiFirst = tiRoot->FirstChild(XMLLIST_XML);
    if (tiFirst == NULL)
    {
        return false;
    }
    for (TiXmlElement* tiElement = tiFirst->ToElement();
        tiElement != NULL;
        tiElement = tiElement->NextSiblingElement())
    {
        std::string strPath;
        std::string strType;
        if (Unit::GetXmlStrAttributeA(tiElement, XMLLIST_PATH, strPath)
            && Unit::GetXmlStrAttributeA(tiElement, TYPE_OBJECT, strType))
        {
            m_mapXMLList[strType] = strPath;
        }
    }
    return true;
}