#include "stdafx.h"
#include "PlaneXMLParser.h"

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

void CPlaneXMLParse::_ParsePlane(TiXmlElement* tiElement, CPlaneXMLObject* pPlane)
{
    std::string strSkinId;
    std::string strWeapon;
    int nHp = 0;
    int nSpeed = 0;
    int nFrameCount = 0;
    Unit::GetXmlStrAttributeA(tiElement ,PLANE_SKIN_OBJECT, strSkinId);
    Unit::GetXmlStrAttributeA(tiElement ,PLANE_WEAPON_OBJECT, strWeapon);
    Unit::GetXmlIntAttribute(tiElement ,PLANE_HP_OBJECT, nHp);
    Unit::GetXmlIntAttribute(tiElement ,PLANE_SPEED_OBJECT, nSpeed);
    pPlane->SetWeapon(strWeapon);
    pPlane->SetSkinId(strSkinId);
    pPlane->SetHP(nHp);
    pPlane->SetSpeed(nSpeed);
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
        if (!BaseParse(pEnemy, tiElement))
        {
            continue;
        }
        _ParsePlane(tiElement, pEnemy);
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
        if (!BaseParse(pSelf, tiElement))
        {
            continue;
        }
        _ParsePlane(tiElement, pSelf);
        m_mapSelf[pSelf->GetId()] = pSelf;
    }
    return true;
}