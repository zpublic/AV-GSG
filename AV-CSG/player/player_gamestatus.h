#pragma once

class Player_GameStatus
{
public:
	Player_GameStatus();
	~Player_GameStatus();

public:
	int GetMaxScore();
	void SetMaxScore(int nMaxScore);

private:
	int m_nMaxScore;
};