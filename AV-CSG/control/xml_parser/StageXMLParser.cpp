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
        if (tiStage->Attribute(ID_OBJECT) != NULL)
        {
            pStage->SetId(tiStage->Attribute(ID_OBJECT));
        }
        if (tiStage->Attribute(NAME_OBJECT) != NULL)
        {
            pStage->SetName(tiStage->Attribute(NAME_OBJECT));
        }
        if (tiStage->Attribute(STAGE_MAP_OBJECT) != NULL)
        {
            pStage->SetMap(tiStage->Attribute(STAGE_MAP_OBJECT));
        }
        if (tiStage->Attribute(STAGE_DIFFICULTY_OBJECT) != NULL)
        {
            pStage->SetDifficulty(::atol(tiStage->Attribute(STAGE_DIFFICULTY_OBJECT)));
        }

        if (tiStage->Attribute(TYPE_OBJECT) != NULL)
        {
            pStage->SetType(tiStage->Attribute(TYPE_OBJECT));
        }

        TiXmlNode* tiEnemyItem = tiFirst->FirstChild(ITEM_GAME);
        if (tiEnemyItem != NULL)
        {
            for (TiXmlElement* tiItem = tiEnemyItem->FirstChildElement();
                tiItem != NULL;
                tiItem = tiItem->NextSiblingElement())
            {
                CStageXMLItem* pItem = new CStageXMLItem(tiItem->Attribute(ITEM_WAY_OBJECT));
                if (tiItem->Attribute(ID_OBJECT) != NULL)
                {
                    pItem->SetId(tiItem->Attribute(ID_OBJECT));
                }
                if (tiItem->Attribute(TYPE_OBJECT) != NULL)
                {
                    pItem->SetType(tiItem->Attribute(TYPE_OBJECT));
                }
                if (tiItem->Attribute(ITEM_NUMBER_OBJECT) != NULL)
                {
                    pItem->SetNumber(atol(tiItem->Attribute(ITEM_NUMBER_OBJECT)));
                }
                int PosX = 0, PosY = 0;
                if (tiItem->Attribute(POSX_OBJECT) != NULL)
                {
                    PosX = atoi(tiItem->Attribute(POSX_OBJECT));
                }
                if (tiItem->Attribute(POSY_OBJECT) != NULL)
                {
                    PosY = atoi(tiItem->Attribute(POSY_OBJECT));
                }
                pItem->SetPoint(PosX, PosY);
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
            if (tiElementEnemy->Attribute(ID_OBJECT) != NULL)
            {
                pEnemy->SetId(tiElementEnemy->Attribute(ID_OBJECT));
            }
            if (tiElementEnemy->Attribute(NAME_OBJECT) != NULL)
            {
                pEnemy->SetName(tiElementEnemy->Attribute(NAME_OBJECT));
            }
            if (tiElementEnemy->Attribute(TYPE_OBJECT) != NULL)
            {
                pEnemy->SetType(tiElementEnemy->Attribute(TYPE_OBJECT));
            }

            int PosX = 0, PosY = 0;
            if (tiElementEnemy->Attribute(POSX_OBJECT) != NULL)
            {
                PosX = atoi(tiElementEnemy->Attribute(POSX_OBJECT));
            }
            else
            {
                PosX = 0;
            }
            if (tiElementEnemy->Attribute(POSY_OBJECT) != NULL)
            {
                PosY = atoi(tiElementEnemy->Attribute(POSY_OBJECT));
            }
            else
            {
                PosY = 0;
            }
            pEnemy->SetPoint(PosX, PosY);

            if (tiElementEnemy->Attribute(ENEMY_APPEAR_OBJECT) != NULL)
            {
                pEnemy->SetAppear(atol(tiElementEnemy->Attribute(ENEMY_APPEAR_OBJECT)));
            }
            if (tiElementEnemy->Attribute(ENEMY_BIND_OBJECT) != NULL)
            {
                pEnemy->SetBind(tiElementEnemy->Attribute(ENEMY_BIND_OBJECT));
            }

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
                if (tiItem->Attribute(ID_OBJECT) != NULL)
                {
                    pItem->SetId(tiItem->Attribute(ID_OBJECT));
                }
                if (tiItem->Attribute(TYPE_OBJECT) != NULL)
                {
                    pItem->SetType(tiItem->Attribute(TYPE_OBJECT));
                }
                if (tiItem->Attribute(ITEM_NUMBER_OBJECT) != NULL)
                {
                    pItem->SetNumber(atol(tiItem->Attribute(ITEM_NUMBER_OBJECT)));
                }
                int PosX = 0, PosY = 0;
                if (tiItem->Attribute(POSX_OBJECT) != NULL)
                {
                    PosX = atoi(tiItem->Attribute(POSX_OBJECT));
                }
                if (tiItem->Attribute(POSY_OBJECT) != NULL)
                {
                    PosY = atoi(tiItem->Attribute(POSY_OBJECT));
                }
                pItem->SetPoint(PosX, PosY);
                pEnemy->PushItem(pItem);
            }
            pStage->PushEnemy(pEnemy);
        }
        m_mapStage[::atol(pStage->GetId().c_str())] = pStage;
    }
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