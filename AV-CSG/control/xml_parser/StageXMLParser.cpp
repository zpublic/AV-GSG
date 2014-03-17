#include "stdafx.h"
#include "StageXMLParser.h"

CStageXMLParse CStageXMLParse::m_XMLParse;

CStageXMLParse& CStageXMLParse::GetInstance()
{
    return m_XMLParse;
}

CStageXMLParse::CStageXMLParse()
{
}

CStageXMLParse::~CStageXMLParse()
{
    _Close();
}

void CStageXMLParse::_Close()
{
    if (!m_mapStage.empty())
    {
        for (auto it = m_mapStage.begin(); it != m_mapStage.end(); it++)
        {
            delete it->second;
        }
    }
}

int CStageXMLParse::Size() const
{
    return m_mapStage.size();
}

bool CStageXMLParse::Empty() const
{
    return m_mapStage.empty();
}

bool CStageXMLParse::LoadXML(const std::string& strPath)
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

bool CStageXMLParse::_Parse(TiXmlDocument& TinyXML)
{
    TiXmlElement* tiRoot = TinyXML.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != STAGE_ROOT_GAME)
    {
        return false;
    }

    TiXmlNode* tiFirst = tiRoot->FirstChild(STAGE_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }

    for (TiXmlElement* tiStage = tiFirst->ToElement();
        tiStage != NULL;
        tiStage = tiStage->NextSiblingElement())
    {
        CStageXMLStage* pStage = new CStageXMLStage;
        if (!BaseParse(pStage, tiStage))
        {
            continue;
        }
        std::string strMap;
        std::string strChat;
        int nDifficulty = 0;
        Unit::GetXmlStrAttributeA(tiStage ,STAGE_MAP_OBJECT, strMap);
        Unit::GetXmlStrAttributeA(tiStage ,STAGE_CHAT, strChat);
        Unit::GetXmlIntAttribute(tiStage ,STAGE_DIFFICULTY_OBJECT, nDifficulty);
        pStage->SetMap(strMap);
        pStage->SetChat(strChat);
        pStage->SetDifficulty(nDifficulty);

        TiXmlNode* tiEnemyItem = tiFirst->FirstChild(ITEM_GAME);
        if (tiEnemyItem != NULL)
        {
            for (TiXmlElement* tiItem = tiEnemyItem->FirstChildElement();
                tiItem != NULL;
                tiItem = tiItem->NextSiblingElement())
            {
                CStageXMLItem* pItem = new CStageXMLItem(tiItem->Attribute(ITEM_WAY_OBJECT));
                if (!BaseParse(pItem, tiItem))
                {
                    continue;
                }
                if(!_ParseItem(tiItem, pItem))
                {
                    continue;
                }
                PosObject posobjitem;
                BasePos(&posobjitem, tiItem);
                pItem->SetPoint(posobjitem.PosX, posobjitem.PosY);
                pStage->PushItem(pItem);
            }
        }

        TiXmlNode* tiEnemy = tiStage->FirstChild(ENEMY_GAME);
        if (tiEnemy == NULL)
        {
            return false;
        }
        for (TiXmlElement* tiElementEnemy = tiEnemy->ToElement();
            tiElementEnemy != NULL;
            tiElementEnemy = tiElementEnemy->NextSiblingElement())
        {
            CStageXMLEnemy* pEnemy = new CStageXMLEnemy;
            if (!BaseParse(pEnemy, tiElementEnemy))
            {
                continue;
            }
            PosObject posobjenemy;
            BasePos(&posobjenemy, tiElementEnemy);
            pEnemy->SetPoint(posobjenemy.PosX, posobjenemy.PosY);

            _ParseEnemy(tiElementEnemy, pEnemy);

            TiXmlNode* tiEnemyItem = tiEnemy->FirstChild(ITEM_GAME);
            if (tiEnemyItem == NULL)
            {
                return false;
            }
            for (TiXmlElement* tiItem = tiEnemyItem->ToElement();
                tiItem != NULL;
                tiItem = tiEnemyItem->NextSiblingElement())
            {
                CStageXMLItem* pItem = new CStageXMLItem(tiItem->Attribute(ITEM_WAY_OBJECT));
                if (!BaseParse(pItem, tiItem))
                {
                    continue;
                }
                if(!_ParseItem(tiItem, pItem))
                {
                    continue;
                }
                PosObject posobjitem;
                BasePos(&posobjitem, tiItem);
                pItem->SetPoint(posobjitem.PosX, posobjitem.PosY);
                pEnemy->PushItem(pItem);
            }
            pStage->PushEnemy(pEnemy);
        }
        m_mapStage[::atol(pStage->GetId().c_str())] = pStage;
    }
    return true;
}

bool CStageXMLParse::_ParseItem(TiXmlElement* pElement, CStageXMLItem* pItem)
{
    if (!pElement || !pItem)
    {
        return false;
    }
    int nNumber = 0;
    Unit::GetXmlIntAttribute(pElement, ITEM_NUMBER_OBJECT, nNumber);
    pItem->SetNumber(nNumber);
    return false;
}

bool CStageXMLParse::_ParseEnemy(TiXmlElement* pElement, CStageXMLEnemy* pEnemy)
{
    if (!pElement || !pEnemy)
    {
        return false;
    }
    int nAppear = 0;
    std::string strBind;
    Unit::GetXmlIntAttribute(pElement, ENEMY_APPEAR_OBJECT, nAppear);
    Unit::GetXmlStrAttributeA(pElement, ENEMY_BIND_OBJECT, strBind);
    pEnemy->SetAppear(nAppear);
    pEnemy->SetBind(strBind);
    return true;
}

CStageXMLStage* CStageXMLParse::Get(int nId) const
{
    auto it = m_mapStage.find(nId);
    if (it == m_mapStage.end())
    {
        return NULL;
    }
    return it->second;
}

const MapStageList::const_iterator CStageXMLParse::Begin() const
{
    return m_mapStage.begin();
}

const MapStageList::const_iterator CStageXMLParse::End() const
{
    return m_mapStage.end();
}