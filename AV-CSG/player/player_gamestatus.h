#pragma once

class Player_GameStatus
{
public:
	Player_GameStatus();
	~Player_GameStatus();

public:
    bool SetPlayerMaxScore(int nPlayerMaxScore);
	int GetPlayerMaxScore();
	
    bool SetPlayerHp(int nPlayerHp);
    int GetPlayerHp();
    
    bool SetPlayerLifeNum(int nPlayerLifeNum);
    int GetPlayerLifeNum();
    
    bool SetPlayerCurrentScore(int nPlayerCurrentScore);
    int GetPlayerCurrentScore();
    

private:
	///> 玩家打飞机的单局最高得分
	int m_nPlayerMaxScore;
    int m_nPlayerHp;
    int m_nPlayerLifeNum;
    ///> 玩家打飞机的当前得分
    int m_nPlayerCurrentScore;
};