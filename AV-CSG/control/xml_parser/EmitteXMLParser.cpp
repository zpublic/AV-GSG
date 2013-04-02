#include "stdafx.h"
#include "EmitterXMLParser.h"

CEmitterXMLParse* Singleton<CEmitterXMLParse>::m_pInst = NULL;

CEmitterXMLParse::CEmitterXMLParse()
{
}

CEmitterXMLParse::~CEmitterXMLParse()
{
}

bool CEmitterXMLParse::Initialize()
{
    return true;
}

bool CEmitterXMLParse::LoadXML(const std::string& strPath)
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

const CEmitterXMLObject* CEmitterXMLParse::Get(const std::string& strId) const
{
    auto it = m_mapEmitter.find(strId);
    if (it == m_mapEmitter.end())
    {
        return NULL;
    }
    return it->second;
}

bool CEmitterXMLParse::_Parse(TiXmlDocument& TinyXML)
{
    TiXmlElement* tiRoot = TinyXML.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != EMITTER_ROOT_GAME)
    {
        return false;
    }

    TiXmlNode* tiFirst = tiRoot->FirstChild(EMITTER_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }
    for (TiXmlElement* tiElement = tiFirst->ToElement();
        tiElement != NULL;
        tiElement = tiElement->NextSiblingElement())
    {
        CEmitterXMLObject* pEmitter = new CEmitterXMLObject;
        if (tiElement->Attribute(ID_OBJECT) != NULL)
        {
            pEmitter->SetId(tiElement->Attribute(ID_OBJECT));
        }
        if (tiElement->Attribute(NAME_OBJECT) != NULL)
        {
            pEmitter->SetName(tiElement->Attribute(NAME_OBJECT));
        }
        if (tiElement->Attribute(TYPE_OBJECT) != NULL)
        {
            pEmitter->SetType(tiElement->Attribute(TYPE_OBJECT));
        }
        m_mapEmitter[pEmitter->GetId()] = pEmitter;
    }
    return true;
}