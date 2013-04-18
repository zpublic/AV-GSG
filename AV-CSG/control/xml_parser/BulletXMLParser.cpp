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
        std::string strSkinId;
        int nPower = 0;
        int nSpeed = 0;
        int nFrameCount = 0;
        if (!BaseParse(pExplosion, tiElement))
        {
            continue;
        }
        Unit::GetXmlStrAttributeA(tiElement ,PLANE_SKIN_OBJECT, strSkinId);
        Unit::GetXmlIntAttribute(tiElement ,BULLET_POWER_GAME, nPower);
        Unit::GetXmlIntAttribute(tiElement ,BULLET_SPEED_GAME, nSpeed);
        Unit::GetXmlIntAttribute(tiElement ,FRAMECOUNT_OBJECT, nFrameCount);
        pExplosion->SetFrameCount(nFrameCount);
        pExplosion->SetSkinId(strSkinId);
        pExplosion->SetPower(nPower);
        pExplosion->SetSpeed(nSpeed);

        ShapeObject shapeobj;
        BaseShape(&shapeobj, tiElement);
        pExplosion->SetWidth(shapeobj.nWidth);
        pExplosion->SetHeight(shapeobj.nHeight);
        m_mapBullet[pExplosion->GetId()] = pExplosion;
    }
    return true;
}