#include "stdafx.h"
#include "ExplosinXMLParser.h"

CExplosinXMLParse CExplosinXMLParse::m_Explosin;

CExplosinXMLParse& CExplosinXMLParse::GetInstance()
{
    return m_Explosin;
}

CExplosinXMLParse::CExplosinXMLParse()
{
}

CExplosinXMLParse::~CExplosinXMLParse()
{
    _Close();
}

const CExplosinXMLObject* CExplosinXMLParse::Get(const std::string& strId) const
{
    auto it = m_mapExplosin.find(strId);
    if (it == m_mapExplosin.end())
    {
        return NULL;
    }
    return it->second;
}


void CExplosinXMLParse::_Close()
{
    if (!m_mapExplosin.empty())
    {
        for (auto it = m_mapExplosin.begin(); it != m_mapExplosin.end(); it++)
        {
            delete it->second;
        }
    }
}

const int CExplosinXMLParse::Size() const
{
    return m_mapExplosin.size();
}


bool CExplosinXMLParse::LoadXML(const std::string& strPath)
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

bool CExplosinXMLParse::_Parse(TiXmlDocument& TinyXML)
{
    TiXmlElement* tiRoot = TinyXML.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != EXPLOSIN_ROOT_GAME)
    {
        return false;
    }

    TiXmlNode* tiFirst = tiRoot->FirstChild(EXPLOSIN_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }
    for (TiXmlElement* tiElement = tiFirst->ToElement();
        tiElement != NULL;
        tiElement = tiElement->NextSiblingElement())
    {
        CExplosinXMLObject* pExplosion = new CExplosinXMLObject;
        if (tiElement->Attribute(ID_OBJECT) != NULL)
        {
            pExplosion->SetId(tiElement->Attribute(ID_OBJECT));
        }
        if (tiElement->Attribute(NAME_OBJECT) != NULL)
        {
            pExplosion->SetName(tiElement->Attribute(NAME_OBJECT));
        }
        if (tiElement->Attribute(PLANE_SKIN_OBJECT) != NULL)
        {
            pExplosion->SetSkinId(tiElement->Attribute(PLANE_SKIN_OBJECT));
        }
        if (tiElement->Attribute(EXPLOSIN_POWER_GAME) != NULL)
        {
            pExplosion->SetPower(::atol(tiElement->Attribute(EXPLOSIN_POWER_GAME)));
        }
        if (tiElement->Attribute(EXPLOSIN_SPEED_GAME) != NULL)
        {
            pExplosion->SetSpeed(::atoi(tiElement->Attribute(EXPLOSIN_SPEED_GAME)));
        }
        if (tiElement->Attribute(TYPE_OBJECT) != NULL)
        {
            pExplosion->SetType(tiElement->Attribute(TYPE_OBJECT));
        }
        m_mapExplosin[pExplosion->GetId()] = pExplosion;
    }
    return true;
}