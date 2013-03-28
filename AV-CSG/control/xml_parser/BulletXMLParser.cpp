#include "stdafx.h"
#include "BulletXMLParser.h"

CBulletXMLParse CBulletXMLParse::m_Explosin;

CBulletXMLParse& CBulletXMLParse::GetInstance()
{
    return m_Explosin;
}

CBulletXMLParse::CBulletXMLParse()
{
}

CBulletXMLParse::~CBulletXMLParse()
{
    _Close();
}

const CBulletXMLObject* CBulletXMLParse::Get(const std::string& strId) const
{
    auto it = m_mapBullet.find(strId);
    if (it == m_mapBullet.end())
    {
        return NULL;
    }
    return it->second;
}


void CBulletXMLParse::_Close()
{
    if (!m_mapBullet.empty())
    {
        for (auto it = m_mapBullet.begin(); it != m_mapBullet.end(); it++)
        {
            delete it->second;
        }
    }
}

const int CBulletXMLParse::Size() const
{
    return m_mapBullet.size();
}


bool CBulletXMLParse::LoadXML(const std::string& strPath)
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

bool CBulletXMLParse::_Parse(TiXmlDocument& TinyXML)
{
    TiXmlElement* tiRoot = TinyXML.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != BULLET_ROOT_GAME)
    {
        return false;
    }

    TiXmlNode* tiFirst = tiRoot->FirstChild(BULLET_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }
    for (TiXmlElement* tiElement = tiFirst->ToElement();
        tiElement != NULL;
        tiElement = tiElement->NextSiblingElement())
    {
        CBulletXMLObject* pExplosion = new CBulletXMLObject;
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
        if (tiElement->Attribute(BULLET_POWER_GAME) != NULL)
        {
            pExplosion->SetPower(::atol(tiElement->Attribute(BULLET_POWER_GAME)));
        }
        if (tiElement->Attribute(BULLET_SPEED_GAME) != NULL)
        {
            pExplosion->SetSpeed(::atoi(tiElement->Attribute(BULLET_SPEED_GAME)));
        }
        if (tiElement->Attribute(TYPE_OBJECT) != NULL)
        {
            pExplosion->SetType(tiElement->Attribute(TYPE_OBJECT));
        }
        if (tiElement->Attribute(FRAMECOUNT_OBJECT) != NULL)
        {
            pExplosion->SetFrameCount(::atol(tiElement->Attribute(FRAMECOUNT_OBJECT)));
        }
        if (tiElement->Attribute(WIDTH_OBJCET) != NULL)
        {
            pExplosion->SetWidth(::atol(tiElement->Attribute(WIDTH_OBJCET)));
        }
        if (tiElement->Attribute(HEIGHT_OBJECT) != NULL)
        {
            pExplosion->SetHeight(::atol(tiElement->Attribute(HEIGHT_OBJECT)));
        }
        m_mapBullet[pExplosion->GetId()] = pExplosion;
    }
    return true;
}