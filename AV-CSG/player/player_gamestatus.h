#pragma once

class Player_GameStatus
{
public:
	Player_GameStatus();
	~Player_GameStatus();

public:
	int GetMaxScore();
	bool SetMaxScore(int nMaxScore);

private:
	///> 玩家打飞机的单局最高得分
	int m_nMaxScore;  
};