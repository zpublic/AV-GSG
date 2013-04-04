#include "stdafx.h"
#include "player_gamestatus.h"

Player_GameStatus::Player_GameStatus()
{
}

Player_GameStatus::~Player_GameStatus()
{
}

int Player_GameStatus::GetMaxScore()
{
	return m_nMaxScore;
}
	
void  Player_GameStatus::SetMaxScore(int nMaxScore)
{
	m_nMaxScore = nMaxScore;
}