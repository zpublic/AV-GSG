#include "stdafx.h"
#include "GameStagePlayer.h"

CGameStagePlayer CGameStagePlayer::m_StagePlayer;

CGameStagePlayer& CGameStagePlayer::GetInstance()
{
    return m_StagePlayer;
}

bool CGameStagePlayer::Stage(const CStageXMLParse* pStage)
{
    if (pStage->Begin() == pStage->End())
    {
        return false;
    }
    m_StageBegin = pStage->Begin();
    m_StageEnd = pStage->End();
    m_pStage = m_StageBegin->second;
    m_emType = (GameStagePlayType)::atol(m_StageBegin->second->GetType().c_str());
    if (m_pStage == NULL)
    {
        return false;
    }
    m_emStatus = emGameStagePlayStatusRuning;
    return true;
}

GameStagePlayStatus CGameStagePlayer::PresentStatus() const
{
    return m_emStatus;
}

CGameStagePlayer::CGameStagePlayer()
    : m_pStage(NULL)
    , m_emStatus(emGameStagePlayStatusRuning)
    , m_lnFrame(0)
    , m_lnStopwatch(0)
    , m_lnEnemyNumber(0)
    , m_lnDeadEnemy(0)
{
}

CGameStagePlayer::~CGameStagePlayer()
{
}

void CGameStagePlayer::Updata(int nEnemyNumber)
{
    if (m_lnFrame == FastenFrameNum_Play)
    {
        m_lnStopwatch++;
    }
    else
    {
        m_lnFrame++;
    }
    switch (m_emType)
    {
    case emGameStagePlayTime:
        break;
    case emGameStagePlayEnemy:
        if ((m_lnEnemyNumber - nEnemyNumber) == 0)
        {
            m_emStatus = emGameStagePlayStatusNone;
        }
        break;
    case emGameStagePlayEnemyBoss:
        break;
    default:
        break;
    }
}

const CStageXMLStage* CGameStagePlayer::PresentObject() const
{
    return m_pStage;
}

void CGameStagePlayer::NextStage()
{
    if (m_StageBegin != m_StageEnd)
    {
        m_StageBegin++;
    }
}

long CGameStagePlayer::Stopwatch() const
{
    return m_lnStopwatch;
}