#include "stdafx.h"
#include "WeaponXMLParser.h"

CWeaponXMLParse* Singleton<CWeaponXMLParse>::m_pInst = NULL;

CWeaponXMLParse::CWeaponXMLParse()
{
}

CWeaponXMLParse::~CWeaponXMLParse()
{
}

bool CWeaponXMLParse::Initialize()
{
    return true;
}

bool CWeaponXMLParse::LoadXML(const std::string& strPath)
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

const CWeaponXMLObject* CWeaponXMLParse::Get(const std::string& strId) const
{
    auto it = m_mapWeapon.find(strId);
    if (it == m_mapWeapon.end())
    {
        return NULL;
    }
    return it->second;
}

bool CWeaponXMLParse::_Parse(TiXmlDocument& TinyXML)
{
    TiXmlElement* tiRoot = TinyXML.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != WEAPON_ROOT_GAME)
    {
        return false;
    }

    TiXmlNode* tiFirst = tiRoot->FirstChild(WEAPON_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }
    for (TiXmlElement* tiElement = tiFirst->ToElement();
        tiElement != NULL;
        tiElement = tiElement->NextSiblingElement())
    {
        CWeaponXMLObject* pWeapon = new CWeaponXMLObject;
        if (!BaseParse(pWeapon, tiElement))
        {
            continue;
        }
        std::string strBullettype;
        std::string strEmitter;
        Unit::GetXmlStrAttributeA(tiElement, WEAPON_BULLETTYPE_OBJECT, strBullettype);
        Unit::GetXmlStrAttributeA(tiElement, WEAPON_EMITTER_OBJCET, strEmitter);
        pWeapon->SetBulletType(strBullettype);
        pWeapon->SetEmitter(strEmitter);
        m_mapWeapon[pWeapon->GetId()] = pWeapon;
    }
    return true;
}