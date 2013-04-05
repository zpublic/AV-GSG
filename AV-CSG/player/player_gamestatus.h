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
	///> ��Ҵ�ɻ��ĵ�����ߵ÷�
	int m_nPlayerMaxScore;
    int m_nPlayerHp;
    int m_nPlayerLifeNum;
    ///> ��Ҵ�ɻ��ĵ�ǰ�÷�
    int m_nPlayerCurrentScore;
};