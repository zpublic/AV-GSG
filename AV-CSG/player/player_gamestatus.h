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
	///> ��Ҵ�ɻ��ĵ�����ߵ÷�
	int m_nMaxScore;  
};