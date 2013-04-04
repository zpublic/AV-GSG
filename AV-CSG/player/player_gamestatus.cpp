#include "stdafx.h"
#include "player_gamestatus.h"

Player_GameStatus::Player_GameStatus(int nMaxScore/*=0*/)
	: m_nMaxScore(nMaxScore)
{
}

Player_GameStatus::~Player_GameStatus()
{
}

int Player_GameStatus::GetMaxScore()			
{
	return m_nMaxScore;
}
	
bool  Player_GameStatus::SetMaxScore(int nMaxScore)
{
	if(nMaxScore <= 0 || nMaxScore < m_nMaxScore){
		return false;
	}
	m_nMaxScore = nMaxScore;
	return true;
}