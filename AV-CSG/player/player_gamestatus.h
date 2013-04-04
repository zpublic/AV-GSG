#pragma once

class Player_GameStatus
{
public:
	Player_GameStatus(int nMaxScore = 0);
	~Player_GameStatus();

public:
	int GetMaxScore();
	bool SetMaxScore(int nMaxScore);

private:
	int m_nMaxScore;  // 玩家打飞机的单局最高得分
};