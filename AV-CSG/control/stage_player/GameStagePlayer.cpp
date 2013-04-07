#include "stdafx.h"
#include "GameStagePlayer.h"

CGameStagePlayer CGameStagePlayer::m_StagePlayer;

CGameStagePlayer& CGameStagePlayer::GetInstance()
{
    return m_StagePlayer;
}

bool CGameStagePlayer::LoadStageXML(const CStageXMLParse* pStage)
{
    if (pStage)
    {
        m_pStage = pStage;
        return true;
    }
    return false;
}

int CGameStagePlayer::FirstStageId() const
{
    if (!m_pStage)
    {
        return 0;
    }
    return m_pStage->Begin()->first;
}

int CGameStagePlayer::StageCount() const
{
    if (!m_pStage)
    {
        return 0;
    }
    return m_pStage->Size();
}

CStageXMLStage* CGameStagePlayer::GetStage(int nId)
{
    if (!m_pStage)
    {
        return NULL;
    }
    return m_pStage->Get(nId);
}

CGameStagePlayer::CGameStagePlayer()
    : m_pStage(NULL)
{
}

CGameStagePlayer::~CGameStagePlayer()
{
}