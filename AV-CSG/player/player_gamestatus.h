#pragma once
#include <list>

#define Default_Life    2

class Player_GameStatus
{
public:
    Player_GameStatus();
    ~Player_GameStatus();

public:
    ///> 单局最高得分
    int GetMaxScore();
    bool SetMaxScore(int nMaxScore);

    ///> 得到玩家得分榜的得分, 栈底为最低分, 栈顶为最高分 
    bool PopScore(int& nScore);
    ///> 值入玩家分数
    bool PushScore(int nScore);
    ///> 获得分数栈
    bool GetScoreStack(int nScoreStack[]);
    ///> 设置分数栈
    void SetScoreStack(int nScoreStack[]);

    ///> 剩余生命
    int GetLife();
    int AddLife(int nAdd = 1);
    int SubLife(int nSub = 1);

    ///> 血量
    int GetHp();
    void SetHp(int nHp);
    int AddHp(int nAdd);
    int SubHp(int nSub);

    ///> 当前得分
    int GetScore();
    int AddScore(int nAdd);
    int SubScore(int nSub);

    ///> 重置游戏状态
    void ResetGameStatus();

private:
    ///> 玩家打飞机的单局最高得分
    int m_nMaxScore;
    ///> 存储前10玩家的得分
    std::list<int> m_nScoreList;
    ///> 当前得分
    int m_nScroe;
    ///> 剩余血量
    int m_HP;
    ///> 剩余生命条数
    int m_nLife;
};