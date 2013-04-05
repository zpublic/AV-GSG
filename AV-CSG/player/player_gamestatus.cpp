#include "stdafx.h"
#include "player_gamestatus.h"

Player_GameStatus::Player_GameStatus()
	: m_nPlayerMaxScore(0)
    , m_nPlayerHp(0)
    , m_nPlayerLifeNum(0)
    , m_nPlayerCurrentScore(0)
{
}

Player_GameStatus::~Player_GameStatus()
{
}

bool Player_GameStatus::SetPlayerMaxScore(int nPlayerMaxScore)
{
	if(nPlayerMaxScore <= 0 || nPlayerMaxScore < m_nPlayerMaxScore)
	{
		return false;
	}
	m_nPlayerMaxScore = nPlayerMaxScore;
	return true;
}

int Player_GameStatus::GetPlayerMaxScore()			
{
	return m_nPlayerMaxScore;
}


bool Player_GameStatus::SetPlayerHp(int nPlayerHp)
{
    if(nPlayerHp < 0)
    {
        return false;
    }

    m_nPlayerHp = nPlayerHp;
}
    
int Player_GameStatus::GetPlayerHp()
{
    return m_nPlayerHp;
}


bool Player_GameStatus::SetPlayerLifeNum(int nPlayerLifeNum)
{
    if(nPlayerLifeNum < 0)
    {
        return false;
    }

    m_nPlayerLifeNum = nPlayerLifeNum;
}

int Player_GameStatus::GetPlayerLifeNum()
{
    return m_nPlayerLifeNum;
}


bool Player_GameStatus::SetPlayerCurrentScore(int nPlayerCurrentScore)
{
    if(nPlayerCurrentScore < 0 && nPlayerCurrentScore < m_nPlayerCurrentScore)
    {
        return false;
    }

    m_nPlayerCurrentScore = nPlayerCurrentScore;
}

int Player_GameStatus::GetPlayerCurrentScore()
{
    return m_nPlayerCurrentScore;
}