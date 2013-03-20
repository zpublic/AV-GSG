#include "stdafx.h"
#include "GameStatus.h"


GameStatus CGameStatus::m_emGameStatus = emGameStatusReady;

CGameStatus::CGameStatus(void)
{
}

CGameStatus::~CGameStatus(void)
{
}

bool CGameStatus::GetGameOver()
{
    return m_emGameStatus == emGameStatusOver;
}

bool CGameStatus::GetGameReady()
{
    return m_emGameStatus == emGameStatusReady;
}

bool CGameStatus::GetGameRuning()
{
    return m_emGameStatus == emGameStatusRuning;
}

bool CGameStatus::GetGamePause()
{
    return m_emGameStatus == emGameStatusPause;
}

void CGameStatus::ClearGameStatus()
{
    m_emGameStatus = emGameStatusNone;
}

bool CGameStatus::IsNeedUpdate()
{
    return m_emGameStatus != emGameStatusNone;
}

void CGameStatus::StartGame()
{
    m_emGameStatus = emGameStatusRuning;
}

void CGameStatus::PauseGame()
{
    m_emGameStatus = emGameStatusPause;
}

void CGameStatus::SetGameOver()
{
    m_emGameStatus = emGameStatusOver;
}
