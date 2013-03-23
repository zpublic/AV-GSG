#include "stdafx.h"
#include "PlaneXMLParse.h"

CPlaneXMLParse CPlaneXMLParse::m_Plane;

CPlaneXMLParse& CPlaneXMLParse::GetInstance()
{
    return m_Plane;
}

CPlaneXMLParse::CPlaneXMLParse()
{
}

CPlaneXMLParse::~CPlaneXMLParse()
{
    _Close();
}

const CPlaneXMLObject* CPlaneXMLParse::GetEnemyPlane(const std::string& strId) const
{
    auto it = m_mapEnemy.find(strId);
    if (it == m_mapEnemy.end())
    {
        return NULL;
    }
    return it->second;
}

const CPlaneXMLObject* CPlaneXMLParse::GetSelfPlane(const std::string& strId) const
{
    auto it = m_mapSelf.find(strId);
    if (it == m_mapSelf.end())
    {
        return NULL;
    }
    return it->second;
}

void CPlaneXMLParse::_Close()
{
    if (!m_mapEnemy.empty())
    {
        for (auto it = m_mapEnemy.begin(); it != m_mapEnemy.end(); it++)
        {
            delete it->second;
        }
    }
    if (!m_mapSelf.empty())
    {
        for (auto it = m_mapSelf.begin(); it != m_mapSelf.end(); it++)
        {
            delete it->second;
        }
    }
}

const int CPlaneXMLParse::EnemyTypeMax() const
{
    return m_mapEnemy.size();
}

const int CPlaneXMLParse::SelfTypeMax() const
{
    return m_mapSelf.size();
}

bool CPlaneXMLParse::LoadXML(const std::string& strPath)
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

bool CPlaneXMLParse::_Parse(TiXmlDocument& TinyXML)
{
    TiXmlElement* tiRoot = TinyXML.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != PLANE_ROOT_GAME)
    {
        return false;
    }

    TiXmlNode* tiFirst = tiRoot->FirstChild(PLANE_ENEMY_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }
    tiFirst = tiFirst->FirstChild(PLANE_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }
    for (TiXmlElement* tiElement = tiFirst->ToElement();
        tiElement != NULL;
        tiElement = tiElement->NextSiblingElement())
    {
        CPlaneXMLObject* pEnemy = new CPlaneXMLObject;
        if (tiElement->Attribute(ID_OBJECT) != NULL)
        {
            pEnemy->SetId(tiElement->Attribute(ID_OBJECT));
        }
        if (tiElement->Attribute(NAME_OBJECT) != NULL)
        {
            pEnemy->SetName(tiElement->Attribute(NAME_OBJECT));
        }
        if (tiElement->Attribute(PLANE_SKIN_OBJECT) != NULL)
        {
            pEnemy->SetSkinId(tiElement->Attribute(PLANE_SKIN_OBJECT));
        }
        if (tiElement->Attribute(PLANE_BULLETTYPE_OBJECT) != NULL)
        {
            pEnemy->SetBulletType(::atoi(tiElement->Attribute(PLANE_BULLETTYPE_OBJECT)));
        }
        if (tiElement->Attribute(PLANE_HP_OBJECT) != NULL)
        {
            pEnemy->SetHP(::atol(tiElement->Attribute(PLANE_HP_OBJECT)));
        }
        if (tiElement->Attribute(PLANE_SPEED_OBJECT) != NULL)
        {
            pEnemy->SetSpeed(::atoi(tiElement->Attribute(PLANE_SPEED_OBJECT)));
        }
        if (tiElement->Attribute(TYPE_OBJECT) != NULL)
        {
            pEnemy->SetType(tiElement->Attribute(TYPE_OBJECT));
        }
        m_mapEnemy[pEnemy->GetId()] = pEnemy;
    }

    tiFirst = tiRoot->FirstChild(PLANE_SELF_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }
    tiFirst = tiFirst->FirstChild(PLANE_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }
    for (TiXmlElement* tiElement = tiFirst->ToElement();
        tiElement != NULL;
        tiElement = tiElement->NextSiblingElement())
    {
        CPlaneXMLObject* pSelf = new CPlaneXMLObject;
        if (tiElement->Attribute(ID_OBJECT) != NULL)
        {
            pSelf->SetId(tiElement->Attribute(ID_OBJECT));
        }
        if (tiElement->Attribute(NAME_OBJECT) != NULL)
        {
            pSelf->SetName(tiElement->Attribute(NAME_OBJECT));
        }
        if (tiElement->Attribute(PLANE_SKIN_OBJECT) != NULL)
        {
            pSelf->SetSkinId(tiElement->Attribute(PLANE_SKIN_OBJECT));
        }
        if (tiElement->Attribute(PLANE_BULLETTYPE_OBJECT) != NULL)
        {
            pSelf->SetBulletType(::atoi(tiElement->Attribute(PLANE_BULLETTYPE_OBJECT)));
        }
        if (tiElement->Attribute(PLANE_HP_OBJECT) != NULL)
        {
            pSelf->SetHP(::atol(tiElement->Attribute(PLANE_HP_OBJECT)));
        }
        if (tiElement->Attribute(PLANE_SPEED_OBJECT) != NULL)
        {
            pSelf->SetSpeed(::atoi(tiElement->Attribute(PLANE_SPEED_OBJECT)));
        }
        if (tiElement->Attribute(TYPE_OBJECT) != NULL)
        {
            pSelf->SetType(tiElement->Attribute(TYPE_OBJECT));
        }
        m_mapSelf[pSelf->GetId()] = pSelf;
    }
    return true;
}