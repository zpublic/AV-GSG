#include "stdafx.h"
#include "xmlresource.h"

CXMLResource* Singleton<CXMLResource>::m_pInst = NULL;

CXMLResource::CXMLResource()
{
}

CXMLResource::~CXMLResource()
{
}

bool CXMLResource::Initialize()
{
    return true;
}

bool CXMLResource::LoadXML(const std::string& strPath)
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

bool CXMLResource::_LoadGameXML(mapXMLList& mapXMLList)
{
    for (auto it = mapXMLList.begin(); it != mapXMLList.end(); it++)
    {
        char filePath[MAX_PATH] = {0};
        ::GetModuleFileNameA(0, filePath, MAX_PATH);
        ::PathRemoveFileSpecA(filePath);
        ::PathAppendA(filePath, it->second.c_str());
        if (it->first == PLANE_ROOT_GAME)
        {
            CPlaneXMLParse::GetInstance().LoadXML(filePath);
        }
        if (it->first == BLAST_ROOT_GAME)
        {
            CBlastXMLParse::Instance()->LoadXML(filePath);
        }
        if (it->first == BULLET_ROOT_GAME)
        {
            CBulletXMLParse::GetInstance().LoadXML(filePath);
        }
        if (it->first == EMITTER_ROOT_GAME)
        {
            CEmitterXMLParse::Instance()->LoadXML(filePath);
        }
        if (it->first == WEAPON_ROOT_GAME)
        {
            CWeaponXMLParse::Instance()->LoadXML(filePath);
        }
        if (it->first == STAGE_ROOT_GAME)
        {
            CStageXMLParse::GetInstance().LoadXML(filePath);
        }
        if (it->first == XML_ROOT_ELEMENT_NAME)
        {
            CPicturePool::GetInstance()->LoadImage(CA2W(filePath));
        }
        if (it->first == CHATPAGE_ROOT_GAME)
        {
            CChatPageParser::Instance()->LoadXML(filePath);
        }
        if (it->first == CHAT_ROOT_GAME)
        {
            CChatParser::Instance()->LoadXML(filePath);
        }
        ::memset(filePath, 0, MAX_PATH);
    }
    return true;
}

bool CXMLResource::_Parse(TiXmlDocument& tiDoc)
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
    return _LoadGameXML(m_mapXMLList);
}